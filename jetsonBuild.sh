#!/bin/bash

cp build/processor/config.txt config.temp

rm -rf build

touch *
find . -exec touch {} \;

mkdir build
cd build

cmake ..
make -j4

cd ..
cp config.temp build/processor/config.txt