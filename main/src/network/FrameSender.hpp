//
// Created by cameronearle on 1/2/17.
//

#ifndef PROJECT_FRAMESENDER_HPP
#define PROJECT_FRAMESENDER_HPP

#include "opencv2/core.hpp"
#include "boost/lockfree/spsc_queue.hpp"

using namespace boost::lockfree;

class FrameSender {
public:
    FrameSender(int port_) {
        port = port_;
    }
    void run();
    static void addToQueue(cv::Mat frame);
private:
    int port;
    static spsc_queue<cv::Mat> sendQueue;
};


#endif //PROJECT_FRAMESENDER_HPP
