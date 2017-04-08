//
// Created by cameronearle on 3/31/17.
//

#ifndef PROJECT_MOCKPROCESSOR_HPP
#define PROJECT_MOCKPROCESSOR_HPP

#include "gmock/gmock.h"
#include "../../processor/src/processing/Processor.hpp"
#include "../../processor/src/utility/Configuration.hpp"

class MockProcessor : public Processor {
public:
    MOCK_METHOD0(run, void());
    MOCK_METHOD1(subConfig, void(Configuration config_));
};


#endif //PROJECT_MOCKPROCESSOR_HPP
