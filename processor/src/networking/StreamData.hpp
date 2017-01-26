/**
 * Holder object for data ready to be sent over the network
 */

#ifndef PROJECT_STREAMDATA_HPP
#define PROJECT_STREAMDATA_HPP

#include <string>


class StreamData {
public:
    enum Type {
        DATA, //Default carrier, holds a full data set
        SHUTDOWN, //Currently unused on the client end, but is sent when the vision processor stops
        INVALID //Used when there is no valid data to send
    };
    StreamData(); //Constructor for invalid data
    StreamData(Type type); //Used for sending status updates such as shutdown only, DATA and INVALID types will be rejected
    StreamData(double distance, double pitch, double yaw); //Used for creating a DATA type

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
};


#endif //PROJECT_STREAMDATA_HPP
