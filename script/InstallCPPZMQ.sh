#!/usr/bin/env bash

mkdir installDeps
cd installDeps

if [ ! -f /usr/local/include/zmq.hpp ]; then
git clone https://github.com/zeromq/cppzmq

cd cppzmq

sudo cp zmq.hpp /usr/local/include
sudo cp zmq_addon.hpp /usr/local/include

cd ..
else
echo "----CPPZMQ FOUND, NOT INSTALLING----"
fi

cd ..