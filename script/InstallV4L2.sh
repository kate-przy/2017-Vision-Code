#!/usr/bin/env bash

mkdir installDeps
cd installDeps

sudo apt-get -y install v4l-utils
sudo apt-get -y install qv4l2

cd ..