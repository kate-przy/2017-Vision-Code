//
// Created by cameronearle on 1/2/17.
//

#ifndef PROJECT_THREADFLAGS_HPP
#define PROJECT_THREADFLAGS_HPP

#include <atomic>

using namespace std;


struct ThreadFlags {
    static atomic<bool> FRAME_SENDER;
    static void setAll(bool value);
};


#endif //PROJECT_THREADFLAGS_HPP
