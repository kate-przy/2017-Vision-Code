//
// Created by cameronearle on 3/30/17.
//

#ifndef PROJECT_PROCESSOR_HPP
#define PROJECT_PROCESSOR_HPP

#include "../utility/Configuration.hpp"

//A base class for processors to be derived off of, used for mocking mostly

//LCOV_EXCL_START
//This is a base class and has no functionality
//It also can't be instantiated, so it is untestable

class Processor {
public:
    virtual void run() {}
    virtual void subConfig(Configuration config_) {}
    virtual ~Processor() {}
protected:
    Processor() {} //Prevent instantiation
};

#endif //PROJECT_PROCESSOR_HPP
//LCOV_EXCL_STOP