//Team 401 Vision Processing
//File: MatProvider.hpp
//Description: A threadable object that provides the latest image from a capture device in a non-blocking way
//Author: Cameron Earle

#ifndef PROJECT_MATPROVIDER_HPP
#define PROJECT_MATPROVIDER_HPP

#include <atomic>
#include "opencv2/videoio/videoio.hpp"
#include <string>
#include <mutex>

using namespace cv;

class MatProvider {
public:
    MatProvider(VideoCapture cap_, int open=0); //Constructor for setting the videocapture
    MatProvider(); //"null" constructor
    void run(); //Method to run the thread
    Mat getLatestFrame(); //Method to get the latest frame from the device using a "deep copy"
    Size getSize(); //Method to get the size of the frames from the camera
    int getType(); //Method to get the type of the frames from the camera

    void setName(std::string name_);
private:
    VideoCapture cap; //The capture device to use
    Size size; //The size of the camera
    int type; //The type of the camera
    Mat frame; //The volatile frame that will contain data pulled from the capture device
    bool usable; //Has the MatProvider been constructed properly?

    std::string ld = "MatProvider"; //The log descriptor
};


#endif //PROJECT_MATPROVIDER_HPP
