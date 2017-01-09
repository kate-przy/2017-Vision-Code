//Team 401 Vision Processor
//File: Processor.cpp
//Description: Pipeline code to do all image processing and control calculations
//Author: Liam Lawrence and Cameron Earle

#include <boost/thread/thread.hpp>
#include <opencv2/opencv.hpp>
#include "Processor.hpp"
#include "../utility/OutWindows.hpp"
#include <iostream>

/* Method: Processor
 * Parameter: Configuration config_: The configuration from the config file, used for grabbing math data
 * Parameter: MatProvider provider_: The MatProvider from main, should be initialized with a valid capture device
 * Description: Sets up the processor with the config and provider fields
 * Returns: void
 */
Processor::Processor(Configuration config_, MatProvider provider_) {
    config = config_;
    provider = provider_;
}

/* Method: run
 * Parameter: void
 * Description: Method to be run by boost to create a processing thread
 * Returns: void
 */
void Processor::run() {
    cv::Mat latestFrame;
    while (!boost::this_thread::interruption_requested()) {
        cv::waitKey(1);
        latestFrame = provider.getLatestFrame();

        OutWindows::update("Frame", latestFrame);
    }
}