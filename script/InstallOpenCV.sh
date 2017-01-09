#!/usr/bin/env bash

mkdir installDeps
cd installDeps

if [ ! -f /usr/local/lib/libopencv_core.so.3.1 ]; then #If the opencv >3.1< core module isn't there
wget https://github.com/Itseez/opencv/archive/3.1.0.zip

unzip -qq 3.1.0.zip
cd opencv-3.1.0

mkdir build
cd build

cmake -DWITH_CUDA=ON -DCUDA_ARCH_BIN="3.2" -DCUDA_ARCH_PTX="" -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF ..
sudo make -j$(nproc) install

cd ../..
else
echo "----OPENCV FOUND, NOT INSTALLING----"
fi

cd ..