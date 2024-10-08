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
    echo "path ok"
else
    echo "Path error.Please ensure that the last few strings after using pwd are "$project
    exit 1  # stop
fi
# check dir libraries
echo "Check libraries exist..."
if [ -d "./libraries" ];
then
    echo "libraries exist."
else
    echo "Directory [libraries] does not exist"
    exit 1 # stop
fi

# check PostgreSQL
cd libraries
echo "Check libraries exist..."
if [ -d "./sqlite-3.45.0" ];
then
    echo "sqlite-3.45.0 exist."
else
    echo "Directory [sqlite-3.45.0] does not exist"
    exit 1 # stop
fi

# init
cd sqlite-3.45.0/bin

echo "--"
./sqlite3 test.db
./sqlite3 test.db < createTable.sql
echo "--"
