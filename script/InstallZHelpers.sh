#!/usr/bin/env bash

mkdir installDeps
cd installDeps

if [ ! -f /usr/local/include/zhelpers.hpp ]; then
git clone https://github.com/booksbyus/zguide

cd zguide/examples/C++

sudo cp zhelpers.hpp /usr/local/include

cd ../../..
else
echo "----ZHELPERS FOUND, NOT INSTALLING----"
fi

cd ..