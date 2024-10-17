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
git clone https://github.com/lua/lua.git ./libraries/lua/ || \
  { echo "Failed to clone lua repository."; exit 1; }
cd libraries
mv lua lua-src
mkdir lua-v5.3.6
cd lua-v5.3.6
install_path=$(pwd)
cd ..

# build
cd lua-src
git checkout v5.3.6 || \
  { echo "Failed to checkout v5.3.6 of lua."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
cp ./lua "$install_path"
