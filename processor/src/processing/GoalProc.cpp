//
// Created by cameronearle on 2/14/17.
//

#include "GoalProc.hpp"
#include "../utility/Debug.hpp"
#include <boost/thread/thread.hpp>

#include <opencv2/opencv.hpp>


GoalProc::GoalProc(Configuration config_, MatProvider *provider_, DataStreamer *streamer_) {
    config = config_;
    provider = provider_;
    streamer = streamer_;
}

using namespace std;
using namespace cv;

void GoalProc::run() {
    // Initializes frames
    Mat latestFrame;
    Mat grayFrame;
    Mat hsvFrame;
    Mat inRangeFrame;
    Mat erosionMat;
    Mat imageUndistorted;
    Mat blankFrame = Mat::zeros(provider->getSize(), provider->getType());

    // Initializes shapes
    Rect rect;
    Rect rect2;
    Point topLeft, bottomRight, center;

    // Initializes contours and a blank frame
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    int idx = 0;
    //Mat edges = Mat::zeros(480, 640, CV_8UC3);

    // Initializes HSV values TODO Change these to what they should
    const int H = 60;
    const int S = 255;
    const int V = 170;

    double yaw;
    double pitch;

    // Sets up undistortion on the frame
    FileStorage fs("res/distortion.yml", FileStorage::READ);
    Mat cameraMatrix, dist;
    fs["Camera_Matrix"] >> cameraMatrix;
    fs["Distortion_Coefficients"] >> dist;

    // Main loop to run code
    while (!boost::this_thread::interruption_requested()) {
        // Resets the contours and max contours
        contours.clear();
        idx = 0;

        // Reset the blankFrame with an empty Mat if we have debug enabled
        Debug::runDebugOperation([this, &blankFrame]() {
            blankFrame = Mat::zeros(provider->getSize(), provider->getType());
        });

        // Reads in the latest frame and undistorts it
        latestFrame = provider->getLatestFrame();
        undistort(latestFrame, imageUndistorted, cameraMatrix, dist);

        // Converts color from BGR to HSV, filters out unwanted colors, erodes out noise and then finds contours
        cvtColor(imageUndistorted, hsvFrame, CV_BGR2HSV);

        inRange(hsvFrame, Scalar(H - 2, S - 2, V - 80), Scalar(H + 2, S + 2, V + 80), inRangeFrame);
        erode(inRangeFrame, erosionMat,  Mat(), Point(-1, -1), 1, 0, 1);

        Mat preston = Mat::zeros(provider->getSize(), provider->getType());
        imageUndistorted.copyTo(preston, erosionMat);

        findContours(erosionMat, contours, RETR_LIST, CHAIN_APPROX_SIMPLE );
        //findContours(inRangeFrame, contours, RETR_LIST, CHAIN_APPROX_SIMPLE );

        // If we have at least two contours, find points and do math on them
        if(contours.size() >= 2) {
            idx = contours.size() - 1;  // The contours we want will always be contours.size() - 1, the largest contours are biggest

            // Finds the two rectangles for each one of the strips of the tape on the boiler
            rect = boundingRect(contours[idx]);
            rect2 = boundingRect(contours[idx - 1]);

            // Finds the top left point of the higher rectangle
            topLeft.y = rect.y;
            topLeft.x = rect.x;

            // Finds the bottom right point of the lower rectangle
            bottomRight.x = rect2.x + rect2.width;
            bottomRight.y = rect2.y + rect2.height;

            // Finds the center of the rectangles
            center.x = (topLeft.x + bottomRight.x) / 2;
            center.y = (topLeft.y + bottomRight.y) / 2;

            // Calculates Yaw and Pitch in degrees
            // We decimal at the end is how many degrees/pixel we have
            yaw = ((center.x - ((640/2) - 0.5)) * 0.1171875);
            pitch = ((center.y - ((480/2) - 0.5)) * 0.15625);

            streamer->addToQueue(StreamData(0, pitch, yaw));

            // Draw and print expensive operations if debug is enabled
            Debug::runDebugOperation([this, &imageUndistorted, &center]() {
                circle(imageUndistorted, center, 2, Scalar(255, 204, 10), 2);

                //TODO 203, 223
            });
            Debug::printDebugText("YAW: " + to_string(yaw) + " | PITCH: " + to_string(pitch));
        } else {
            streamer->addToQueue(StreamData(StreamData::Type::GOAL_DATA_INVALID));
        }

        // Show the image if debug is enabled
        Debug::updateWindow("latestFrame", imageUndistorted);
        Debug::updateWindow("blank", blankFrame);
        Debug::updateWindow("range", inRangeFrame);
    }
}