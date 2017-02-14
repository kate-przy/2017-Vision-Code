//
// Created by cameronearle on 1/6/17.
//

//LCOV_EXCL_START

//These are DEBUG functions, and can't be tested in a logical way.  Therefore, they don't get to drag down our coverage.
#ifndef PROJECT_OUTWINDOWS_HPP
#define PROJECT_OUTWINDOWS_HPP

#include "Configuration.hpp"
#include <opencv2/core/mat.hpp>
#include <string>
#include <queue>
#include <mutex>
#include <functional>

class Debug {
public:
    static void init(Configuration config);
    static bool updateWindow(std::string windowName, cv::Mat mat);
    static void printDebugText(std::string text);
    static void runDebugOperation(std::function<void()> lambda);
private:
    static bool showWindows;
    static bool showText;
    static bool runFunctions;
    static std::string ld;
};


#endif //PROJECT_OUTWINDOWS_HPP

//LCOV_EXCL_STOP
