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
cmake -D CMAKE_C_COMPILER=/usr/bin/gcc-5 -D CMAKE_CXX_COMPILER=/usr/bin/g++-5 ${BUILD_DEBUG} -DUSE_CUDNN=OFF -DCUDA_USE_STATIC_CUDA_RUNTIME=OFF ../
make -j 4

cd ..
mkdir -p ./build_r
cd ./build_r
cmake -D CMAKE_C_COMPILER=/usr/bin/gcc-5 -D CMAKE_CXX_COMPILER=/usr/bin/g++-5 ${BUILD_RELEASE} -DUSE_CUDNN=OFF -DCUDA_USE_STATIC_CUDA_RUNTIME=OFF  ../
make -j 4
cd ..

mkdir -p ./build_d_cudnn
cd ./build_d_cudnn
cmake -D CMAKE_C_COMPILER=/usr/bin/gcc-5 -D CMAKE_CXX_COMPILER=/usr/bin/g++-5 ${BUILD_DEBUG} -DUSE_CUDNN=ON -DCUDA_USE_STATIC_CUDA_RUNTIME=OFF  ../
make -j 4

cd ..
mkdir -p ./build_r_cudnn
cd ./build_r_cudnn
cmake -D CMAKE_C_COMPILER=/usr/bin/gcc-5 -D CMAKE_CXX_COMPILER=/usr/bin/g++-5 ${BUILD_RELEASE} -DUSE_CUDNN=ON -DCUDA_USE_STATIC_CUDA_RUNTIME=OFF  ../
make -j 4
cd ..

exit 0
