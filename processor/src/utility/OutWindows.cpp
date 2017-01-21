//
// Created by cameronearle on 1/6/17.
//


//LCOV_EXCL_START

//These are DEBUG functions, and can't be tested in a logical way.  Therefore, they don't get to drag down our coverage.
#include "OutWindows.hpp"
#include <opencv2/opencv.hpp>
#include <boost/thread/thread.hpp>
#include <mutex>
#include "Log.hpp"

bool OutWindows::showWindows = false;        //Static member initialization
std::string OutWindows::ld = "OutWindows";

void OutWindows::init(bool showWindows_) {
    showWindows = showWindows_;
}

bool OutWindows::update(string windowName, cv::Mat mat) {
    if (showWindows) {
        cv::imshow(windowName, mat);
        cv::waitKey(1);
    }
}

//LCOV_EXCL_STOP

