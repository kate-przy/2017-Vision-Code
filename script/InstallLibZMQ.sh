#!/usr/bin/env bash

mkdir installDeps
cd installDeps

if [ ! -f /usr/local/lib/libzmq.so ]; then
git clone https://github.com/zeromq/libzmq
cd libzmq

mkdir build
cd build

cmake ..
sudo make -j8 install

cd ../..
else
echo "----LIBZMQ FOUND, NOT INSTALLING----"
fi

cd ..