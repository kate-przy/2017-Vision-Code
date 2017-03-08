/**
 * @deprecated
 */

#ifndef PROJECT_STREAMER_HPP
#define PROJECT_STREAMER_HPP


#include "../abstraction/MatProvider.hpp"
#include <atomic>

class Streamer {
public:
    enum StreamType {
        OFF = 0,
        GOAL = 1,
        GEAR = 2
    };
    Streamer();
    Streamer(int port_, MatProvider *goalProvider_, MatProvider *gearProvider_, int initialCompression = 30);
    void setMode(int newMode);
    void setCompression(int compression_);
    int getCompression();
    void run();
private:
    int port;
    MatProvider *goalProvider;
    MatProvider *gearProvider;
    std::atomic<int> compression;
    std::atomic<int> currentStreamType;
    bool usable = false;
};


#endif //PROJECT_STREAMER_HPP
