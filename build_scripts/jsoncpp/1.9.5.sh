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
git clone https://github.com/open-source-parsers/jsoncpp.git ./libraries/jsoncpp/ || \
  { echo "Failed to clone jsoncpp repository."; exit 1; }
cd libraries
mv jsoncpp jsoncpp-src
mkdir jsoncpp-1.9.5
cd jsoncpp-1.9.5
install_path=$(pwd)
cd ..

# build
cd jsoncpp-src
git checkout 1.9.5 || \
  { echo "Failed to checkout 1.9.5 of jsoncpp."; exit 1; }
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" .. || \
  { echo "cmake failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }
