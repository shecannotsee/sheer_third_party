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
git clone https://github.com/shecannotsee/she_log.git ./libraries/she_log/
cd libraries
# build third_party
cd she_log
./scripts/third_party_she_test_build.sh
cd ..
# build done.

mv she_log she_log-src
mkdir she_log
cd she_log
install_path=$(pwd)
cd ..

# build
cd she_log-src
git checkout v0.0.1
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" ..
make -j8
make install
cp -r ./she_log/* "$install_path"
