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
git clone https://github.com/ArthurSonzogni/FTXUI.git ./libraries/FTXUI/ || \
  { echo "Failed to clone FTXUI repository."; exit 1; }
cd libraries
mv FTXUI FTXUI-src
mkdir FTXUI-v5.0.0
cd FTXUI-v5.0.0
install_path=$(pwd)
cd ..

# build
cd FTXUI-src
git checkout v5.0.0 || \
  { echo "Failed to checkout v5.0.0 of FTXUI."; exit 1; }
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" ..
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }









