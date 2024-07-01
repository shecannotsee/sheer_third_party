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
git clone https://github.com/openssl/openssl.git ./libraries/openssl/
cd libraries
mv openssl openssl-src
mkdir openssl
cd openssl
install_path=$(pwd)
cd ..

# build
cd openssl-src
git checkout OpenSSL_1_1_1
./config --prefix="$install_path" --openssldir="$install_path"/ssl
make -j8
make install









