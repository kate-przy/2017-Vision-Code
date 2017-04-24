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

    int H[2];
    int S[2];
    int V[2];

    int width;
    int height;

    double pitchCalculation;
    double yawCalculation;
    double horizontalDPP;
    double verticalDPP;
    double distanceCalculation;

    std::string ld = "GearProc";
};


#endif //PROJECT_GEARPROC_HPP
