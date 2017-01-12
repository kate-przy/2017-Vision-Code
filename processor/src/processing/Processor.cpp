//Team 401 Vision Processor
//File: Processor.cpp
//Description: Pipeline code to do all image processing and control calculations
//Author: Liam Lawrence and Cameron Earle

#include <boost/thread/thread.hpp>
#include <opencv2/opencv.hpp>
#include "Processor.hpp"
#include "../utility/OutWindows.hpp"
#include <iostream>


Processor::Processor(Configuration config_, MatProvider provider_) {
    config = config_;
    provider = provider_;
}


void Processor::run() {
    cv::Mat latestFrame;
    while (!boost::this_thread::interruption_requested()) {
        cv::waitKey(1);
        latestFrame = provider.getLatestFrame();

        OutWindows::update("Frame", latestFrame);
    }
}