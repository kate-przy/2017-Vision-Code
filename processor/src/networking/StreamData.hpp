/**
 * Holder object for data ready to be sent over the network
 */

#ifndef PROJECT_STREAMDATA_HPP
#define PROJECT_STREAMDATA_HPP

#include <string>


class StreamData {
public:
    enum Type {
        GOAL_DATA, //Carrier for goal finding data
        GEAR_DATA, //Carrier for gear target data
        GOAL_DATA_INVALID, //Carrier for invalid goal data
        GEAR_DATA_INVALID, //Carrier for invalid gear data
        SHUTDOWN, //Currently unused on the client end, but is sent when the vision processor stops
        INVALID //Used when there is no valid data to send, will force set all data to invalid on the client side
    };
    enum Strafe {
        LEFT = -1,
        CENTER = 0,
        RIGHT = 1
    };
    StreamData(); //Constructor for invalid data
    StreamData(Type type); //Used for sending invalid types or shutdown signals, all other values will be rejected
    StreamData(double distance, double pitch, double yaw); //Used for creating a GOAL_DATA type
    StreamData(double distance, double yaw, Strafe strafe); //Used for creating a GEAR_DATA type

    /**
     * Gets the type of the current instance
     * @return The type of the current instance
     */
    Type getType() {
        return thisType;
    }

    std::string hash(); //Hashes the current object into a sendable string
private:
    Type thisType; //The type of packet

    //DATA VALUES
    double thisDistance;
    double thisPitch;
    double thisYaw;
    Strafe thisStrafe;
};


#endif //PROJECT_STREAMDATA_HPP
