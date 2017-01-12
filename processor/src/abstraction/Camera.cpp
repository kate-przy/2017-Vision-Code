//Team 401 Vision Processing
//File: Camera.cpp
//Description: An object that abstracts things such as raw V4L operations from the user.  Can return CV and MatProvider camera reader objects
//Author: Cameron Earle

#include <libv4l2.h>
#include <linux/videodev2.h>
#include <fcntl.h>
#include "Camera.hpp"
#include "../utility/Log.hpp"

/**
 * Sets up a camera from a config file, given a type
 * @param config_ The config object to read from
 * @param type_ The type of camera to use
 */
Camera::Camera(Configuration config_, CameraType type_) {
    assert(type_ != VIRTUAL); //Some checks to ensure that we don't use the wrong constructor
    assert(type_ != SIMPLE);
    config = config_;
    type = type_;
    switch (type_) {
        case PROCESSING:
            deviceNumber = config.procDeviceNumber;
            break;
        case STREAM:
            deviceNumber = config.streamDeviceNumber;
            break;
        default:
            deviceNumber = 0; //This is a safe assumption for a production environment
            break;
    }
}

/**
 * Setus up a camera from a device number
 * @param deviceNumber_ The device number to use
 */
Camera::Camera(int deviceNumber_) {
    deviceNumber = deviceNumber_;
    type = SIMPLE;
}

/**
 * Sets up a virtual camera from a video file
 * @param deviceId_ The file path to read the video file from
 */
Camera::Camera(std::string deviceId_)  {
    deviceId = deviceId_;
    type = VIRTUAL;
}

/**
 * Sets a V4L property on a supported capture device
 * @param property The property that should be set
 * @param value The value to set the property to
 * @return true if the operation succeded, false if the device is not supported or the operation failed
 */
bool Camera::setProperty(int property, int value) {
    if (type != VIRTUAL) { //If the camera is not virtual (video file)
        int descriptor = v4l2_open(("/dev/video" + std::to_string(deviceNumber)).c_str(), O_RDWR); //A number that linux uses to reference the camera object

        v4l2_control c; //A video4linux control that we will use to change a specific setting
        c.id = property; //Set the control property to our property
        c.value = value; //Set the control value to our value

        bool success = v4l2_ioctl(descriptor, VIDIOC_S_CTRL, &c) == 0; //Run the operation and see if it succeeds
        if (success) { //If the operation succeeded
            Log::i(ld, "Set property [" + std::to_string(property) + "] to value [" + std::to_string(value) + "] on device [" + std::to_string(deviceNumber) + "]");
            return true; //NOTE: This is not just "return success;" because we may want to add additional (log) functions later
        } else { //The operation didn't succeed
            Log::e(ld, "Failed to set property [" + std::to_string(property) + "] to value [" + std::to_string(value) + "] on device [" + std::to_string(deviceNumber) + "]");
            return false;
        }
    } else { //The camera is virtual
        Log::e(ld, "Can't set properties on a virtual device!");
        return false;
    }
}

/**
 * Sets up the camera based on its type and, if applicable, properties from a config
 * @return true if the setup succeeded, false if the operation failed
 */
bool Camera::setup() {
    bool validity = true;
    switch (type) {
        case PROCESSING:
            //TODO INSERT SET PROPERTIES FROM CONFIG HERE
            break;
        case STREAM:
            //TODO INSERT SET PROPERTIES FROM CONFIG HERE
            break;
    }
    if (type == VIRTUAL) {
        if (!cap.open(deviceId)) { //Try to open the capture device, if it fails:
            Log::x(ld, "Can't open the VIRTUAL capture resource [" + deviceId + "].  Operation can't continue!");
            exit(1); //If the resource can't be opened, kill the program now to prevent problems later
        }
        if (validity) { //If nothing has failed up to this point
            provider = MatProvider(cap, -1); //Initialize the matprovider with an invalid fallback device number, since this is a virtual capture device
            Log::i(ld, "Setup complete on VIRTUAL capture resource [" + deviceId + "]");
        } else {
            Log::w(ld, "Issues were encountered setting up VIRTUAL capture resource [" + deviceId + "]"); //This shouldn't ever happen
        }
    } else {
        if (!cap.open(deviceNumber)) { //Try to open the capture device, it it fails:
            Log::x(ld, "Can't open the capture device [" + std::to_string(deviceNumber) + "].  Operation can't continue!");
            exit(1); //If the resource can't be opened, kill the program now to prevent problems later
        }
        if (validity) { //If nothing has failed up to this point
            provider = MatProvider(cap, deviceNumber); //Initialize the matprovider with the fallback number in case opening somehow failed earlier
            Log::i(ld, "Setup complete on capture device [" + std::to_string(deviceNumber) + "]");
        } else {
            Log::w(ld, "Issues were encountered setting up capture device [" + std::to_string(deviceNumber) + "]");
        }
    }
    //At this point, setup should be complete
    isSetup = validity; //If everything worked properly, the setup is complete
    return validity; //Tell the caller what happened
}

/**
 * Gets an OpenCV VideoCapture instance from this camera
 * @return The CV capture instance
 */
cv::VideoCapture Camera::getCapture() {
    if (isSetup) { //If this camera was properly set up
        return cap; //This should be configured if the Camera was set up first
    } else {
        Log::w(ld, "Can't get a valid VideoCapture from an unconfigured Camera!  This WILL cause problems!");
        return cv::VideoCapture(); //Return a blank capture instance
    }
}

/**
 * Gets the MatProvider instance associated with this camera, which should be started in a thread before use
 * @return The MatProvider instance
 */
MatProvider Camera::getProvider() {
    if (isSetup) {
        return provider;
    } else {
        Log::w(ld, "Can't get a valid MatProvider from an unconfigured Camera!  This WILL cause problems!");
        return MatProvider(); //Return a blank matprovider instance
    }
}