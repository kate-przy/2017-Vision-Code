/**
 * Object to be run in a thread that queues StreamData and sends it as soon as possible
 * @warning This class must NOT BE COPIED!  It contains instance sensitive data, and must be passed BY REFERENCE
 */

#include <zhelpers.hpp>
#include "DataStreamer.hpp"
#include <boost/thread/thread.hpp>

/**
 * Constructor for setting up the object to be run in a thread.
 * Initialized the queue, and then sets the port
 * @param port_ The port to set
 */
DataStreamer::DataStreamer(int port_) : sendQueue(512) {
    port = port_;
}

/**
 * Adds elements to the queue, which will be sent assuming the thread is running
 * @param data The StreamData to be added to the queue
 */
void DataStreamer::addToQueue(StreamData data) {
    sendQueue.push(data);
}

/**
 * Method to be run in a thread that streams data from the queue
 * until there is no data left.  Terminates when interrupt() is called
 * on the thread
 */
void DataStreamer::run() {
    zmq::context_t context(1); //Set up a ZMQ context to hold the socket
    zmq::socket_t socket(context, ZMQ_PUB); //Initialize a TCP publisher socket
    socket.bind("tcp://*:" + std::to_string(port)); //Connect to the socket
    StreamData latestData; //Null object to hold the latest data from the queue
    while (!boost::this_thread::interruption_requested()) { //While this thread should run
        while (sendQueue.pop(latestData)) { //Store the latest data from the queue into latestData
            s_send(socket, latestData.hash()); //Send the latest data hashed
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(10)); //Keep the CPU happy
    }
    socket.close(); //Close the socket and terminate the thread
}