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
git clone https://github.com/shecannotsee/she_log.git ./libraries/she_log/ || \
  { echo "Failed to clone she_log repository."; exit 1; }
cd libraries
# build third_party
cd she_log
./scripts/third_party_she_test_build.sh
cd ..
# build done.

mv she_log she_log-src
mkdir she_log-v0.0.1
cd she_log-v0.0.1
install_path=$(pwd)
cd ..

# build
cd she_log-src
git checkout v0.0.1 || \
  { echo "Failed to checkout v0.0.1 of she_log."; exit 1; }
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" .. || \
  { echo "cmake failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }

cp -r ./she_log/* "$install_path"
