/**
 * Object to be run in a thread that queues StreamData and sends it as soon as possible
 * @warning This class must NOT BE COPIED!  It contains instance sensitive data, and must be passed BY REFERENCE
 */

#ifndef PROJECT_DATASTREAMER_HPP
#define PROJECT_DATASTREAMER_HPP

#include <boost/lockfree/queue.hpp>
#include "StreamData.hpp"

class DataStreamer {
public:
    DataStreamer(int port_); //Constructor to set the port in which to bind a TCP socket on
    void run(); //Method to be run by a threading engine
    void addToQueue(StreamData data); //Method to add StreamData to the queue, which will proceed to be sent, assuming the thread is running
private:
    int port; //The port to bind to (ZMQ requires single thread sockets, so the socket is created and connected in run()
    boost::lockfree::queue<StreamData> sendQueue; //The instance sensitive queue to hold incoming data
};


#endif //PROJECT_DATASTREAMER_HPP
