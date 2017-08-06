#!/bin/bash

ARGS=$@

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

export CC=/usr/bin/gcc-5
export CXX=/usr/bin/g++-5

cd $DIR

BUILD_DEBUG="-DCMAKE_BUILD_TYPE=Debug"
BUILD_RELEASE="-DCMAKE_BUILD_TYPE=Release"

mkdir -p ./build_d
cd ./build_d
cmake -D CMAKE_C_COMPILER=/usr/bin/gcc-5 -D CMAKE_CXX_COMPILER=/usr/bin/g++-5 ${BUILD_DEBUG} ../
make -j 4

cd ..
mkdir -p ./build_r
cd ./build_r
cmake -D CMAKE_C_COMPILER=/usr/bin/gcc-5 -D CMAKE_CXX_COMPILER=/usr/bin/g++-5 ${BUILD_RELEASE} ../
make -j 4
cd ..


exit 0
