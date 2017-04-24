//
// Created by cameronearle on 2/14/17.
//

#include "GearProc.hpp"
#include "../utility/Debug.hpp"
#include "../utility/Log.hpp"
#include <boost/thread/thread.hpp>

#include <opencv2/opencv.hpp>

GearProc::GearProc(Configuration config_, MatProvider *provider_, DataStreamer *streamer_) {
    config = config_;
    provider = provider_;
    streamer = streamer_;
}

using namespace std;
using namespace cv;

void GearProc::subConfig(Configuration config_) {
    Log::d(ld, "Beginning config sub");
    operativeLock.lock();
    config = config_;
    calc();
    operativeLock.unlock();
    Log::d(ld, "Config sub complete");
}

void GearProc::calc() {
    Log::d(ld, "Calculating values");
    width = provider->getSize().width;  //Convenience variables to simplify calculation statements
    height = provider->getSize().height; //Will be deleted when this method is finished
    Log::d(ld + "-CALC", "WIDTH: " + std::to_string(width) + ", HEIGHT: " + std::to_string(height));

    //HSV CALCULATIONS
    H[0] = config.gearProcHLower;
    H[1] = config.gearProcHUpper;
    S[0] = config.gearProcSLower;
    S[1] = config.gearProcSUpper;
    V[0] = config.gearProcVLower;
    V[1] = config.gearProcVUpper;
    Log::d(ld + "-CALC", "H: [" + std::to_string(H[0]) + ", " + std::to_string(H[1]) + "], S: [" + std::to_string(S[0]) +
                         ", " + std::to_string(S[1]) + "], V: [" + std::to_string(V[0]) + ", " + std::to_string(V[1]) + "]");


    //DISTANCE, PITCH, AND YAW CALCULATIONS
    distanceCalculation = config.gearProcFocalLength * 10;
    Log::d(ld + "-CALC", "DISTANCE CALCULATION: " + std::to_string(distanceCalculation));

    horizontalDPP = config.gearProcFOV/width;
    verticalDPP = config.gearProcFOV/height;

    yawCalculation = (width/2) - 0.5;
    pitchCalculation = (height/2) - 0.5;

    Log::d(ld + "-CALC", "PITCH CALC: " + std::to_string(pitchCalculation) + ", YAW CALC: " + std::to_string(yawCalculation));
    Log::d(ld, "Calculation complete!");
}

void GearProc::run() {
    Log::i(ld, "Starting!");
    calc(); //Calculate values

    // Contour lists
    vector<vector<Point>> contours, goodContours;

    // Debug image processing
    Mat goodCont, drawing;

    // Image processing
    Mat latestFrame, hsvFrame, rangeFrame;

    // Shapes and centers
    Rect rect, rect2;
    Point topLeft, bottomRight, center, topCenter, bottomCenter;

    double yaw, pitch, distance;

    // Context checks
    Rect bb;
    double area;
    double solid;
    double ratio;
    vector<Point> hull;

    while (!boost::this_thread::interruption_requested()) {
        operativeLock.lock();
        // Clears out our old contour list
        contours.clear();

        // Reads in the latest frame, converts it to HSV, and then filters out the colors we don't want
        latestFrame = provider->getLatestFrame();
        cv::cvtColor(latestFrame, hsvFrame, CV_BGR2HSV);
        cv::inRange(hsvFrame, cv::Scalar(H[0], S[0], V[0]), cv::Scalar(H[1], S[1], V[1]), rangeFrame);

        // Finds contours for our image stream
        findContours(rangeFrame, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

        // Filters the contours
        goodContours.clear();
        for (std::vector<cv::Point> currentContour: contours) {
            bb = boundingRect(currentContour);
            if (bb.width < config.gearMinWidth || bb.width > config.gearMaxWidth) continue;
            if (bb.height < config.gearMinHeight || bb.height > config.gearMaxHeight) continue;
            area = cv::contourArea(currentContour);
            if (area < config.gearMinArea) continue;
            if (arcLength(currentContour, true) < config.gearMinPerimeter) continue;
            cv::convexHull(cv::Mat(currentContour, true), hull);
            solid = 100 * area / cv::contourArea(hull);
            if (solid < config.gearMinSolidity || solid > config.gearMaxSolidity) continue;
            if (currentContour.size() < config.gearMinVertices || currentContour.size() > config.gearMaxVertices) continue;
            ratio = (double) bb.width / (double) bb.height;
            if (ratio < config.gearMinRatio || ratio > config.gearMaxRatio) continue;
            goodContours.push_back(currentContour);
        }

        // If there is a goal, do processing on it
        if (goodContours.size() >= 2) {
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
            //yaw = ((center.x - ((width / 2) - 0.5)) * horizontalDPP);
            //pitch = ((center.y - ((height / 2) - 0.5)) * verticalDPP);

            // Calculate the diagonal distance from the camera to the center of the retro reflective tape
            //distance = 10 * focalLength / (bottomCenter.y - topCenter.y);
        }
    }
}