//Team 401 Vision Processing
//File: MatProvider.cpp
//Description: A threadable object that provides the latest image from a capture device in a non-blocking way
//Author: Cameron Earle

#include <opencv/cv.hpp>
#include "MatProvider.hpp"
#include <boost/thread/thread.hpp>
#include "../utility/Log.hpp"


/* Method: MatProvider
 * Parameter: VideoCapture cap_: The CV capture instance to use to provide the images
 * Parameter: int open: The fallback device number to use if the given cap isn't open
 * Description: Constructs a usable MatProvider that can stream images
 * Returns: void
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
    cap >> initFrame; //Capture a single frame from our capture device to get the properties
    frame = Mat::zeros(initFrame.size(), initFrame.type()); //Initialize the volatile frame with the properties of our device
    usable = true;
}

/* Method: MatProvider
 * Parameter: void
 * Description: Constructs a blank MatProvider that can't be used, used for doing initial construction in camera classes
 * Returns: void
 */
MatProvider::MatProvider() {
    usable = false;
}

/* Method: run
 * Parameter: void
 * Description: Method to be run by boost in a thread.  Reads the device and stores the frame in the "volatile" frame
 */
void MatProvider::run() {
    Log::d(ld, "Starting!");
    if (usable) {
        while (!boost::this_thread::interruption_requested()) { //While this thread should run
            cap.read(frame); //Read the data from the capture device into the volatile frame
            //NOTE: This is a blocking function, so we have a delay between iterations depending on the framerate
        }
    }
    Log::d(ld, "Stopping!");

}

/* Method: getLatestFrame
 * Parameter: void
 * Description: Grabs the latest available frame from the device, copies it (for thread safety), and returns it
 * Returns: Mat: The grabbed frame
 */
Mat MatProvider::getLatestFrame() {
    readLock.lock();
    Mat toReturn;
    if (usable) {
        toReturn =  frame.clone();
    } else {
        toReturn =  Mat();
    }
    readLock.unlock();
    return toReturn;
}

/* Method: setName
 * Parameter: std::string name_: The name to set
 * Description: Modifies the log descriptor to show which MatProvider this is
 * Returns: void
 */
void MatProvider::setName(std::string name_) {
    ld = "MatProvider-" + name_; //Update the log descriptor with the name
}