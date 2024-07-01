#ifndef RTSP_TO_H264_H
#define RTSP_TO_H264_H

#include <unistd.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

namespace rtsp_to_h264 {

int run() {
  AVFormatContext* format_ctx = nullptr;
  AVPacket packet;

  const char* input_url      = "rtsp://localhost:8554/mystream";
  const char* outputFilename = "rtsp_to_h264.h264";

  av_register_all();

  // 1.input rtsp
  if (avformat_open_input(&format_ctx, input_url, nullptr, nullptr) != 0) {
    std::cerr << "Error: Couldn't open input file." << std::endl;
    return -1;
  }

  // 2.find stream info
  if (avformat_find_stream_info(format_ctx, nullptr) < 0) {
    std::cerr << "Error: Couldn't find stream information." << std::endl;
    return -1;
  }

  // Find video stream
  int videoStream = -1;
  for (unsigned int i = 0; i < format_ctx->nb_streams; i++) {
    if (format_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
      videoStream = i;
      break;
    }
  }

  if (videoStream == -1) {
    std::cerr << "Error: Couldn't find video stream." << std::endl;
    return -1;
  }

  // Get video stream parameters
  AVCodecParameters* codec_params = format_ctx->streams[videoStream]->codecpar;
  int width = codec_params->width;
  int height = codec_params->height;

  std::cout << "Video Resolution: " << width << "x" << height << std::endl;

  // Open output file
  FILE* outputFile = fopen(outputFilename, "wb");
  if (!outputFile) {
    std::cerr << "Error: Couldn't open output file." << std::endl;
    return -1;
  }

  // Read frames and write H.264 data to file
  while (av_read_frame(format_ctx, &packet) >= 0) {
    if (packet.stream_index == videoStream) {
      // Write H.264 data to file
      fwrite(packet.data, 1, packet.size, outputFile);
    }
    av_packet_unref(&packet);
  }

  fclose(outputFile);

  // Clean up
  avformat_close_input(&format_ctx);

  return 0;
}

}  // namespace rtsp_to_h264

#endif  // RTSP_TO_H264_H
