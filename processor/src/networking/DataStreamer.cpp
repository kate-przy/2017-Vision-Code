//
// Created by cameronearle on 1/20/17.
//

#include <zhelpers.hpp>
#include "DataStreamer.hpp"
#include "DataBlob.hpp"
#include <boost/thread/thread.hpp>

DataStreamer::DataStreamer(int port_) : sendQueue(512) {
    port = port_;
}

void DataStreamer::addToQueue(DataBlob blob) {
    sendQueue.push(blob);
}

void DataStreamer::run() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUB);
    socket.bind("tcp://*:" + std::to_string(port)); //Connect to the socket
    DataBlob latestBlob;
    while (!boost::this_thread::interruption_requested()) {
        while (sendQueue.pop(latestBlob)) {
            s_send(socket, latestBlob.hash());
            std::cout << "send" << std::endl;
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(10));
        std::cout << "wait" << std::endl;
    }
}