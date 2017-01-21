//
// Created by cameronearle on 1/20/17.
//

#ifndef PROJECT_DATASTREAMER_HPP
#define PROJECT_DATASTREAMER_HPP

#include <boost/lockfree/queue.hpp>
#include "DataBlob.hpp"

class DataStreamer {
public:
    DataStreamer(int port_);
    void run();
    void addToQueue(DataBlob blob);
private:
    int port;
    boost::lockfree::queue<DataBlob> sendQueue;
};


#endif //PROJECT_DATASTREAMER_HPP
