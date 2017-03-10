#!/bin/bash

rsync -avP --exclude=cmake-build-debug ./ ubuntu@cobra-vision.local:/home/ubuntu/2017-Vision-Code/ #upload files
ssh ubuntu@cobra-vision.local 'bash -c "cd /home/ubuntu/2017-Vision-Code && mkdir -p build && cd build && cmake .. && make -j4"' #build stuff
rsync -avP ./cmake-build-debug/processor/targetConfig.txt ubuntu@cobra-vision.local:/home/ubuntu/2017-Vision-Code/build/processor/config.txt #copy new config
ssh ubuntu@cobra-vision.local 'screen -X -S vision quit || true && screen -dmS vision bash -c "cd /home/ubuntu/2017-Vision-Code/build/processor && ./start.sh" && echo DONE' #restart vision
