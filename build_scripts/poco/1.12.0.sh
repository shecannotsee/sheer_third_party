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
git clone https://github.com/pocoproject/poco.git ./libraries/poco/ || \
  { echo "Failed to clone poco repository."; exit 1; }
cd libraries
mv poco poco-src
mkdir poco-1.12.0
cd poco-1.12.0
install_path=$(pwd)
cd ..

# build
cd poco-src
git checkout poco-1.12.0-release || \
  { echo "Failed to checkout poco-1.12.0-release of poco."; exit 1; }
./configure --prefix="$install_path" --no-tests || \
  { echo "configure failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }
