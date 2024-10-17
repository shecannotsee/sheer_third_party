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
git clone https://github.com/jtv/libpqxx.git ./libraries/libpqxx/ || \
  { echo "Failed to clone libpqxx repository."; exit 1; }
cd libraries
mv libpqxx libpqxx-src
mkdir libpqxx-7.9.0
cd libpqxx-7.9.0
install_path=$(pwd)
cd ..
# pgsql include #
cd PostgreSQL-14.12
pgsql_dir=$(pwd)
cd include
pgsql_include=$(pwd)
cd ..
cd ..
# pgsql lib
cd PostgreSQL-14.12
cd lib
pgsql_lib=$(pwd)
cd ..
cd ..
# done #

# build
cd libpqxx-src
git checkout 7.9.0 || \
  { echo "Failed to checkout 7.9.0 of libpqxx."; exit 1; }
# method 1 #
#./configure --prefix="$install_path" \
#  --enable-shared \
#  --enable-static \
#  --with-postgres-include="$pgsql_include" \
#  --with-postgres-lib="$pgsql_lib"
# 1 done #

# method 2 #
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" \
  -DPostgreSQL_ROOT="$pgsql_dir" \
  -DSKIP_BUILD_TEST=on \
  -DBUILD_SHARED_LIBS=on \
  -DBUILD_DOC=off \
  .. || \
  { echo "cmake failed."; exit 1; }
# 2 done #

make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }