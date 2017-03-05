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
    int width = provider->getSize().width;  //Convenience variables to simplify calculation statements
    int height = provider->getSize().height; //Will be deleted when this method is finished

    //HSV CALCULATIONS
    H[0] = config.goalProcHLower;
    H[1] = config.goalProcHUpper;
    S[0] = config.goalProcSLower;
    S[1] = config.goalProcSUpper;
    V[0] = config.goalProcVLower;
    V[1] = config.goalProcVUpper;

    //DISTANCE, PITCH, AND YAW CALCULATIONS
    distanceCalculation = config.goalProcFocalLength * 10;

    if ((height / 2) % 2 == 0) { //If height/2 is even
        pitchCalculation = (height / 2) * (config.goalProcFOV/height); //Find the center
    } else {
        pitchCalculation = ((height / 2) - 0.5) * (config.goalProcFOV/height); //Find the actual center
    }

    if ((width / 2) % 2 == 0) { //If width/2 is even
        yawCalculation = (width / 2) * (config.goalProcFOV/width); //Find the center
    } else {
        yawCalculation = ((width / 2) - 0.5) * (config.goalProcFOV/width); //Find the actual center
    }
}

void GoalProc::run() {
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
        //Clear variables from last run
        contours.clear();
        goodContours.clear();
        hull.clear();

        // Reads in the latest frame, converts it to HSV, and then filters out the colors we don't want
        latestFrame = provider->getLatestFrame();
        cvtColor(latestFrame, hsvFrame, CV_BGR2HSV);
        inRange(hsvFrame, Scalar(H[0], S[0], V[0]), Scalar(H[1], S[1], V[1]), rangeFrame);

        // Finds contours for our image stream
        findContours(rangeFrame, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

        //CONTEXT CHECKING
        for (std::vector<cv::Point> contour: contours) { //Iterate each contour
            bb = boundingRect(contour);
            if (bb.width < config.goalMinWidth || bb.width > config.goalMaxWidth) continue;
            if (bb.height < config.goalMinHeight || bb.height > config.goalMaxHeight) continue;
            area = cv::contourArea(contour);
            if (area < config.goalMinArea) continue;
            if (arcLength(contour, true) < config.goalMinPerimeter) continue;
            cv::convexHull(cv::Mat(contour, true), hull);
            solid = 100 * area / cv::contourArea(hull);
            if (solid < config.goalMinSolidity || solid > config.goalMaxSolidity) continue;
            if (contour.size() < config.goalMinVertices || contour.size() > config.goalMaxVertices)	continue;
            ratio = (double) bb.width / (double) bb.height;
            if (ratio < config.goalMinRatio || ratio > config.goalMaxRatio) continue;
            goodContours.push_back(contour);
        }

        // If there is a goal, do processing on it
        if(goodContours.size() >= 2) {
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
            yaw = (center.x - yawCalculation);
            pitch = (center.y - pitchCalculation);

            // Calculate the x distance away from the goal the robot is (not diagonal)
            distance = distanceCalculation / (bottomCenter.y - topCenter.y);

            streamer->addToQueue(StreamData(distance, pitch, yaw)); //Send the data
        } else {
            streamer->addToQueue(StreamData(StreamData::Type::GOAL_DATA_INVALID)); //Send invalid data
        }

        // Debug drawings and image streams
        Debug::runDebugOperation([this, &drawing, &latestFrame, &goodCont, &contours, &goodContours, &bottomCenter, &topCenter, &center, &topLeft, &bottomRight](){
            // Refreshes the Mats
            drawing = Mat::zeros(latestFrame.size(), CV_8UC3);
            goodCont = Mat::zeros( latestFrame.size(), CV_8UC3 );

            // Draws the contours and filtered contours onto their respective Mats
            for (int i = 0; i < contours.size(); i++){
                drawContours(drawing, contours, i, Scalar(100, 100, 100));
            }
            for( int i = 0; i< goodContours.size(); i++ ){
                drawContours(goodCont, goodContours, i, Scalar(100,100,100));
            }

            // Draws the centers of the goal on the filtered contours
            circle(goodCont, bottomCenter, 1, Scalar(255,0,255), 2);
            circle(goodCont, topCenter, 1, Scalar(0,255,255), 2);
            circle(goodCont, center, 1, Scalar(0,100,255), 2);

            // Draws the top left and bottom right of the goal on the filtered contours
            circle(goodCont, topLeft, 1, Scalar(255,255,0), 2);
            circle(goodCont, bottomRight, 1, Scalar(255,100,0), 2);

            // Draws a dot in the center of the image
            circle(goodCont, Point(480/2 -0.5, 640/2-0.5), 1, Scalar(255,255,255), 2);
        });

        Debug::updateWindow("goalFilteredContours", goodCont);
        Debug::updateWindow("goalContours", drawing);

        operativeLock.unlock();
        boost::this_thread::sleep(boost::posix_time::microseconds(10));
    }
}