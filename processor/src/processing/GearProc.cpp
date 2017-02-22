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

void GearProc::subConfig(Configuration config_) {
    operativeLock.lock();
    config = config_;
    calc();
    operativeLock.unlock();
}

void GearProc::calc() {
    //HSV CALCULATIONS
    hLower = config.gearProcHBase - config.gearProcHRange;
    sLower = config.gearProcSBase - config.gearProcSRange;
    vLower = config.gearProcVBase - config.gearProcVRange;
    hUpper = config.gearProcHBase + config.gearProcHRange;
    sUpper = config.gearProcSBase + config.gearProcSRange;
    vUpper = config.gearProcVBase + config.gearProcVRange;

    //YAW CALCULATIONS
    if ((provider->getSize().width / 2) % 2 == 0) {
        yawCalculation = (provider->getSize().width/2) * (config.gearProcFOV/provider->getSize().width);
    } else {
        yawCalculation = ((provider->getSize().width/2) - 0.5) * (config.gearProcFOV/provider->getSize().width);
    }

    //ASPECT CALCULATIONS
    aspectLower = config.gearProcAspect - config.gearProcAspectRange;
    aspectUpper = config.gearProcAspect + config.gearProcAspectRange;
}

void GearProc::run() {
    // Initializes frames
    Mat latestFrame,
        grayFrame,
        hsvFrame,
        inRangeFrame,
        erosionMat,
        imageUndistorted,
        blankFrame;

    blankFrame = Mat::zeros(provider->getSize(), provider->getType());


    // Initializes shapes
    Rect rect,
         rect2,
         selectedRect;
         //rekt

    Point center;

    // Initializes contours and a blank frame
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<int> selected;



    int w_threshold = 3;
    int h_threshold = 3;

    double yaw;

    double selectedAspect;


    // Sets up undistortion on the frame
    FileStorage fs("res/distortion.yml", FileStorage::READ);
    Mat cameraMatrix, dist;
    fs["Camera_Matrix"] >> cameraMatrix;
    fs["Distortion_Coefficients"] >> dist;

    StreamData::Strafe strafe = StreamData::Strafe::CENTER; //Variable to hold the current strafe status
    Debug::printDebugText("YAW: " + to_string(yaw) + " | STRAFE: " + to_string(strafe));

    calc(); //Pre-run calculations

    // Main loop to run code
    while (!boost::this_thread::interruption_requested()) {
        operativeLock.lock();
        //start = std::clock();
        // Resets the contours and max contours
        contours.clear();
        selected.clear();

        // Reset the blankFrame with an empty Mat if we have debug enabled
        Debug::runDebugOperation([this, &blankFrame]() {
            blankFrame = Mat::zeros(provider->getSize(), provider->getType());
        });

        // Reads in the latest frame and undistorts it
        latestFrame = provider->getLatestFrame();
        undistort(latestFrame, imageUndistorted, cameraMatrix, dist);

        // Converts color from BGR to HSV, filters out unwanted colors, erodes out noise and then finds contours
        cvtColor(imageUndistorted, hsvFrame, CV_BGR2HSV);

        inRange(hsvFrame, Scalar(hLower, sLower, vLower), Scalar(hUpper, sUpper, vUpper), inRangeFrame);

        erode(inRangeFrame, erosionMat, Mat(), Point(-1, -1), 1, 0, 1);

        findContours(erosionMat, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
        //findContours(inRangeFrame, contours, RETR_LIST, CHAIN_APPROX_SIMPLE );

        //w_threshold = 3;
        //h_threshold = 3;

        for (int i = contours.size() - 2; i < contours.size(); i++)  {
            selectedRect = boundingRect(contours[i]);
            // filter contours according to their bounding box

            selectedAspect = selectedRect.width / selectedRect.height;
            if (selectedAspect < aspectUpper && selectedAspect > aspectLower) {
                selected.push_back(i);
            }
        }

        // If we have at least two contours, find points and do math on them
        if (selected.size() >= 2) {
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

            // Calculates yaw in degrees
            // We decimal at the end is how many degrees/pixel we have
            yaw = (center.x - yawCalculation);

            // Draw and print expensive operations if debug is enabled
            Debug::runDebugOperation([this, &blankFrame, &rect, &rect2, &imageUndistorted, &center, &strafe, &yaw]() {
                rectangle(blankFrame, rect, Scalar(255, 100, 50), 1);
                rectangle(blankFrame, rect2, Scalar(0, 0, 255), 1);
                circle(blankFrame, Point(rect.x, rect.y), 2, Scalar(255, 204, 10), 2);
                circle(blankFrame, Point(rect2.x, rect2.y), 2, Scalar(255, 204, 10), 2);
                circle(imageUndistorted, center, 2, Scalar(255, 204, 10), 2);
            });

            if (abs(rect.y - rect2.y) <= 5) //Set the strafe based on our angle
                strafe = StreamData::Strafe::CENTER;
            else if (rect.x > 250)
                strafe = StreamData::Strafe::RIGHT;
            else if (rect.x < 230)
                strafe = StreamData::Strafe::LEFT;
            else
                strafe = StreamData::Strafe::CENTER;

            Debug::printDebugText("YAW: " + to_string(yaw) + " | STRAFE: " + to_string(strafe));

            streamer->addToQueue(StreamData(0, yaw, strafe));

            // Show the image if debug is enabled
        } else {
            streamer->addToQueue(StreamData(StreamData::Type::GEAR_DATA_INVALID));
        }
        Debug::updateWindow("gearLatest", imageUndistorted);
        Debug::updateWindow("gearBlank", blankFrame);
        Debug::updateWindow("gearRange", inRangeFrame);
        
        operativeLock.unlock();
        boost::this_thread::sleep(boost::posix_time::microseconds(10));
    }
}