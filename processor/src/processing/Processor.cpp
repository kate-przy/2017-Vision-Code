//Team 401 Vision Processor
//File: Processor.cpp
//Description: Pipeline code to do all image processing and control calculations
//Author: Liam Lawrence and Cameron Earle

#include <boost/thread/thread.hpp>
#include <opencv2/opencv.hpp>
#include "Processor.hpp"
#include "../utility/OutWindows.hpp"
#include <iostream>

using namespace std;
Processor::Processor(Configuration config_, MatProvider provider_, DataStreamer *streamer_) {
    config = config_;
    provider = provider_;
    streamer = streamer_;
}


void Processor::run() {
    // Initializes frames
    Mat latestFrame;
    Mat grayFrame;
    Mat hsvFrame;
    Mat inRangeFrame;
    Mat erosionMat;
    Mat imageUndistorted;
    Mat blankFrame = Mat::zeros(480, 640, CV_8UC3);

    // Initializes shapes
    Rect rect;
    Rect rect2;
    Rect bounding_rect;
    Point topLeft, bottomRight, center;

    // Initializes contours and a blank frame
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    int idx = 0;
    Mat edges = Mat::zeros(480, 640, CV_8UC3);

    // Initializes HSV values TODO Change these to what they should
    const int H = 60;
    const int S = 255;
    const int V = 164;

    // Initializes math, angle, and distance calculations
    double kTopTargetHeightIn = 87.5;    // The top of the tape is 97" from the ground
    double kCameraHeightIn = 18.2;       // Camera is 18.2" from the ground
    double kCameraPitchDeg = 23.6;       // Angle camera is tilted up
    double PI = 3.141592653;
    double kVerticalFOVDeg = /*(480.0 / 640.0 * 56);*/ (75 / 0.75);
    double y;
    double distance;
    double yaw;
    double pitch;

    // Sets up undistortion on the frame
    FileStorage fs("res/distortion.yml", FileStorage::READ);
    Mat cameraMatrix, dist;
    fs["Camera_Matrix"] >> cameraMatrix;
    fs["Distortion_Coefficients"] >> dist;

    cout << cameraMatrix << endl;

    // Main loop to run code
    while (!boost::this_thread::interruption_requested()) {
        // Resets the contours and max contours
        contours.clear();
        idx = 0;

        // Reset the blankFrame with an empty Mat if we have debug enabled
        blankFrame = Mat::zeros(480, 640, CV_8UC3);

        // Reads in the latest frame and undistorts it
        latestFrame = provider.getLatestFrame();
        undistort(latestFrame, imageUndistorted, cameraMatrix, dist);

        // Converts color from BGR to HSV, filters out unwanted colors, erodes out noise and then finds contours
        cvtColor(imageUndistorted, hsvFrame, CV_BGR2HSV);
        inRange(hsvFrame, Scalar(H - 5, S - 5, V - 20), Scalar(H + 5, S + 5, V + 20), inRangeFrame);
        erode(inRangeFrame, erosionMat,  Mat(), Point(-1, -1), 1, 0, 1);
        findContours(erosionMat, contours, RETR_LIST, CHAIN_APPROX_SIMPLE );

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

            // Used for math
            y = (topLeft.y + bottomRight.y) / 2;
            y = -((2 * (y / 480)) - 1);

            //4.5 because the tube is 4.5" from the front plane of the goal
            distance = 4.5 + (kTopTargetHeightIn - kCameraHeightIn) / tan((y * kVerticalFOVDeg / 2.0 + kCameraPitchDeg) * PI / 180.0);

            // Draw and print expensive operations if debug is enabled
            if(config.showDebugText){
                rectangle(imageUndistorted, topLeft, bottomRight, cv::Scalar(255, 204, 0), 1);
                circle(imageUndistorted, center, 2, cv::Scalar(255, 204, 10), 2);
                drawContours(blankFrame, contours,idx, Scalar( 0, 0, 255 ), 3 );
                drawContours(blankFrame, contours,idx - 1, Scalar( 0, 0, 255 ), 3 );

                cout << endl << "YAW: " << yaw << " | PITCH: " << pitch << endl;
                cout << "DISTANCE: " << distance << " inches" << endl;
            }
            streamer->addToQueue(StreamData(distance, pitch, yaw)); //Pushed a valid data blob
        } else {
            streamer->addToQueue(StreamData()); //Push an invalid data blob
        }


        // Show the image if debug is enabled
        OutWindows::update("latestFrame", imageUndistorted);
        OutWindows::update("blank", blankFrame);
    }
}