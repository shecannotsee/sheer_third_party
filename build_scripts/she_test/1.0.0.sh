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
git clone https://github.com/shecannotsee/she_test.git ./libraries/she_test/
cd libraries
mv she_test she_test-src
mkdir she_test-1.0.0
cd she_test-1.0.0
install_path=$(pwd)
cd ..

# build
cd she_test-src
git checkout 1.0.0 || \
  { echo "git checkout failed."; exit 1; }
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" \
  -Dbuild_release=ON \
  -Dbuild_tests=OFF \
  -Dbuild_shared_libs=ON \
  .. || \
  { echo "cmake failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }
