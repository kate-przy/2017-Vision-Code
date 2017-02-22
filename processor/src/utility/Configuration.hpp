//
// Created by cameronearle on 1/4/17.
//

#ifndef PROJECT_CONFIGURATION_HPP
#define PROJECT_CONFIGURATION_HPP

#include <string>

struct Configuration {

    std::string hash();

    int goalProcDeviceNumber;
    int gearProcDeviceNumber;
    int goalProcFOV;
    int gearProcFOV;
    int streamDeviceNumber;
    int networkBasePort;
    bool showDebugWindows;
    bool showDebugText;
    bool runDebugFunctions;

    int streamCompression;

    int goalProcHBase;
    int goalProcSBase;
    int goalProcVBase;
    int goalProcHRange;
    int goalProcSRange;
    int goalProcVRange;

    int gearProcHBase;
    int gearProcSBase;
    int gearProcVBase;
    int gearProcHRange;
    int gearProcSRange;
    int gearProcVRange;

    double goalProcAspect;
    double gearProcAspect;
    double goalProcAspectRange;
    double gearProcAspectRange;

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
    /*
     * brightness
     * contrast
     * saturation
     * hue
     * auto wb
     * exposure
     * auto gain
     * gain
     * flip
     * auto exposure
     */
};

#endif //PROJECT_CONFIGURATION_HPP
