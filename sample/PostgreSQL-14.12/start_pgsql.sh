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
if [ -d "./PostgreSQL" ];
then
    echo "PostgreSQL exist."
else
    echo "Directory [PostgreSQL] does not exist"
    exit 1 # stop
fi

# check data_store
cd PostgreSQL
if [ -d "./data_store" ];
then
    echo "data_store exist."
else
    echo "Directory [data_store] does not exist"
    exit 1 # stop
fi

# check log
if [ -d "./log" ];
then
    echo "log exist."
else
    echo "Directory [log] does not exist, create it"
    mkdir log
fi

echo "--"
./bin/pg_ctl start \
  -l ./log/log.log \
  -D ./data_store
echo "--"
