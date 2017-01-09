//
// Created by cameronearle on 1/8/17.
//

#ifndef PROJECT_STREAMER_HPP
#define PROJECT_STREAMER_HPP


#include "../abstraction/MatProvider.hpp"
#include <mutex>

class Streamer {
public:
    Streamer(int port_, MatProvider provider_);
    void setCompression(int compression_);
    void run();
private:
    int port;
    MatProvider provider;
    Mutex compressionModifyMutex;
    int compression = 30;
};


#endif //PROJECT_STREAMER_HPP
