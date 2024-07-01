#ifndef RTSP_TO_JPEG_H
#define RTSP_TO_JPEG_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

extern "C" {
#include <jpeglib.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

namespace rtsp_to_jpeg {

void save_frame_as_jpeg(AVFrame *pFrame, int width, int height, int iFrame) {
  // Create JPEG file name
  char filename[32];
  snprintf(filename, sizeof(filename), "frame%d.jpg", iFrame);

  // Open file
  FILE *jpeg_file = fopen(filename, "wb");
  if (!jpeg_file) {
    std::cerr << "Could not open file " << filename << std::endl;
    return;
  }

  // Initialize JPEG compression object
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  jpeg_stdio_dest(&cinfo, jpeg_file);

  // Set parameters for compression
  cinfo.image_width      = width;
  cinfo.image_height     = height;
  cinfo.input_components = 3;  // Number of color components per pixel
  cinfo.in_color_space   = JCS_RGB;
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, 85, TRUE);  // Adjust the quality value as needed

  // Start compression
  jpeg_start_compress(&cinfo, TRUE);

  // Convert the frame to RGB format
  std::vector<uint8_t> buffer(width * 3);  // RGB buffer
  JSAMPROW row_pointer[1];
  while (cinfo.next_scanline < cinfo.image_height) {
    int y = cinfo.next_scanline;
    for (int x = 0; x < width; x++) {
      buffer[x * 3 + 0] = pFrame->data[0][y * pFrame->linesize[0] + x * 3 + 0];
      buffer[x * 3 + 1] = pFrame->data[0][y * pFrame->linesize[0] + x * 3 + 1];
      buffer[x * 3 + 2] = pFrame->data[0][y * pFrame->linesize[0] + x * 3 + 2];
    }
    row_pointer[0] = &buffer[0];
    jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  // Finish compression
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);

  // Close the file
  fclose(jpeg_file);
}

int run() {
  // Register all formats and codecs
  av_register_all();
  avformat_network_init();

  // Open RTSP stream
  AVFormatContext *pFormatCtx = avformat_alloc_context();
  AVDictionary *opts          = nullptr;
  av_dict_set(&opts, "rtsp_transport", "tcp", 0);  // Use TCP for more reliability
  av_dict_set(&opts, "max_delay", "500000", 0);    // Set max delay to 500ms

  if (avformat_open_input(&pFormatCtx, "rtsp://localhost:8554/mystream", nullptr, &opts) != 0) {
    std::cerr << "Could not open source" << std::endl;
    return -1;
  }
  av_dict_free(&opts);

  // Retrieve stream information
  if (avformat_find_stream_info(pFormatCtx, nullptr) < 0) {
    std::cerr << "Could not find stream information" << std::endl;
    return -1;
  }

  // Find the first video stream
  int videoStream = -1;
  for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++) {
    if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
      videoStream = i;
      break;
    }
  }
  if (videoStream == -1) {
    std::cerr << "Could not find a video stream" << std::endl;
    return -1;
  }

  // Get a pointer to the codec context for the video stream
  AVCodecParameters *pCodecPar = pFormatCtx->streams[videoStream]->codecpar;
  AVCodec *pCodec              = avcodec_find_decoder(pCodecPar->codec_id);
  if (!pCodec) {
    std::cerr << "Unsupported codec" << std::endl;
    return -1;
  }

  AVCodecContext *pCodecCtx = avcodec_alloc_context3(pCodec);
  if (avcodec_parameters_to_context(pCodecCtx, pCodecPar) < 0) {
    std::cerr << "Could not copy codec context" << std::endl;
    return -1;
  }

  // Open codec
  if (avcodec_open2(pCodecCtx, pCodec, nullptr) < 0) {
    std::cerr << "Could not open codec" << std::endl;
    return -1;
  }

  // Allocate video frame
  AVFrame *pFrame    = av_frame_alloc();
  AVFrame *pFrameRGB = av_frame_alloc();
  if (!pFrame || !pFrameRGB) {
    std::cerr << "Could not allocate video frame" << std::endl;
    return -1;
  }

  // Determine required buffer size and allocate buffer
  int numBytes    = av_image_get_buffer_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height, 32);
  uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

  // Assign appropriate parts of buffer to image planes in pFrameRGB
  av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, buffer, AV_PIX_FMT_RGB24, pCodecCtx->width,
                       pCodecCtx->height, 1);

  // Initialize SWS context for software scaling
  struct SwsContext *sws_ctx =
      sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
                     AV_PIX_FMT_RGB24, SWS_BILINEAR, nullptr, nullptr, nullptr);

  int frameFinished;
  AVPacket packet;
  int i = 0;

  while (av_read_frame(pFormatCtx, &packet) >= 0) {
    // Is this a packet from the video stream?
    if (packet.stream_index == videoStream) {
      // Decode video frame
      int ret = avcodec_send_packet(pCodecCtx, &packet);
      if (ret < 0) {
        std::cerr << "Error sending a packet for decoding: " << ret << std::endl;
        av_packet_unref(&packet);
        continue;
      }

      while (ret >= 0) {
        ret = avcodec_receive_frame(pCodecCtx, pFrame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
          break;
        } else if (ret < 0) {
          std::cerr << "Error during decoding: " << ret << std::endl;
          break;
        }

        // Convert the image from its native format to RGB
        sws_scale(sws_ctx, (uint8_t const *const *)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
                  pFrameRGB->data, pFrameRGB->linesize);

        // Save the frame as a JPEG file
        save_frame_as_jpeg(pFrameRGB, pCodecCtx->width, pCodecCtx->height, i++);
      }
    }

    // Free the packet that was allocated by av_read_frame
    av_packet_unref(&packet);
  }

  // Free the RGB image
  av_free(buffer);
  av_frame_free(&pFrameRGB);

  // Free the YUV frame
  av_frame_free(&pFrame);

  // Close the codecs
  avcodec_close(pCodecCtx);

  // Close the video file
  avformat_close_input(&pFormatCtx);

  return 0;
}

}  // namespace rtsp_to_jpeg

#endif  // RTSP_TO_JPEG_H
