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
git clone https://github.com/Neargye/magic_enum.git ./libraries/magic_enum/ || \
  { echo "Failed to clone magic_enum repository."; exit 1; }
cd libraries
mv magic_enum magic_enum-src
mkdir magic_enum-v0.9.0
cd magic_enum-v0.9.0
install_path=$(pwd)
cd ..

# build
cd magic_enum-src
git checkout v0.9.0 || \
  { echo "Failed to checkout v0.9.0 of magic_enum."; exit 1; }
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" .. || \
  { echo "cmake failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }
