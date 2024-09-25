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
git clone https://github.com/jbeder/yaml-cpp.git ./libraries/yaml-cpp/
cd libraries
mv yaml-cpp yaml-cpp-src
mkdir yaml-cpp-0.8.0
cd yaml-cpp-0.8.0
install_path=$(pwd)
cd ..

# build
cd yaml-cpp-src
git checkout 0.8.0
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" ..
make -j8
make install
