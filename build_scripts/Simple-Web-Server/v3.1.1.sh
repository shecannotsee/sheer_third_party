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
git clone https://gitlab.com/eidheim/Simple-Web-Server.git ./libraries/Simple-Web-Server/
cd libraries
mv Simple-Web-Server Simple-Web-Server-src
mkdir Simple-Web-Server-v3.1.1
cd Simple-Web-Server-v3.1.1
install_path=$(pwd)
cd ..

# build
cd Simple-Web-Server-src
git checkout v3.1.1
mkdir build
cd build
# set boost install dir
cmake -DBOOST_ROOT=/home/shecannotsee/Desktop/sheer_third_party/libraries/boost-1.79.0 -DCMAKE_INSTALL_PREFIX="$install_path" ..
make -j8
make install
