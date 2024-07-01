//
// Created by shecannotsee on 24-5-27.
//

#include <iostream>

#include "cut_frame_to_h264.h"
#include "rtsp_to_h264.h"
#include "rtsp_to_jpeg.h"

int main() {
  std::cout << "ffmpeg_4.1 test start" << std::endl;
  // rtsp_to_h264::run();
  // cut_frame_to_h264::run();
  rtsp_to_jpeg::run();
  return 0;
}