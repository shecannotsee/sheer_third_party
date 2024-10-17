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
git clone https://github.com/google/googletest.git ./libraries/googletest/ || \
  { echo "Failed to clone googletest repository."; exit 1; }
cd libraries
mv googletest googletest-src
mkdir googletest-1.12.0
cd googletest-1.12.0
install_path=$(pwd)
cd ..

# build
cd googletest-src
git checkout release-1.12.0 || \
  { echo "Failed to checkout release-1.12.0 of googletest."; exit 1; }
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" .. || \
  { echo "cmake failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }
