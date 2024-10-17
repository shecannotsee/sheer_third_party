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
git clone https://github.com/boostorg/boost.git ./libraries/boost/ || \
  { echo "Failed to clone boost repository."; exit 1; }
cd libraries
mv boost boost-src
mkdir boost-1.79.0
cd boost-1.79.0
install_path=$(pwd)
cd ..

# build
cd boost-src
git checkout boost-1.79.0 || \
  { echo "Failed to checkout boost-1.79.0 of boost."; exit 1; }
git submodule update --init --recursive || \
  { echo "git submodule failed."; exit 1; }
./bootstrap.sh --prefix="$install_path" || \
  { echo "bootstrap failed."; exit 1; }
# set python version
# ./bootstrap.sh --with-python=/usr/local/python3.8/bin/python3 --prefix="$install_path"
./b2 install || \
  { echo "install failed."; exit 1; }
