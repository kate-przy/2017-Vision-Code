/**
 * Holder object for data ready to be sent over the network
 */

#include <assert.h>
#include "StreamData.hpp"

/**
 * Null constructor, sets up this instance as an "invalid" object
 */
StreamData::StreamData() {
    thisType = Type::INVALID;
}

/**
 * Constructor for setting up command types such as SHUTDOWN
 * @param type The type of command, must not be DATA or INVALID
 */
StreamData::StreamData(Type type) {
    assert(type != Type::DATA); //Ensure we get the correct type
    assert(type != Type::INVALID);

    thisType = type;
}

/**
 * Constructor for setting up a data container
 * @param distance The distance to set
 * @param pitch The pitch to set
 * @param yaw The yaw to set
 */
StreamData::StreamData(double distance, double pitch, double yaw) {
    thisType = Type::DATA;
    thisDistance = distance;
    thisPitch = pitch;
    thisYaw = yaw;
}

/**
 * Hashes the data contained in this instance into a routable string
 * Example hash with data:
 * "DATA#distance:123.4123,pitch:342.3854,yaw:254.78257"
 * @return The routable string
 */
std::string StreamData::hash() {
    std::string returnString;
    switch (thisType) {
        case INVALID:
            returnString = "INVALID#";
            break;
        case SHUTDOWN:
            returnString = "SHUTDOWN#";
            break;
        case DATA:
            returnString = "DATA#"
                    + ("distance:" + std::to_string(thisDistance)) + ","
                    + ("pitch:" + std::to_string(thisPitch)) + ","
                    + ("yaw:" + std::to_string(thisYaw))
                    ;
            break;
    }
    return returnString;
}