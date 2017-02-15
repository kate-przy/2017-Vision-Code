//
// Created by cameronearle on 2/14/17.
//

#ifndef PROJECT_GEARPROC_HPP
#define PROJECT_GEARPROC_HPP


#include "../utility/Configuration.hpp"
#include "../abstraction/MatProvider.hpp"
#include "../networking/DataStreamer.hpp"

class GearProc {
public:
    GearProc(Configuration config_, MatProvider *provider_, DataStreamer *streamer_);
    void run();
private:
    Configuration config;
    MatProvider *provider;
    DataStreamer *streamer;
};


#endif //PROJECT_GEARPROC_HPP
