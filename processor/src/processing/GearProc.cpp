//
// Created by cameronearle on 2/14/17.
//

#include "GearProc.hpp"
#include <boost/thread/thread.hpp>
#include "../utility/Debug.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

GearProc::GearProc(Configuration config_, MatProvider *provider_, DataStreamer *streamer_) {
    config = config_;
    provider = provider_;
    streamer = streamer_;
}

void GearProc::run() {
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
    Point rectangleOne, rectangleTwo, center;

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

    string turn;

    // Main loop to run code
    while (!boost::this_thread::interruption_requested()) {
        //start = std::clock();
        // Resets the contours and max contours
        contours.clear();
        idx = 0;

        // Reset the blankFrame with an empty Mat if we have debug enabled
        Debug::runDebugOperation([this, &blankFrame]() {
            blankFrame = Mat::zeros(provider->getSize(), provider->getType());
        });

        // Reads in the latest frame and undistorts it
        latestFrame = provider->getLatestFrame();
        //latestFrame = imread("/home/and3212/Desktop/yay.png");
        undistort(latestFrame, imageUndistorted, cameraMatrix, dist);

        // Converts color from BGR to HSV, filters out unwanted colors, erodes out noise and then finds contours
        cvtColor(imageUndistorted, hsvFrame, CV_BGR2HSV);

        inRange(hsvFrame, Scalar(H - 2, S - 2, V - 80), Scalar(H + 2, S + 2, V + 80), inRangeFrame);
        erode(inRangeFrame, erosionMat, Mat(), Point(-1, -1), 1, 0, 1);

        Mat preston = Mat::zeros(480, 640, CV_8UC3);
        imageUndistorted.copyTo(preston, erosionMat);

        findContours(erosionMat, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
        //findContours(inRangeFrame, contours, RETR_LIST, CHAIN_APPROX_SIMPLE );

        int w_threshold = 3;
        int h_threshold = 3;
        vector<int> selected;
        for (int i = contours.size() - 2; i < contours.size(); i++) {
            Scalar color = Scalar(0, 255, 0);
            Rect R = boundingRect(contours[i]);
            // filter contours according to their bounding box
            if (R.width > w_threshold && R.height > h_threshold) {
                selected.push_back(i);
                cout << i << endl;
                cout << selected[i] << endl;
            }
        }

        // If we have at least two contours, find points and do math on them
        if (contours.size() >= 2 && selected.size() >= 2) {
            //idx = contours.size() - 1;  // The contours we want will always be contours.size() - 1, the largest contours are biggest


            // Finds the two rectangles for each one of the strips of the tape on the boiler
            rect = boundingRect(contours[selected[0]]); //(const _InputArray &) adds an extra millisecond of run time
            rect2 = boundingRect(contours[selected[1]]);

            // Finds the top left point of the higher rectangle
            // rectangleOne.y = rect.y;
            // rectangleOne.x = rect.x;

            // Finds the bottom right point of the lower rectangle
            // rectangleTwo.x = rect2.x;
            // rectangleTwo.y = rect2.y;

            // Finds the center of the rectangles
            center.x = (rect.x + rect2.x) / 2;
            center.y = (rect.y + rect2.y) / 2;

            // Calculates Yaw and Pitch in degrees
            // We decimal at the end is how many degrees/pixel we have
            yaw = ((center.x - ((640 / 2) - 0.5)) * 0.1171875);
            pitch = ((center.y - ((480 / 2) - 0.5)) * 0.15625);


            // Draw and print expensive operations if debug is enabled
            Debug::runDebugOperation([this, &blankFrame, &rect, &rect2, &imageUndistorted, &center, &turn, &yaw, &pitch]() {
                rectangle(blankFrame, rect, Scalar(255, 100, 50), 1);
                rectangle(blankFrame, rect2, Scalar(0, 0, 255), 1);
                circle(blankFrame, Point(rect.x, rect.y), 2, Scalar(255, 204, 10), 2);
                circle(blankFrame, Point(rect2.x, rect2.y), 2, Scalar(255, 204, 10), 2);

                circle(imageUndistorted, center, 2, Scalar(255, 204, 10), 2);


                if (abs(rect.y - rect2.y) <= 5)
                    turn = "None";
                else if (rect.x > 250)
                    turn = "Right";
                else if (rect.x < 230)
                    turn = "Left";
                else
                    turn = "ERROR";

                cout << endl << "YAW: " << yaw << " | PITCH: " << pitch << " | TURN: " << turn << endl;
            });


            // Show the image if debug is enabled
        }
        Debug::updateWindow("gearLatest", imageUndistorted);
        Debug::updateWindow("gearBlank", blankFrame);
        Debug::updateWindow("gearRange", inRangeFrame);
    }
}