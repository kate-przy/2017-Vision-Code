//
// Created by cameronearle on 1/4/17.
//

#ifndef PROJECT_CONFIGURATION_HPP
#define PROJECT_CONFIGURATION_HPP

struct Configuration {
    int goalProcDeviceNumber;
    int gearProcDeviceNumber;
    int goalProcFOV;
    int gearProcFOV;
    int streamDeviceNumber;
    int networkBasePort;
    bool showDebugWindows;
    bool showDebugText;
    bool runDebugFunctions;

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
};

#endif //PROJECT_CONFIGURATION_HPP
