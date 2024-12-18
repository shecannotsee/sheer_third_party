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
git clone https://github.com/json-c/json-c.git ./libraries/json-c/ || \
  { echo "Failed to clone json-c repository."; exit 1; }
cd libraries
mv json-c json-c-src
mkdir json-c-0.17
cd json-c-0.17
install_path=$(pwd)
cd ..

# build
cd json-c-src
git checkout json-c-0.17-20230812 || \
  { echo "Failed to checkout json-c-0.17-20230812 of json-c."; exit 1; }
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" .. || \
  { echo "cmake failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }
