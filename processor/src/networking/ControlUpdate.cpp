//
// Created by cameronearle on 1/9/17.
//
#include "ControlUpdate.hpp"

#include <string>

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <boost/thread/thread.hpp>
#include <zhelpers.hpp>

ControlUpdate::ControlUpdate(Streamer *streamer_, int port_) {
    streamer = streamer_;
    port = port_;
}

void ControlUpdate::run() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.setsockopt(ZMQ_RCVTIMEO, 10);
    socket.bind("tcp://*:" + std::to_string(port));

    std::string recvData;
    int changeNumber;
    while (!boost::this_thread::interruption_requested()) {
        recvData = s_recv(socket); //Get the request from the client
        if (recvData != "") { //If the request didn't time out
            if (recvData != "init") { //If this isn't a request for initial value
                changeNumber = std::stoi(recvData);
                std::cout << std::stoi(recvData) << std::endl;
                streamer->setCompression(changeNumber); //Change the compression to the new number
            }
            s_send(socket, std::to_string(streamer->getCompression())); //Return the current compression
        }
    }
    std::cout << "ctrlupdate stopping" << std::endl;
    socket.close(); //Close the socket
}