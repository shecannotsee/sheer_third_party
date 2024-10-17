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
git clone https://github.com/google/benchmark.git ./libraries/benchmark/ || \
  { echo "Failed to clone benchmark repository."; exit 1; }
cd libraries
mv benchmark benchmark-src
mkdir benchmark-v1.8.3
cd benchmark-v1.8.3
install_path=$(pwd)
cd ..

# build
cd benchmark-src
git checkout v1.8.3 || \
  { echo "Failed to checkout v1.8.3 of benchmark."; exit 1; }
mkdir build
cd build
cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$install_path" .. || \
  { echo "cmake failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }
