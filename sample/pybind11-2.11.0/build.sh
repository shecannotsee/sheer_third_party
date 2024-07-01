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
git clone https://github.com/pybind/pybind11.git ./libraries/pybind11/
cd libraries
mv pybind11 pybind11-src
mkdir pybind11
cd pybind11
install_path=$(pwd)
cd ..

# build
cd pybind11-src
git checkout v2.11.0
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" ..
make -j8
make install









