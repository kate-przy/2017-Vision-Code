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
std::vector<string> OutWindows::windowsList;
std::string OutWindows::ld = "OutWindows";

void OutWindows::init(bool showWindows_, std::vector<string> windowsList_) {
    showWindows = showWindows_;
    windowsList = windowsList_;
    for (string s : windowsList) { //For each name in the list of initial window names
        cv::namedWindow(s, CV_WINDOW_AUTOSIZE); //Create a window with the given name
    }
    boost::this_thread::sleep(boost::posix_time::seconds(1)); //Give the windows some time to initialize (window creation is non-blocking)
}

bool OutWindows::update(string windowName, cv::Mat mat) {
    if (showWindows) { //If we should show windows
        if (std::find(windowsList.begin(), windowsList.end(), windowName) != windowsList.end()) { //If the requested window was created
            cv::imshow(windowName, mat);
            return true;
        } else { //The requested window doesn't exist
            Log::e(ld, "The window [" + windowName + "] doesn't exist!");
            return false;
        }
    } else { //We shouldn't show windows
        return false;
    }
}

//LCOV_EXCL_STOP

