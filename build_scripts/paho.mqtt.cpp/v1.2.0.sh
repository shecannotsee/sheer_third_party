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
git clone https://github.com/eclipse/paho.mqtt.cpp.git ./libraries/paho.mqtt.cpp/
cd libraries
mv paho.mqtt.cpp paho.mqtt.cpp-src
mkdir paho.mqtt.cpp-v1.2.0
cd paho.mqtt.cpp-v1.2.0
install_path=$(pwd)
cd ..

# build
cd paho.mqtt.cpp-src
git checkout v1.2.0
mkdir build
cd build
# set openssl path
cmake -DCMAKE_INSTALL_PREFIX="$install_path" \
  -DPAHO_WITH_SSL=TRUE \
  -DOPENSSL_ROOT_DIR=/home/shecannotsee/Desktop/sheer_third_party/libraries/openssl-1.1.1 \
  -DCMAKE_PREFIX_PATH=/home/shecannotsee/Desktop/sheer_third_party/libraries/paho.mqtt.c-v1.3.10 \
  ..
make -j8
make install
