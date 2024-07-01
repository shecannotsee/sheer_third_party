#ifndef CUT_FRAME_TO_JPEG_H
#define CUT_FRAME_TO_JPEG_H

#include <fcntl.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace cut_frame_to_h264 {

int run() {
  av_register_all();
  avcodec_register_all();

  AVFormatContext *formatContext = nullptr;
  AVPacket packet;
  av_init_packet(&packet);

  const char *rtspUrl    = "rtsp://localhost:8554/mystream";
  const char *outputFile = "frame";  // 或者 ".265"，根据需要选择

  // 打开RTSP流
  if (avformat_open_input(&formatContext, rtspUrl, nullptr, nullptr) != 0) {
    fprintf(stderr, "无法打开RTSP流\n");
    return 1;
  }

  // 查找流信息
  if (avformat_find_stream_info(formatContext, nullptr) < 0) {
    fprintf(stderr, "无法获取流信息\n");
    return 1;
  }

  // 找到视频流
  int videoStreamIndex = -1;
  for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
    if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
      videoStreamIndex = i;
      break;
    }
  }

  if (videoStreamIndex == -1) {
    fprintf(stderr, "未找到视频流\n");
    return 1;
  }

  AVCodecParameters *codecParameters = formatContext->streams[videoStreamIndex]->codecpar;
  AVCodec *codec                     = avcodec_find_decoder(codecParameters->codec_id);

  if (!codec) {
    fprintf(stderr, "未找到解码器\n");
    return 1;
  }

  AVCodecContext *codecContext = avcodec_alloc_context3(codec);
  avcodec_parameters_to_context(codecContext, codecParameters);

  if (avcodec_open2(codecContext, codec, nullptr) < 0) {
    fprintf(stderr, "无法打开解码器\n");
    return 1;
  }

  // 打开输出文件
  FILE *outputFilePtr = fopen(outputFile, "wb");
  if (!outputFilePtr) {
    fprintf(stderr, "无法打开输出文件\n");
    return 1;
  }

  int frame_sum = 0;
  int id        = 1;
  // 读取数据并保存为H.264/H.265文件
  while (av_read_frame(formatContext, &packet) >= 0) {
    if (packet.stream_index == videoStreamIndex) {
      // 写入数据到输出文件
      fwrite(packet.data, 1, packet.size, outputFilePtr);
      frame_sum++;

      // 如果是一个GOP的结尾，关闭当前文件并打开新文件
      if (packet.flags & AV_PKT_FLAG_KEY) {
        if (id == 1) {
          std::string file_name_temp = "frame_" + std::to_string(id) + "_" + std::to_string(frame_sum) + ".h264";
          std::string command        = "mv frame " + file_name_temp;
          system(command.c_str());
        }
        fclose(outputFilePtr);
        char filename[256];
        id++;
        snprintf(filename, sizeof(filename), "frame_%d_%d.%s", id, frame_sum,
                 codecContext->codec_id == AV_CODEC_ID_H264 ? "h264" : "h265");
        frame_sum = 0;

        outputFilePtr = fopen(filename, "wb");
        if (!outputFilePtr) {
          fprintf(stderr, "无法打开输出文件\n");
          return 1;
        }
      }
    }
    av_packet_unref(&packet);
  }

  // 清理资源
  fclose(outputFilePtr);
  avcodec_free_context(&codecContext);
  avformat_close_input(&formatContext);
  avformat_free_context(formatContext);

  return 0;
}

}  // namespace cut_frame_to_jpeg

#endif  // CUT_FRAME_TO_JPEG_H
