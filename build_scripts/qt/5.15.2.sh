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
git clone git://code.qt.io/qt/qt5.git ./libraries/qt5/
cd libraries
mv qt5 qt5-src
mkdir qt5
mkdir qt5-build
cd qt5
install_path=$(pwd)
cd ..

# build
cd qt5-src
git checkout 5.15.2
git submodule update --init --recursive
cd ..

echo "https://shecannotsee.github.io/qt-install.html"
read go
echo "$go"

cd qt5-build
../qt5-src/configure -developer-build -opensource -nomake examples -nomake tests -skip qtdocgallery -prefix "$install_path"
make -j8
make install
