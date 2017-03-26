//Team 401 Vision Processing
//File: MatProvider.cpp
//Description: A threadable object that provides the latest image from a capture device in a non-blocking way
//Author: Cameron Earle

//LCOV_EXCL_START
//This class is tested by hardware tests, and is thus not a valid representation of coverage

#include <opencv/cv.hpp>
#include "MatProvider.hpp"
#include <boost/thread/thread.hpp>
#include "../utility/Log.hpp"


/**
 * Sets up a usable MatProvider from a CV capture instance
 * @param cap_ The CV capture instance to use when creating the MatProvider
 * @param open The fallback address to use should the CV capture device not be open already
 */
MatProvider::MatProvider(VideoCapture cap_, int open) {
    cap = cap_;
    Mat initFrame; //An initial frame for grabbing some properties about our capture device
    if (!cap.isOpened()) { //If the capture device is not already open
        Log::d(ld, "Capture device isn't already opening, using fallback [" + to_string(open) + "]");
        if (!cap.open(open)) { //If we can't open the "fallback device"
            Log::e(ld, "Can't open fallback device [" + to_string(open) + "].  This MatProvider is unusable!");
            usable = false; //Mark this instance as unusable
            return; //Break execution here
        }
    }
    cap.read(initFrame); //Capture a single frame from our capture device to get the properties
    size = initFrame.size();
    type = initFrame.type();
    frame = Mat::zeros(size, type); //Initialize the volatile frame with the properties of our device
    usable = true;
}

/**
 * Sets up a non-usable MatProvider, for initialization purposes only.  This constructor should never be directly run.
 */
MatProvider::MatProvider() {
    usable = false;
}

/**
 * Method to be run in a thread, reads frames into the volatile frame
 */
void MatProvider::run() {
    Log::d(ld, "Starting!");
    if (usable) {
        while (!boost::this_thread::interruption_requested()) { //While this thread should run
            cap.read(frame); //Read the data from the capture device into the volatile frame
            //NOTE: This is a blocking function, so we have a delay between iterations depending on the framerate
        }
    }
    cap.release(); //Release the capture device so other system resources can use it
    Log::d(ld, "Stopping!");

}

/**
 * Gets the latest frame from this MatProvider, assuming it is usable and running
 * @return The Mat from the capture device
 */
Mat MatProvider::getLatestFrame() {
    Mat toReturn;
    if (usable) {
        toReturn = frame.clone();
    } else {
        toReturn = Mat::zeros(480, 640, CV_8UC3); //Return a blank mat of a standard size
    }
    return toReturn;
}

/**
 * Gets the size of the source of frames
 * @return The size
 */
Size MatProvider::getSize() {
    return size;
}

/**
 * Gets the type of the source of frames
 * @return The type
 */
int MatProvider::getType() {
    return type;
}

/**
 * Sets the name of this MatProvider, for logging purposes
 * @param name_ The name to set
 */
void MatProvider::setName(std::string name_) {
    ld = "MatProvider-" + name_; //Update the log descriptor with the name
}

//LCOV_EXCL_STOP