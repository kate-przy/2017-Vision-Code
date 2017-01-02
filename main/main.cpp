//
// Created by cameronearle on 12/25/16.
//

#include <opencv2/videoio.hpp>
#include <cv.hpp>
#include "src/SayHello.hpp"

#include "boost/thread/thread.hpp"
#include "src/network/FrameSender.hpp"
#include "src/ThreadFlags.hpp"

int main() {
    SayHello::sayHello();

    FrameSender frameSender(5800);

    cv::VideoCapture cap;
    cap.open(0);

    //cap.set(CV_CAP_PROP_FPS, 60);


    boost::thread frameSenderThread(boost::bind(&FrameSender::run, frameSender));

    cv::Mat currentFrame;
    cv::namedWindow("Frame", CV_WINDOW_AUTOSIZE);

    while (true) {
        if (cv::waitKey(1) == 27) {
            break;
        }
        cap >> currentFrame;
        FrameSender::addToQueue(currentFrame);
        cv::imshow("Frame", currentFrame);
    }

    ThreadFlags::setAll(false);
}