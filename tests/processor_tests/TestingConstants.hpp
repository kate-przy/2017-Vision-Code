//
// Created by cameronearle on 3/26/17.
//

#ifndef PROJECT_CONSTANTS_HPP
#define PROJECT_CONSTANTS_HPP

#include <cstdlib>
#include <ctime>

namespace TestingConstants {

    static void setRand() {
        srand((int) std::time(0)); //Set the seed to the current time
    }
    static int randInt(int max) {
        return rand() % max;
    }

    struct Networking {
        const static int TEST_PORT;
        const static int TIMEOUT;
    };
}

#endif //PROJECT_CONSTANTS_HPP
