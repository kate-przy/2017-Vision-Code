//
// Created by cameronearle on 2/14/17.
//

#ifndef PROJECT_GEARPROC_HPP
#define PROJECT_GEARPROC_HPP


#include "../utility/Configuration.hpp"
#include "../abstraction/MatProvider.hpp"
#include "../networking/DataStreamer.hpp"
#include "Processor.hpp"

#include <mutex>

class GearProc : public Processor {
public:
    GearProc(Configuration config_, MatProvider *provider_, DataStreamer *streamer_);
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

    double yawCalculation;

    double aspectLower;
    double aspectUpper;
};


#endif //PROJECT_GEARPROC_HPP
