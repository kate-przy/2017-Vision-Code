//
// Created by cameronearle on 1/20/17.
//

#ifndef PROJECT_DATABLOB_HPP
#define PROJECT_DATABLOB_HPP

struct DataBlob {
    DataBlob(double distance_, double pitch_, double yaw_) {
        distance = distance_;
        pitch = pitch_;
        yaw = yaw_;
        valid = true;
    }
    DataBlob() {
        valid = false;
    }
    std::string hash() {
        if (!valid) {
            return "invalid";
        }
        return std::to_string(distance) + "," + std::to_string(pitch) + "," + std::to_string(yaw);
    }
    double distance;
    double pitch;
    double yaw;
    bool valid = false;
};

#endif //PROJECT_DATABLOB_HPP
