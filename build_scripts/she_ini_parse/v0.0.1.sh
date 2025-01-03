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
git clone https://github.com/shecannotsee/she_ini_parse.git ./libraries/she_ini_parse/ || \
  { echo "Failed to clone she_ini_parse repository."; exit 1; }
cd libraries
# build third_party
cd she_ini_parse
./scripts/googletest-1.12.1_build.sh
cd ..
# build done.

mv she_ini_parse she_ini_parse-src
mkdir she_ini_parse-v0.0.1
cd she_ini_parse-v0.0.1
install_path=$(pwd)
cd ..

# build
cd she_ini_parse-src
git checkout v0.0.1 || \
  { echo "Failed to checkout v0.0.1 of she_ini_parse."; exit 1; }
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" .. || \
  { echo "cmake failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }
cp -r ./she_ini_parse/* "$install_path"
