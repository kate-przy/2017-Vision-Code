//
// Created by cameronearle on 2/14/17.
//

#ifndef PROJECT_GOALPROC_HPP
#define PROJECT_GOALPROC_HPP


#include "../utility/Configuration.hpp"
#include "../abstraction/MatProvider.hpp"
#include "../networking/DataStreamer.hpp"

#include <mutex>

class GoalProc {
public:
    GoalProc(Configuration config_, MatProvider *provider_, DataStreamer *streamer_);
    void run();
    void subConfig(Configuration config_);
private:
    Configuration config;
    MatProvider *provider;
    DataStreamer *streamer;
    std::mutex operativeLock;
    void calc();

    int hLower;
    int sLower;
    int vLower;
    int hUpper;
    int sUpper;
    int vUpper;

    double pitchCalculation;
    double yawCalculation;

    double aspectLower;
    double aspectUpper;
};


#endif //PROJECT_GOALPROC_HPP
