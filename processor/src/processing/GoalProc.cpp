//
// Created by cameronearle on 2/14/17.
//

#include "GoalProc.hpp"
#include "../utility/Debug.hpp"
#include "../utility/Log.hpp"
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
    Log::d(ld, "Beginning config sub");
    operativeLock.lock();
    config = config_;
    calc(); //Recalculate values
    operativeLock.unlock(); //Allow execution to resume
    Log::d(ld, "Config sub complete");
}

void GoalProc::calc() {
    Log::d(ld, "Calculating values");
    width = provider->getSize().width;  //Convenience variables to simplify calculation statements
    height = provider->getSize().height; //Will be deleted when this method is finished
    Log::d(ld + "-CALC", "WIDTH: " + std::to_string(width) + ", HEIGHT: " + std::to_string(height));

    //HSV CALCULATIONS
    H[0] = config.goalProcHLower;
    H[1] = config.goalProcHUpper;
    S[0] = config.goalProcSLower;
    S[1] = config.goalProcSUpper;
    V[0] = config.goalProcVLower;
    V[1] = config.goalProcVUpper;
    Log::d(ld + "-CALC", "H: [" + std::to_string(H[0]) + ", " + std::to_string(H[1]) + "], S: [" + std::to_string(S[0]) +
            ", " + std::to_string(S[1]) + "], V: [" + std::to_string(V[0]) + ", " + std::to_string(V[1]) + "]");


    //DISTANCE, PITCH, AND YAW CALCULATIONS
    distanceCalculation = config.goalProcFocalLength * 10;
    Log::d(ld + "-CALC", "DISTANCE CALCULATION: " + std::to_string(distanceCalculation));

    horizontalDPP = config.goalProcFOV/width;
    verticalDPP = config.goalProcFOV/height;

    yawCalculation = (width/2) - 0.5;
    pitchCalculation = (height/2) - 0.5;

    Log::d(ld + "-CALC", "PITCH CALC: " + std::to_string(pitchCalculation) + ", YAW CALC: " + std::to_string(yawCalculation));
    Log::d(ld, "Calculation complete!");
}

void GoalProc::run() {
    Log::i(ld, "Starting!");
    calc(); //Calculate values
    vector<vector<Point>> contours, goodContours;

    // Debug image processing
    Mat goodCont, drawing;

    // Image processing
    Mat latestFrame, hsvFrame, rangeFrame;

    Rect rect, rect2;
    Point topLeft, bottomRight, center, topCenter, bottomCenter;

    double yaw, pitch, distance;

    Rect bb;    //Context check variables
    double area;
    double solid;
    double ratio;
    vector<Point> hull;

    while (!boost::this_thread::interruption_requested()) {
        operativeLock.lock();
        // Clears out our old contour list
        contours.clear();

        // Reads in the latest frame, converts it to HSV, and then filters out the colors we don't want
        latestFrame = provider->getLatestFrame(); //Get the latest frame from the camera
        //latestFrame = cv::imread("/home/cameronearle/Documents/goalPhotos/straight/84.jpg");
        cv::cvtColor(latestFrame, hsvFrame, CV_BGR2HSV);
        cv::inRange(hsvFrame, cv::Scalar(H[0], S[0], V[0]), cv::Scalar(H[1], S[1], V[1]), rangeFrame);

        // Finds contours for our image stream
        findContours(rangeFrame, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

        // Filters the contours
        goodContours.clear();
        for (std::vector<cv::Point> currentContour: contours) {
            bb = boundingRect(currentContour);
            if (bb.width < config.goalMinWidth || bb.width > config.goalMaxWidth) continue;
            if (bb.height < config.goalMinHeight || bb.height > config.goalMaxHeight) continue;
            area = cv::contourArea(currentContour);
            if (area < config.goalMinArea) continue;
            if (arcLength(currentContour, true) < config.goalMinPerimeter) continue;
            cv::convexHull(cv::Mat(currentContour, true), hull);
            solid = 100 * area / cv::contourArea(hull);
            if (solid < config.goalMinSolidity || solid > config.goalMaxSolidity) continue;
            if (currentContour.size() < config.goalMinVertices || currentContour.size() > config.goalMaxVertices) continue;
            ratio = (double) bb.width / (double) bb.height;
            if (ratio < config.goalMinRatio || ratio > config.goalMaxRatio) continue;
            goodContours.push_back(currentContour);
        }

        // If there is a goal, do processing on it
        if(goodContours.size() >= 2) { //If there is the proper number of contours
            // Finds the two rectangles the goal has on it
            rect = boundingRect(goodContours[1]);
            rect2 = boundingRect(goodContours[0]);

            // Finds the top left point of the higher rectangle
            topLeft.x = rect.x;
            topLeft.y = rect.y;

            // Finds the bottom right point of the lower rectangle
            bottomRight.x = rect2.x + rect2.width;
            bottomRight.y = rect2.y + rect2.height;

            // Finds the center points
            center.x = (topLeft.x + bottomRight.x) / 2;
            center.y = (topLeft.y + bottomRight.y) / 2;
            topCenter.x = (rect.x + (rect.x + rect.width)) / 2;
            topCenter.y = (topLeft.y);
            bottomCenter.x = (rect2.x + (rect2.x + rect2.width)) / 2;
            bottomCenter.y = (bottomRight.y);

            // Calculates Yaw and Pitch in degrees
            yaw = (center.x - yawCalculation) * horizontalDPP;
            pitch = (center.y - pitchCalculation) * verticalDPP;

            // Calculate the diagonal distance from the camera to the center of the retro reflective tape
            distance = distanceCalculation / (bottomCenter.y - topCenter.y);

            streamer->addToQueue(StreamData(distance, pitch, yaw));
        } else {
            streamer->addToQueue(StreamData(StreamData::Type::GOAL_DATA_INVALID));
        }

        // Debug drawings and image streams
        Debug::runDebugOperation([this, &drawing, &latestFrame, &goodCont, &contours, &bottomCenter, &topCenter, &center,
                                         &bottomRight, &goodContours, &topLeft]() {
            // Refreshes the Mats
            drawing = cv::Mat::zeros(latestFrame.size(), CV_8UC3);
            goodCont = cv::Mat::zeros( latestFrame.size(), CV_8UC3 );

            // Draws the contours and filtered contours onto their respective Mats
            for(int i = 0; i < contours.size(); i++) {
                drawContours(drawing, contours, i, cv::Scalar(100, 100, 100));
            }
            for(int i = 0; i < goodContours.size(); i++) {
                drawContours(goodCont, goodContours, i, cv::Scalar(100,100,100));
            }

            // Draws the centers of the goal on the filtered contours
            circle(goodCont, bottomCenter, 1, cv::Scalar(255,0,255), 2);
            circle(goodCont, topCenter, 1, cv::Scalar(0,255,255), 2);
            circle(goodCont, center, 1, cv::Scalar(0,100,255), 2);

            // Draws the top left and bottom right of the goal on the filtered contours
            circle(goodCont, topLeft, 1, cv::Scalar(255,255,0), 2);
            circle(goodCont, bottomRight, 1, cv::Scalar(255,100,0), 2);

            // Draws a dot in the center of the image
            circle(goodCont, cv::Point(width/2 - 0.5, height/2 - 0.5), 1, cv::Scalar(255,255,255), 2);

        });

        Debug::printDebugText("==========YAW: " + std::to_string(yaw) + " PITCH: " + std::to_string(pitch) + " DISTANCE: "  + std::to_string(distance) + " ==========");


        Debug::updateWindow("goalContours", drawing);
        Debug::updateWindow("goalFilteredContours", goodCont);
        Debug::updateWindow("goalLatestFrame", latestFrame);

        operativeLock.unlock();
        boost::this_thread::sleep(boost::posix_time::milliseconds(1));
    }
    Log::i(ld, "Stopping!");
}