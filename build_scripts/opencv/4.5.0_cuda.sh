#!/bin/bash
project="sheer_third_party"
project_length=${#project}
# Get pwd string
cd ..
cd ..
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
git clone https://github.com/opencv/opencv.git ./libraries/opencv/
git clone https://github.com/opencv/opencv_contrib.git ./libraries/opencv_contrib/
cd libraries
cd opencv_contrib
git checkout 4.5.0
opencv_contrib_path=$(pwd)
cd ..
mv opencv opencv-src
mkdir opencv
cd opencv
install_path=$(pwd)
cd ..

# build
cd opencv-src
git checkout 4.5.0
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX="$install_path" \
      -DOPENCV_EXTRA_MODULES_PATH="$opencv_contrib_path"/modules \
      -DWITH_CUDA=ON \
      -DENABLE_FAST_MATH=ON \
      -DCUDA_FAST_MATH=ON \
      -DWITH_CUBLAS=ON \
      -DOPENCV_DNN_CUDA=ON \
#      -DCUDNN_INCLUDE_DIR=/data1/home/home/hairuiqiao/third_partys/cudnn-linux-x86_64-9.2.0.82_cuda11-archive/include \
#      -DCUDNN_LIBRARY=/data1/home/home/hairuiqiao/third_partys/cudnn-linux-x86_64-9.2.0.82_cuda11-archive/lib/libcudnn.so \
      ..


make -j8
make install
