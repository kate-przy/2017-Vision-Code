#!/usr/bin/env bash

# DEPENDENCY INSTALL #
sudo apt-add-repository -y universe
sudo apt-add-repository -y multiverse
sudo apt-get update
sudo apt-get -y install libopencv-dev build-essential cmake git libgtk2.0-dev pkg-config python-dev python-numpy libdc1394-22 libdc1394-22-dev libjpeg-dev libpng12-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev libtbb-dev libqt4-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils libtiff5-dev libxine2-dev unzip

./script/InstallBoost.sh
./script/InstallOpenCV.sh
./script/InstallLibZMQ.sh
./script/InstallCPPZMQ.sh
./script/InstallZHelpers.sh
./script/InstallV4L2.sh

sudo ldconfig