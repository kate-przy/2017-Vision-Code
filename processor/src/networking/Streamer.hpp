//
// Created by cameronearle on 1/8/17.
//

#ifndef PROJECT_STREAMER_HPP
#define PROJECT_STREAMER_HPP


#include "../abstraction/MatProvider.hpp"
#include <atomic>

class Streamer {
public:
    Streamer();
    Streamer(int port_, MatProvider provider_);
    void setCompression(int compression_);
    int getCompression();
    void run();
private:
    int port;
    MatProvider provider;
    std::atomic<int> compression;
    bool usable = false;
};


#endif //PROJECT_STREAMER_HPP
