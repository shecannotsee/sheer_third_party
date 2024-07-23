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
git clone https://github.com/postgres/postgres.git ./libraries/PostgreSQL/
cd libraries
mv PostgreSQL PostgreSQL-src
mkdir PostgreSQL
cd PostgreSQL
install_path=$(pwd)
cd ..

# build
cd PostgreSQL-src
git checkout REL_14_12
./configure --prefix="$install_path"
make -j8
make install









