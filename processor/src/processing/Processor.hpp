//
// Created by cameronearle on 3/30/17.
//

#ifndef PROJECT_PROCESSOR_HPP
#define PROJECT_PROCESSOR_HPP

#include "../utility/Configuration.hpp"

//A base class for processors to be derived off of, used for mocking mostly

class Processor {
public:
    virtual void run() {}
    virtual void subConfig(Configuration config_) {}
    virtual ~Processor() {}
protected:
    Processor() {} //Prevent instantiation
};

#endif //PROJECT_PROCESSOR_HPP
