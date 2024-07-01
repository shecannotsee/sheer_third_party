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
git clone https://github.com/nlohmann/json.git ./libraries/nlohmann_json/
cd libraries
mv nlohmann_json nlohmann_json-src
mkdir nlohmann_json
cd nlohmann_json
install_path=$(pwd)
cd ..

# build
cd nlohmann_json-src
git checkout v3.10.0
mkdir build
cd build
cmake -DJSON_BuildTests=OFF -DCMAKE_INSTALL_PREFIX="$install_path" ..
make -j8
make install









