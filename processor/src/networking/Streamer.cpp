//
// Created by cameronearle on 1/8/17.
//

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
Streamer::Streamer(int port_, MatProvider provider_) {
    port = port_;
    provider = provider_;
    usable = true;
    compression = 30;
}

/**
 * Sets up a non-usable streamer, for null init
 */
Streamer::Streamer() {
    usable = false;
}

/**
 * Sets the compression of the image encoding
 * @param compression_ The new compression value
 */
void Streamer::setCompression(int compression_) {
    if (compression_ < 0 || compression_ > 100) { //If the compression is out of bounds
        std::cout << "not changing" << std::endl;
        return; //Don't change anything
    }
    compression = compression_;
    std::cout << "new compression: " << compression << std::endl;
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

        while (!boost::this_thread::interruption_requested()) {
            latestFrame = provider.getLatestFrame();
            if (!latestFrame.empty()) { //If the frame isn't empty
                std::cout << "current compression: " << getCompression() << std::endl;
                cv::imencode(".jpg", latestFrame, buff, std::vector<int>{CV_IMWRITE_JPEG_QUALITY, getCompression()}); //Encode the image with compression
                s_send(socket, std::string(buff.begin(), buff.end())); //Send the image
                buff.clear(); //Clear the buffer
            }
            boost::this_thread::sleep(boost::posix_time::milliseconds(30)); //Slow down the thread a bit so we aren't sending the same image all the time
        }
    }
}