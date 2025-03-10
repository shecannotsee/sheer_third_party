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
git clone https://github.com/metayeti/mINI.git ./libraries/mINI/ || \
  { echo "Failed to clone mINI repository."; exit 1; }
cd libraries
mv mINI mINI-src
mkdir mINI-0.9.16
cd mINI-0.9.16
install_path=$(pwd)
cd ..

# build
cd mINI-src
git checkout 0.9.16 || \
  { echo "Failed to checkout 0.9.16 of glog."; exit 1; }
mkdir -p "${install_path}/include/mini"
cp ./src/mini/ini.h "${install_path}/include/mini"

