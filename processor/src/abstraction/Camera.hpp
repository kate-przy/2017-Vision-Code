//Team 401 Vision Processing
//File: Camera.hpp
//Description: An object that abstracts things such as raw V4L operations from the user.  Can return CV and MatProvider camera reader objects
//Author: Cameron Earle

#ifndef PROJECT_CAMERA_HPP
#define PROJECT_CAMERA_HPP


#include "../utility/Configuration.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "MatProvider.hpp"
#include <string>

class Camera {
public:
    enum CameraType {
        GOAL_PROCESSING,
        GEAR_PROCESSING,
        STREAM,
        SIMPLE,
        VIRTUAL
    };
    Camera(Configuration config_, CameraType type_); //Constructor for setting up a camera from the config
    Camera(int deviceNumber_); //Constructor for setting up a camera given a device identifier
    Camera(std::string deviceId_); //Constructor for setting up a "Camera" from a video file
    bool setup();
    cv::VideoCapture getCapture(); //Method to get an OpenCV capture device
    MatProvider getProvider(); //Method to get a MatProvider
    bool setProperty(int property, int value); //Method to set V4L properties on a supported camera
    void close(); //Method to close the camera when done
private:
    cv::VideoCapture cap; //The capture device for use behind the scenes
    int v4lHandle = -1; //V4L2 Handle for changing settings.  Defaults to invalid
    MatProvider provider; //The MatProvider that is linked to our camera
    int deviceNumber; //The id of the capture device for use in setup functions
    std::string deviceId; //The "string" that holds the virtual device id for video files
    Configuration config; //A copy of the config for use around the code
    CameraType type; //A copy of the type for use around the code;
    bool isSetup = false; //A boolean to tell us whether or not the camera has been set up

    std::string ld = "Camera"; //The log descriptor
};


#endif //PROJECT_CAMERA_HPP
