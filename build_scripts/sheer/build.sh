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
git clone https://github.com/shecannotsee/sheer.git ./libraries/sheer/
cd libraries
mv sheer sheer-src
mkdir sheer
cd sheer
install_path=$(pwd)
cd ..

# build
cd sheer-src
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" -Dbuild_tests=OFF ..
make -j8
make install
