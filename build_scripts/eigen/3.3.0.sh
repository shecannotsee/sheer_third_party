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

git clone https://gitlab.com/libeigen/eigen.git ./libraries/eigen/ || \
  { echo "Failed to clone eigen repository."; exit 1; }
cd libraries
mv eigen eigen-src
mkdir eigen-3.3.0
cd eigen-3.3.0
install_path=$(pwd)
cd ..

# build
cd eigen-src
git checkout 3.3.0 || \
  { echo "Failed to checkout 3.3.0 of eigen."; exit 1; }
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" .. || \
  { echo "cmake failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }