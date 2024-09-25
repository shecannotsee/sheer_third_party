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
git clone https://github.com/gabime/spdlog.git ./libraries/spdlog/
cd libraries
mv spdlog spdlog-src
mkdir spdlog-v1.10.0
cd spdlog-v1.10.0
install_path=$(pwd)
cd ..

# build
cd spdlog-src
git checkout v1.10.0
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" ..
make -j8
make install
