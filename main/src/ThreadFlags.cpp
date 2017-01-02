//
// Created by cameronearle on 1/2/17.
//

#include "ThreadFlags.hpp"

atomic<bool> ThreadFlags::FRAME_SENDER(true);

void ThreadFlags::setAll(bool value) {
    FRAME_SENDER = value;
}