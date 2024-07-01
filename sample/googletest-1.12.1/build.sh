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
echo "Check third_party exist?"
if [ -d "./libraries" ];
then
    echo "libraries."
else
    echo "Create libraries."
fi

# get source code
git clone --branch v1.12.x --depth 1 https://github.com/google/googletest.git ./libraries/googletest/

cd libraries
mv googletest googletest-src
# build
mkdir googletest
cd googletest
path=$(pwd)
cmake -DCMAKE_INSTALL_PREFIX=./ ../googletest-src
make -j8
make install
# Delete all, except for the lib and include directories
shopt -s extglob
rm -rf !(include|lib)



