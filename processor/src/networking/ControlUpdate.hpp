//
// Created by cameronearle on 1/9/17.
//

#ifndef PROJECT_CONTROLUPDATE_HPP
#define PROJECT_CONTROLUPDATE_HPP

#include "Streamer.hpp"
#include "../abstraction/Camera.hpp"

class ControlUpdate {
public:
    ControlUpdate(Streamer *streamer_, int port_);
    void run();
private:
    Streamer *streamer; //This MUST be a pointer, because it contains atomics, so it CANNOT be copied.  This will use the original reference in the main function
                        //However, it does NOT have to be deleted, since it was never allocated with "new".  Therefore, the runtime is responsible for deletion
                        //when the original goes out of scope (ex. end of program)
    int port;
};


#endif //PROJECT_CONTROLUPDATE_HPP
