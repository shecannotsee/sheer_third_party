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
git clone https://github.com/llvm/llvm-project.git ./libraries/llvm-project/ || \
  { echo "Failed to clone llvm-project repository."; exit 1; }
cd libraries
mv llvm-project llvm-project-src
mkdir llvm-project-19.1.6
cd llvm-project-19.1.6
install_path=$(pwd)
cd ..

# build
cd llvm-project-src
git checkout llvmorg-19.1.6 || \
  { echo "Failed to checkout llvmorg-19.1.6 ofllvm-project."; exit 1; }


################################# llvm install #################################
# ../llvm-project-src/llvm
cd llvm
mkdir build
# ../llvm-project-src/llvm/build
cd build
cmake -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="$install_path" \
  .. || \
  { echo "cmake failed."; exit 1; }

make -j10 || \
  { echo "make failed."; exit 1; }
make install || \
  { echo "make install failed."; exit 1; }

# ../llvm-project-src/llvm
cd ..
# ../llvm-project-src
cd ..

################################# clang install #################################
# ../llvm-project-src/clang
cd clang
mkdir build
# ../llvm-project-src/clang/build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" \
  -DLLVM_DIR="$install_path"/lib/cmake/llvm \
  -DLLVM_INCLUDE_TESTS=OFF \
  .. || \
  { echo "cmake failed."; exit 1; }


