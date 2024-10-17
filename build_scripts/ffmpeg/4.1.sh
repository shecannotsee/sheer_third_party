#!/bin/bash
project="sheer_third_party"
project_length=${#project}
# Get pwd string
path=$(pwd)
# Get last project_length chars
suffix="${path: -$project_length}"
if [ "$suffix" = "$project" ]; then
    echo "ok"
else
    echo "Path error.Please ensure that the last few strings after using pwd are "$project
    exit 1  # stop
fi
# check dir libraries
echo "Check libraries exist?"
if [ -d "./libraries" ];
then
    echo "libraries."
else
    echo "Create libraries."
fi

# get source code
git clone https://github.com/FFmpeg/FFmpeg.git ./libraries/ffmpeg || \
  { echo "Failed to clone FFmpeg repository."; exit 1; }
cd libraries
mv ffmpeg ffmpeg-src
mkdir ffmpeg-4.1
cd ffmpeg-4.1
install_path=$(pwd)
cd ..

# build
cd ffmpeg-src
git checkout release/4.1 || \
  { echo "Failed to checkout release/4.1 of ffmpeg."; exit 1; }
./configure --prefix="$install_path" --enable-shared --enable-gpl --enable-libx264 --enable-libx265 || \
  { echo "configure failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }
