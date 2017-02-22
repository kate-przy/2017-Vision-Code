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

void GoalProc::subConfig(Configuration config_) {
    operativeLock.lock();
    config = config_;
    calc(); //Recalculate values
    operativeLock.unlock(); //Allow execution to resume
}

void GoalProc::calc() {
    //HSV CALCULATIONS
    hLower = config.goalProcHBase - config.goalProcHRange;
    sLower = config.goalProcSBase - config.goalProcSRange;
    vLower = config.goalProcVBase - config.goalProcVRange;
    hUpper = config.goalProcHBase + config.goalProcHRange;
    sUpper = config.goalProcSBase + config.goalProcSRange;
    vUpper = config.goalProcVBase + config.goalProcVRange;

    //PITCH AND YAW CALCULATIONS
    if ((provider->getSize().height / 2) % 2 == 0) {
        pitchCalculation = (provider->getSize().height/2) * (config.goalProcFOV/provider->getSize().height);
    } else {
        pitchCalculation = ((provider->getSize().height/2) - 0.5) * (config.goalProcFOV/provider->getSize().height);
    }

    if ((provider->getSize().width / 2) % 2 == 0) {
        yawCalculation = (provider->getSize().width/2) * (config.goalProcFOV/provider->getSize().width);
    } else {
        yawCalculation = ((provider->getSize().width/2) - 0.5) * (config.goalProcFOV/provider->getSize().width);
    }

    //ASPECT CALCULATIONS
    aspectLower = config.goalProcAspect - config.goalProcAspectRange;
    aspectUpper = config.goalProcAspect + config.goalProcAspectRange;
}

void GoalProc::run() {
    // Initializes frames
    Mat latestFrame,
        grayFrame,
        hsvFrame,
        inRangeFrame,
        erosionMat,
        imageUndistorted,
        blankFrame,
        edges;

    blankFrame = Mat::zeros(provider->getSize(), provider->getType());
    edges = Mat::zeros(provider->getSize(), provider->getType());

    // Initializes shapes
    Rect rect,
         rect2;

    Point topLeft,
          bottomRight,
          center;

    // Initializes contours and a blank frame
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    int idx = 0; //The index of the largest contour

    // Initializes HSV values TODO Change these to what they should

    double yaw;
    double pitch;

    // Sets up undistortion on the frame
    FileStorage fs("res/distortion.yml", FileStorage::READ);
    Mat cameraMatrix, dist;
    fs["Camera_Matrix"] >> cameraMatrix;
    fs["Distortion_Coefficients"] >> dist;

    calc(); //Run all pre-calculations

    // Main loop to run code
    while (!boost::this_thread::interruption_requested()) {
        operativeLock.lock(); //Start a cycle
        // Resets the contours and max contours
        contours.clear();

        // Reset the blankFrame with an empty Mat if we have debug enabled
        Debug::runDebugOperation([this, &blankFrame]() {
            blankFrame = Mat::zeros(provider->getSize(), provider->getType());
        });

        // Reads in the latest frame and undistorts it
        latestFrame = provider->getLatestFrame();
        undistort(latestFrame, imageUndistorted, cameraMatrix, dist);

        // Converts color from BGR to HSV, filters out unwanted colors, erodes out noise and then finds contours
        cvtColor(imageUndistorted, hsvFrame, CV_BGR2HSV);

        inRange(hsvFrame, Scalar(hLower, sLower, vLower), Scalar(hUpper, sUpper, vUpper), inRangeFrame); //Find data in the configured hsv range

        erode(inRangeFrame, erosionMat,  Mat(), Point(-1, -1), 1, 0, 1);

        findContours(erosionMat, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

        //TODO LIAM WRITE ASPECT RATIO CODE RIGHT NOW YOU SCUM

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
            yaw = (center.x - yawCalculation);
            pitch = (center.y - pitchCalculation);

            streamer->addToQueue(StreamData(0, pitch, yaw)); //Send our data to the RIO

            // Draw and print expensive operations if debug is enabled
            Debug::runDebugOperation([this, &imageUndistorted, &center]() {
                circle(imageUndistorted, center, 2, Scalar(255, 204, 10), 2);
            });
            Debug::printDebugText("YAW: " + to_string(yaw) + " | PITCH: " + to_string(pitch));
        } else {
            streamer->addToQueue(StreamData(StreamData::Type::GOAL_DATA_INVALID));
        }

        // Show the image if debug is enabled
        Debug::updateWindow("latestFrame", imageUndistorted);
        Debug::updateWindow("blank", blankFrame);
        Debug::updateWindow("range", inRangeFrame);

        operativeLock.unlock(); //Complete a cycle
        boost::this_thread::sleep(boost::posix_time::microseconds(10)); //Give any substitution operations time to complete
    }
}