/**
 * Holder object for data ready to be sent over the network
 */

#include <assert.h>
#include "StreamData.hpp"
#include <string>

/**
 * Null constructor, sets up this instance as an "invalid" object
 */
StreamData::StreamData() {
    thisType = Type::INVALID;
}

/**
 * Compares two StreamData objects
 * @param data The data to compare against this instance
 * @return True if the data is the same, false if it is not
 */
bool StreamData::operator==(const StreamData data) {
    if (data.thisType != thisType) { //If the types are different
        return false; //The data is different
    }
    
    switch (data.thisType) { //If the data is a valid type, do a comparision on the fields
        case GOAL_DATA:
            return (data.thisDistance == thisDistance &&
                    data.thisPitch == thisPitch &&
                    data.thisYaw == thisYaw);
        case GEAR_DATA:
            return (data.thisDistance == thisDistance &&
                    data.thisYaw == thisYaw &&
                    data.thisStrafe == thisStrafe);
    }
    return true; //The data must be invalid, and we know the types match, so they are the same
}

/**
 * Compares two StreamData objects
 * @param data The data to compare against this instance
 * @return True if the data is different, false if it is not
 */
bool StreamData::operator!=(const StreamData data) {
    return !operator==(data); //Return the opposite of the == operator
}

/**
 * Constructor for setting up command types such as SHUTDOWN
 * @param type The type of command, must not be DATA or INVALID
 */
StreamData::StreamData(Type type) {
    assert(type != Type::GOAL_DATA); //Ensure we get the correct type
    assert(type != Type::GEAR_DATA);
    assert(type != Type::INVALID);

    thisType = type;
}

/**
 * Constructor for setting up a goal data container
 * @param distance The distance to set
 * @param pitch The pitch to set
 * @param yaw The yaw to set
 */
StreamData::StreamData(double distance, double pitch, double yaw) {
    thisType = Type::GOAL_DATA;
    thisDistance = distance;
    thisPitch = pitch;
    thisYaw = yaw;
}

/**
 * Constructor for setting up a gear data container
 * @param distance The distance to set
 * @param yaw The yaw to set
 * @param strafe The strafe enum to set
 */
StreamData::StreamData(double distance, double yaw, Strafe strafe) {
    thisType = Type::GEAR_DATA;
    thisDistance = distance;
    thisYaw = yaw;
    thisStrafe = strafe;
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
        case GOAL_DATA:
            returnString = "GOAL_DATA#"
                    + ("distance:" + std::to_string(thisDistance)) + ","
                    + ("pitch:" + std::to_string(thisPitch)) + ","
                    + ("yaw:" + std::to_string(thisYaw))
                    ;
            break;
        case GEAR_DATA:
            returnString = "GEAR_DATA#"
                    + ("distance" + std::to_string(thisDistance)) + ","
                    + ("yaw:" + std::to_string(thisYaw)) + ","
                    + ("strafe:" + std::to_string(thisStrafe));
            break;
        case GOAL_DATA_INVALID:
            returnString = "GOAL_DATA_INVALID#";
            break;
        case GEAR_DATA_INVALID:
            returnString = "GEAR_DATA_INVALID#"; // THIS COULD HAVE BEEN PONIES
            break;
    }
    return returnString;
}