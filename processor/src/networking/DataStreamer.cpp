/**
 * Object to be run in a thread that queues StreamData and sends it as soon as possible
 * @warning This class must NOT BE COPIED!  It contains instance sensitive data, and must be passed BY REFERENCE
 */

#include <zhelpers.hpp>
#include "DataStreamer.hpp"
#include "../utility/Log.hpp"
#include <boost/thread/thread.hpp>

/**
 * Constructor for setting up the object to be run in a thread.
 * Initialized the queue, and then sets the port
 * @param port_ The port to set
 */
DataStreamer::DataStreamer(int port_) : sendQueue(512) {
    port = port_;
    counter = 0;
}

/**
 * Adds elements to the queue, which will be sent assuming the thread is running
 * @param data The StreamData to be added to the queue
 */
void DataStreamer::addToQueue(StreamData data) {
    sendQueue.push(data);
    counter++;
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
        if (counter > 10) {
            sendQueue.empty();
            std::cout << "CLEARING!" << std::endl;
        }
        while (sendQueue.pop(latestData)) { //Store the latest data from the queue into latestData
            counter--;
            s_send(socket, latestData.hash()); //Send the latest data hashed
            Log::d(ld, "Sent Data: [" + latestData.hash() + "]");
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(1)); //Keep the CPU happy
    }
    socket.close(); //Close the socket and terminate the thread
}