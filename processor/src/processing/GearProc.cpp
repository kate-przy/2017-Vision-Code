//
// Created by cameronearle on 2/14/17.
//

#include "GearProc.hpp"
#include <boost/thread/thread.hpp>
#include "../utility/Debug.hpp"
#include <opencv2/opencv.hpp>

GearProc::GearProc(Configuration config_, MatProvider *provider_, DataStreamer *streamer_) {
    config = config_;
    provider = provider_;
    streamer = streamer_;
}

void GearProc::run() {
    cv::Mat myMat;
    while (!boost::this_thread::interruption_requested()) {
        myMat = provider->getLatestFrame();
        Debug::updateWindow("myFunMemeton", myMat);
        Debug::printDebugText("test");
        boost::this_thread::sleep(boost::posix_time::milliseconds(10));
    }
}