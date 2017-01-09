//Team 401 Vision Processor
//File: Processor.hpp
//Description: Pipeline code to do all image processing and control calculations
//Author: Liam Lawrence and Cameron Earle

#ifndef PROJECT_PROCESSOR_HPP
#define PROJECT_PROCESSOR_HPP


#include "../utility/Configuration.hpp"
#include "../abstraction/Camera.hpp"

class Processor {
public:
    Processor(Configuration config_, MatProvider provider_); //Constructor for passing needed data
    void run(); //Method to run the thread
private:
    Configuration config;

    MatProvider provider;
};
#endif //PROJECT_PROCESSOR_HPP
