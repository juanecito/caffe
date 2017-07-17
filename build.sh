#!/bin/bash

ARGS=$@

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

export CC=/usr/bin/gcc-5
export CXX=/usr/bin/g++-5

cd $DIR

mkdir -p ./build
cd ./build
cmake -D CMAKE_C_COMPILER=/usr/bin/gcc-5 -D CMAKE_CXX_COMPILER=/usr/bin/g++-5 ../
make -j 20
cd ..


exit 0
