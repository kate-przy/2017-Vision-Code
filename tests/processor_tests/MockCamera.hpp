//
// Created by cameronearle on 3/30/17.
//

#ifndef PROJECT_MOCKCAMERA_HPP
#define PROJECT_MOCKCAMERA_HPP

#include "gmock/gmock.h"
#include "../../processor/src/abstraction/Camera.hpp"

class MockCamera : public Camera {
public:
    MOCK_METHOD0(setup, bool());
    MOCK_METHOD0(close, void());
    MOCK_METHOD2(setProperty, bool(int property, int value));
};

#endif //PROJECT_MOCKCAMERA_HPP
