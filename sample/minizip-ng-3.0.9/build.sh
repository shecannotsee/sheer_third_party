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
git clone https://github.com/zlib-ng/minizip-ng.git ./libraries/minizip-ng/
cd libraries
mv minizip-ng minizip-ng-src
mkdir minizip-ng
cd minizip-ng
install_path=$(pwd)
cd ..

# build
cd minizip-ng-src
git checkout 3.0.9
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" \
  MZ_BUILD_TESTS=OFF \
  ..
make -j8
make install









