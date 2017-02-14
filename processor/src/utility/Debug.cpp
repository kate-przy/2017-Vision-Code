//
// Created by cameronearle on 1/6/17.
//


//LCOV_EXCL_START

//These are DEBUG functions, and can't be tested in a logical way.  Therefore, they don't get to drag down our coverage.
#include "Debug.hpp"
#include <opencv2/opencv.hpp>
#include <boost/thread/thread.hpp>
#include <mutex>
#include "Log.hpp"
#include <functional>

bool Debug::showWindows = false;        //Static member initialization
bool Debug::showText = false;
bool Debug::runFunctions = false;

std::string Debug::ld = "OutWindows";

void Debug::init(Configuration config) {
    showWindows = config.showDebugWindows;
    showText = config.showDebugText;
    runFunctions = config.runDebugFunctions;
}

bool Debug::updateWindow(string windowName, cv::Mat mat) {
    if (showWindows) {
        if (!mat.empty()) { //If we can actually show the mat without the entire program crashing
            cv::imshow(windowName, mat);
            cv::waitKey(1);
        }
    }
}

void Debug::printDebugText(std::string text) {
    if (showText) {
        std::cout << text << std::endl;
    }
}

void Debug::runDebugOperation(std::function<void()> lambda) {
    if (runFunctions) {
        lambda();
    }
}

//LCOV_EXCL_STOP

