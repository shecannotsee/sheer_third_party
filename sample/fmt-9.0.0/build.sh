#!/bin/bash
project="sheer_third_party"
project_length=${#project}
# Get pwd string
cd ..
cd ..
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
git clone https://github.com/fmtlib/fmt.git ./libraries/fmt/
cd libraries
mv fmt fmt-src
mkdir fmt
cd fmt
install_path=$(pwd)
cd ..

# build
cd fmt-src
git checkout 9.0.0
mkdir build
cd build
cmake -DFMT_TEST=OFF -DCMAKE_INSTALL_PREFIX="$install_path" ..
make -j8
make install









