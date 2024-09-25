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
git clone https://github.com/protocolbuffers/protobuf.git ./libraries/protobuf/
cd libraries
mv protobuf protobuf-src
mkdir protobuf-v3.20.2
cd protobuf-v3.20.2
install_path=$(pwd)
cd ..

# build
cd protobuf-src
git checkout v3.20.2
git submodule update --init --recursive
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" -Dprotobuf_BUILD_TESTS=OFF ../cmake/
make -j8
make install
