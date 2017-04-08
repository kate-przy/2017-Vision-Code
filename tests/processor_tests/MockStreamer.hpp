//
// Created by cameronearle on 3/31/17.
//

#ifndef PROJECT_MOCKSTREAMER_HPP
#define PROJECT_MOCKSTREAMER_HPP

#include "../../processor/src/networking/Streamer.hpp"
#include "gmock/gmock.h"

class MockStreamer : public Streamer {
public:
    MOCK_METHOD0(run, void());
    MOCK_METHOD1(setMode, void(int mode));
    MOCK_METHOD1(setCompression, void(int compression));
};

#endif //PROJECT_MOCKSTREAMER_HPP
