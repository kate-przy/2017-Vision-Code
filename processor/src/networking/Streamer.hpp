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
    virtual void setMode(int newMode);
    virtual void setCompression(int compression_);
    int getCompression();
    virtual void run();
    virtual ~Streamer() {};
private:
    int port;
    MatProvider *goalProvider;
    MatProvider *gearProvider;
    std::atomic<int> compression;
    std::atomic<int> currentStreamType;
    bool usable = false;
};


#endif //PROJECT_STREAMER_HPP
