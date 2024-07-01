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
git clone https://github.com/chriskohlhoff/asio.git ./libraries/asio/

cd libraries
mv asio asio-src
# build
mkdir asio
cd asio
install_path=$(pwd)
cd ..

cd asio-src
git checkout asio-1-12-branch
cd asio
./autogen.sh
./configure --prefix="$install_path" --without-boost
make -j8
make install







