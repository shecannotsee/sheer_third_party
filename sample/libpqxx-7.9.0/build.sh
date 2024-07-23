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
git clone https://github.com/jtv/libpqxx.git ./libraries/libpqxx/
cd libraries
mv libpqxx libpqxx-src
mkdir libpqxx
cd libpqxx
install_path=$(pwd)
cd ..
# pgsql include #
cd PostgreSQL
cd include
pgsql_include=$(pwd)
cd ..
cd ..
# pgsql lib
cd PostgreSQL
cd lib
pgsql_lib=$(pwd)
cd ..
cd ..
# done #

# build
cd libpqxx-src
git checkout 7.9.0
./configure --prefix="$install_path" \
  --enable-shared \
  --enable-static \
  --with-postgres-include="$pgsql_include" \
  --with-postgres-lib="$pgsql_lib"
make -j8
make install









