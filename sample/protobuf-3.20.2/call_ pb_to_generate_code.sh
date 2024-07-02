#!/bin/bash
project="protobuf-3.20.2"
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

../../libraries/protobuf/bin/protoc \
  --proto_path=./ \
  --cpp_out=./protobuf \
  ./people.proto