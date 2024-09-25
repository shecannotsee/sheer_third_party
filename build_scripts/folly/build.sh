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
git clone https://github.com/facebook/folly.git ./libraries/folly/
cd libraries
mv folly folly-src
mkdir folly
cd folly
install_path=$(pwd)
cd ..

# build
cd folly-src
git checkout v2023.08.07.00
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/home/shecannotsee/desktop/sheer_third_party/libraries/folly \
      -DBUILD_TESTS=OFF \
      -DCMAKE_INCLUDE_PATH=../../boost/include:../../googletest/include \
      -DCMAKE_LIBRARY_PATH=../../boost/lib:../../googletest/lib \
      ..
make -j8
make install








