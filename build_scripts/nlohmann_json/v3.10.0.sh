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
git clone https://github.com/nlohmann/json.git ./libraries/nlohmann_json/ || \
  { echo "Failed to clone nlohmann_json repository."; exit 1; }
cd libraries
mv nlohmann_json nlohmann_json-src
mkdir nlohmann_json-v3.10.0
cd nlohmann_json-v3.10.0
install_path=$(pwd)
cd ..

# build
cd nlohmann_json-src
git checkout v3.10.0 || \
  { echo "Failed to checkout v3.10.0 of nlohmann_json."; exit 1; }
mkdir build
cd build
cmake -DJSON_BuildTests=OFF -DCMAKE_INSTALL_PREFIX="$install_path" .. || \
  { echo "cmake failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }
