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
git clone https://github.com/Thalhammer/jwt-cpp.git ./libraries/jwt-cpp/ || \
  { echo "Failed to clone jwt-cpp repository."; exit 1; }
cd libraries
mv jwt-cpp jwt-cpp-src
mkdir jwt-cpp-v0.7.0
cd jwt-cpp-v0.7.0
install_path=$(pwd)
cd ..

# build
cd jwt-cpp-src
git checkout v0.7.0 || \
  { echo "Failed to checkout v0.7.0 of jwt-cpp."; exit 1; }
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" \
  -DOPENSSL_ROOT_DIR=../../../libraries/openssl-1.1.1 \
  -DOPENSSL_INCLUDE_DIR=../../../libraries/openssl-1.1.1/include \
  -DOPENSSL_CRYPTO_LIBRARY=../../../libraries/openssl-1.1.1/lib/libcrypto.so \
  -DOPENSSL_SSL_LIBRARY=../../../libraries/openssl-1.1.1/lib/libssl.so \
  -DJWT_SSL_LIBRARY=OpenSSL \
  .. || \
  { echo "cmake failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }
