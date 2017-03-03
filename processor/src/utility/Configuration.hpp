//
// Created by cameronearle on 1/4/17.
//

#ifndef PROJECT_CONFIGURATION_HPP
#define PROJECT_CONFIGURATION_HPP

#include <string>

struct Configuration {

    std::string hash();
    void writeToFile(std::string fileName);

    int goalProcDeviceNumber;
    int gearProcDeviceNumber;
    bool useGoalCamera;
    bool useGearCamera;
    double goalProcFOV;
    double gearProcFOV;
    double goalProcFocalLength;
    double gearProcFocalLength;
    int streamDeviceNumber;
    int networkBasePort;
    bool showDebugWindows;
    bool showDebugText;
    bool runDebugFunctions;

    int streamCompression;

    int goalProcHLower;
    int goalProcSLower;
    int goalProcVLower;
    int goalProcHUpper;
    int goalProcSUpper;
    int goalProcVUpper;

    int gearProcHLower;
    int gearProcSLower;
    int gearProcVLower;
    int gearProcHUpper;
    int gearProcSUpper;
    int gearProcVUpper;

    double goalMinArea;
    double goalMinPerimeter;
    double goalMinWidth;
    double goalMaxWidth;
    double goalMinHeight;
    double goalMaxHeight;
    double goalMinSolidity;
    double goalMaxSolidity;
    double goalMinVertices;
    double goalMaxVertices;
    double goalMinRatio;
    double goalMaxRatio;

    double gearMinArea;
    double gearMinPerimeter;
    double gearMinWidth;
    double gearMaxWidth;
    double gearMinHeight;
    double gearMaxHeight;
    double gearMinSolidity;
    double gearMaxSolidity;
    double gearMinVertices;
    double gearMaxVertices;
    double gearMinRatio;
    double gearMaxRatio;

    int goalProcCameraBrightness;
    int goalProcCameraContrast;
    int goalProcCameraSaturation;
    int goalProcCameraHue;
    bool goalProcCameraAutoWB;
    int goalProcCameraExposure;
    bool goalProcCameraAutoGain;
    int goalProcCameraGain;
    bool goalProcCameraVFlip;
    bool goalProcCameraHFlip;
    bool goalProcCameraManualExposure;

    int gearProcCameraBrightness;
    int gearProcCameraContrast;
    int gearProcCameraSaturation;
    int gearProcCameraHue;
    bool gearProcCameraAutoWB;
    int gearProcCameraExposure;
    bool gearProcCameraAutoGain;
    int gearProcCameraGain;
    bool gearProcCameraVFlip;
    bool gearProcCameraHFlip;
    bool gearProcCameraManualExposure;

    int goalStreamCameraBrightness;
    int goalStreamCameraContrast;
    int goalStreamCameraSaturation;
    int goalStreamCameraHue;
    bool goalStreamCameraAutoWB;
    int goalStreamCameraExposure;
    bool goalStreamCameraAutoGain;
    int goalStreamCameraGain;
    bool goalStreamCameraVFlip;
    bool goalStreamCameraHFlip;
    bool goalStreamCameraManualExposure;

    int gearStreamCameraBrightness;
    int gearStreamCameraContrast;
    int gearStreamCameraSaturation;
    int gearStreamCameraHue;
    bool gearStreamCameraAutoWB;
    int gearStreamCameraExposure;
    bool gearStreamCameraAutoGain;
    int gearStreamCameraGain;
    bool gearStreamCameraVFlip;
    bool gearStreamCameraHFlip;
    bool gearStreamCameraManualExposure;
};

#endif //PROJECT_CONFIGURATION_HPP
