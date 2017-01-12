//
// Created by cameronearle on 1/6/17.
//

//LCOV_EXCL_START

//These are DEBUG functions, and can't be tested in a logical way.  Therefore, they don't get to drag down our coverage.
#ifndef PROJECT_OUTWINDOWS_HPP
#define PROJECT_OUTWINDOWS_HPP

#include <opencv2/core/mat.hpp>
#include <string>
#include <queue>
#include <mutex>

class OutWindows {
public:
    static void init(bool showWindows_);
    static bool update(std::string windowName, cv::Mat mat);
private:
    static bool showWindows;

    static std::string ld;
};


#endif //PROJECT_OUTWINDOWS_HPP

//LCOV_EXCL_STOP
