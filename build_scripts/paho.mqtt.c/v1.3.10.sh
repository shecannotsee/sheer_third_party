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
git clone https://github.com/eclipse/paho.mqtt.c.git ./libraries/paho.mqtt.c/ || \
  { echo "Failed to clone paho.mqtt.c repository."; exit 1; }
cd libraries
mv paho.mqtt.c paho.mqtt.c-src
mkdir paho.mqtt.c-v1.3.10
cd paho.mqtt.c-v1.3.10
install_path=$(pwd)
cd ..

# build
cd paho.mqtt.c-src
git checkout v1.3.10 || \
  { echo "Failed to checkout v1.3.10 of paho.mqtt.c."; exit 1; }
mkdir build
cd build
# set openssl path
cmake -DCMAKE_INSTALL_PREFIX="$install_path" \
  -DPAHO_WITH_SSL=TRUE \
  -DOPENSSL_ROOT_DIR=../../../libraries/openssl-1.1.1 \
  .. || \
  { echo "cmake failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }
