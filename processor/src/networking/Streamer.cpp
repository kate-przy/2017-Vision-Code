/**
 * @deprecated
 */

#include "Streamer.hpp"

#include <zhelpers.hpp>
#include <opencv2/core/core.hpp>
#include <boost/thread/thread.hpp>
#include <opencv2/opencv.hpp>

/**
 * Setus up a usable streamer
 * @param port_ The port to bind to
 * @param provider_ The MatProvider to grab frames from
 */

Streamer::Streamer(int port_, MatProvider *goalProvider_, MatProvider *gearProvider_) {
    port = port_;
    goalProvider = goalProvider_;
    gearProvider = gearProvider_;
    usable = true;
    compression = 30;
    currentStreamType = GOAL;
}

/**
 * Sets up a non-usable streamer, for null init
 */
Streamer::Streamer() {
    usable = false;
}

/**
 * Updates the mode of the streamer, effective next iteration
 * @param newMode The new mode to use (enum StreamType, or int 0-2)
 */
void Streamer::setMode(int newMode) {
    currentStreamType = newMode;
}

/**
 * Sets the compression of the image encoding
 * @param compression_ The new compression value
 */
void Streamer::setCompression(int compression_) {
    if (compression_ < 0 || compression_ > 100) { //If the compression is out of bounds
        return; //Don't change anything
    }
    compression = compression_;
}

/**
 * Gets the current compression value
 * @return The current compression value
 */
int Streamer::getCompression() {
    return compression;
}

/**
 * Method to be run in a thread, streams frames over the port specified in the constructor
 */
void Streamer::run() {
    if (usable) { //If this instance is usable
        zmq::context_t context(1); //Create a context to hold our sockets
        zmq::socket_t socket(context, ZMQ_PUB); //Initialize the socket

        socket.bind("tcp://*:" + std::to_string(port)); //Connect the socket to the port given

        cv::Mat latestFrame; //The latest frame from the camera

        std::vector<uchar> buff; //A buffer to hold the jpg of the latest image
        std::vector<int> cvSettings{CV_IMWRITE_JPEG_QUALITY, getCompression()};

        while (!boost::this_thread::interruption_requested()) {
            cvSettings[1] = getCompression();
            switch (currentStreamType) {
                case GOAL:
                    latestFrame = goalProvider->getLatestFrame();
                    break;
                case GEAR:
                    latestFrame = gearProvider->getLatestFrame();
                    break;
            }
            if (!latestFrame.empty() && currentStreamType != OFF) { //If the frame isn't empty and the stream is not off
                cv::imencode(".jpg", latestFrame, buff, cvSettings); //Encode the image with compression
                s_send(socket, std::string(buff.begin(), buff.end())); //Send the image
                buff.clear(); //Clear the buffer
            }
            boost::this_thread::sleep(boost::posix_time::milliseconds(30)); //Slow down the thread a bit so we aren't sending the same image all the time
        }
    }
}