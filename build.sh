#!/bin/bash

ARGS=$@

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $DIR

mkdir -p ./build
cd ./build
cmake ../
make
cd ..


exit 0
