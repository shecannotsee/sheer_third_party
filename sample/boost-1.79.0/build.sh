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
git clone https://github.com/boostorg/boost.git ./libraries/boost/
cd libraries
mv boost boost-src
mkdir boost
cd boost
install_path=$(pwd)
cd ..

# build
cd boost-src
git checkout boost-1.79.0
git submodule update --init --recursive
./bootstrap.sh --prefix="$install_path"
./b2 install
