//Team 401 Vision Processing
//File: Camera.cpp
//Description: An object that abstracts things such as raw V4L operations from the user.  Can return CV and MatProvider camera reader objects
//Author: Cameron Earle

#include <libv4l2.h>
#include <linux/videodev2.h>
#include <fcntl.h>
#include "Camera.hpp"
#include "../utility/Log.hpp"

/* Method: Camera
 * Parameter: Configuration config_: The config data to use during setup
 * Parameter: CameraType type_: The type of camera being set up (STREAM or PROCESSING)
 * Description: Set up the Camera object for a "complex" setup (from a config)
 * Returns: void
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

/* Method: Camera
 * Parameter: int deviceNumber_: The id number of the capture device to open
 * Description: Set up the Camera object for a "simple" setup, given a camera device number
 * Returns: void
 */
Camera::Camera(int deviceNumber_) {
    deviceNumber = deviceNumber_;
    type = SIMPLE;
}

/* Method: Camera
 * Parameter: std::string deviceId_: The location of the resource to use as a "virtual camera"
 * Description: Set up the Camera object with a resource location, ex. a video file
 * Returns: void
 */
Camera::Camera(std::string deviceId_)  {
    deviceId = deviceId_;
    type = VIRTUAL;
}

/* Method: setProperty
 * Parameter: int property: The V4L property ID for the property we want to change
 * Parameter: int value: The value (usually boolean) for the property we want to change
 * Description: Sets a V4L property on a VALID capture device
 * Returns: bool: Did the operation succeed?
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

/* Method: setup
 * Parameter: void
 * Description: Set up the camera object completely based on instructions from one of the constructors
 * Returns: bool: Did the setup succeed?
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

/* Method: getCapture
 * Parameter: void
 * Description: Gets the CV VideoCapture instance linked to this Camera if setup, or returns a blank instance
 * Returns: cv::VideoCapture: The capture instance
 */
cv::VideoCapture Camera::getCapture() {
    if (isSetup) { //If this camera was properly set up
        return cap; //This should be configured if the Camera was set up first
    } else {
        Log::w(ld, "Can't get a valid VideoCapture from an unconfigured Camera!  This WILL cause problems!");
        return cv::VideoCapture(); //Return a blank capture instance
    }
}

/* Method: getProvider
 * Parameter: void
 * Description: Gets the MatProvider instance linked to this Camera if setup, or returns a blank instance
 * Returns: MatProvider: The provider instance
 */
MatProvider Camera::getProvider() {
    if (isSetup) {
        return provider;
    } else {
        Log::w(ld, "Can't get a valid MatProvider from an unconfigured Camera!  This WILL cause problems!");
        return MatProvider(); //Return a blank matprovider instance
    }
}