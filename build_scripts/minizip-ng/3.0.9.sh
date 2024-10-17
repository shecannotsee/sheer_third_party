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
git clone https://github.com/zlib-ng/minizip-ng.git ./libraries/minizip-ng/ || \
  { echo "Failed to clone minizip-ng repository."; exit 1; }
cd libraries
mv minizip-ng minizip-ng-src
mkdir minizip-ng-3.0.9
cd minizip-ng-3.0.9
install_path=$(pwd)
cd ..

# build
cd minizip-ng-src
git checkout 3.0.9 || \
  { echo "Failed to checkout 3.0.9 of minizip-ng-src."; exit 1; }
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" \
  MZ_BUILD_TESTS=OFF \
  .. || \
  { echo "cmake failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }
