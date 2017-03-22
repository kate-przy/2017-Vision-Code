//
// Created by cameronearle on 2/21/17.
//

#include "Configuration.hpp"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <string>
#include <iostream>

std::string Configuration::hash(bool fileMode) {

    std::string endLine;
    std::string delimiter;
    
    std::string toReturn;
    
    if (fileMode) {
        endLine = "\n";
        delimiter = "=";
        toReturn  = "";
    } else {
        endLine = ",";
        delimiter = ":";
        toReturn = "CONFIG#";
    }
    
    toReturn = toReturn
    + ("goalProcDeviceNumber" + delimiter + std::to_string(goalProcDeviceNumber)) + endLine
    + ("gearProcDeviceNumber" + delimiter + std::to_string(gearProcDeviceNumber)) + endLine
    + ("useGoalCamera" + delimiter + std::to_string(useGoalCamera)) + endLine
    + ("useGearCamera" + delimiter + std::to_string(useGearCamera)) + endLine
    + ("goalProcFOV" + delimiter + std::to_string(goalProcFOV)) + endLine
    + ("gearProcFOV" + delimiter + std::to_string(gearProcFOV)) + endLine
    + ("goalProcFocalLength" + delimiter + std::to_string(goalProcFocalLength)) + endLine
    + ("gearProcFocalLength" + delimiter + std::to_string(gearProcFocalLength)) + endLine
    + ("streamDeviceNumber" + delimiter + std::to_string(streamDeviceNumber)) + endLine
    + ("networkBasePort" + delimiter + std::to_string(networkBasePort)) + endLine
    + ("showDebugWindows" + delimiter + std::to_string(showDebugWindows)) + endLine
    + ("showDebugText" + delimiter + std::to_string(showDebugText)) + endLine
    + ("runDebugFunctions" + delimiter + std::to_string(runDebugFunctions)) + endLine
    + ("streamCompression" + delimiter + std::to_string(streamCompression)) + endLine
    + ("goalProcHLower" + delimiter + std::to_string(goalProcHLower)) + endLine
    + ("goalProcSLower" + delimiter + std::to_string(goalProcSLower)) + endLine
    + ("goalProcVLower" + delimiter + std::to_string(goalProcVLower)) + endLine
    + ("goalProcHUpper" + delimiter + std::to_string(goalProcHUpper)) + endLine
    + ("goalProcSUpper" + delimiter + std::to_string(goalProcSUpper)) + endLine
    + ("goalProcVUpper" + delimiter + std::to_string(goalProcVUpper)) + endLine
    + ("gearProcHLower" + delimiter + std::to_string(gearProcHLower)) + endLine
    + ("gearProcSLower" + delimiter + std::to_string(gearProcSLower)) + endLine
    + ("gearProcVLower" + delimiter + std::to_string(gearProcVLower)) + endLine
    + ("gearProcHUpper" + delimiter + std::to_string(gearProcHUpper)) + endLine
    + ("gearProcSUpper" + delimiter + std::to_string(gearProcSUpper)) + endLine
    + ("gearProcVUpper" + delimiter + std::to_string(gearProcVUpper)) + endLine
    + ("goalMinArea" + delimiter + std::to_string(goalMinArea)) + endLine
    + ("goalMinPerimeter" + delimiter + std::to_string(goalMinPerimeter)) + endLine
    + ("goalMinWidth" + delimiter + std::to_string(goalMinWidth)) + endLine
    + ("goalMaxWidth" + delimiter + std::to_string(goalMaxWidth)) + endLine
    + ("goalMinHeight" + delimiter + std::to_string(goalMinHeight)) + endLine
    + ("goalMaxHeight" + delimiter + std::to_string(goalMaxHeight)) + endLine
    + ("goalMinSolidity" + delimiter + std::to_string(goalMinSolidity)) + endLine
    + ("goalMaxSolidity" + delimiter + std::to_string(goalMaxSolidity)) + endLine
    + ("goalMinVertices" + delimiter + std::to_string(goalMinVertices)) + endLine
    + ("goalMaxVertices" + delimiter + std::to_string(goalMaxVertices)) + endLine
    + ("goalMinRatio" + delimiter + std::to_string(goalMinRatio)) + endLine
    + ("goalMaxRatio" + delimiter + std::to_string(goalMaxRatio)) + endLine
    + ("gearMinArea" + delimiter + std::to_string(gearMinArea)) + endLine
    + ("gearMinPerimeter" + delimiter + std::to_string(gearMinPerimeter)) + endLine
    + ("gearMinWidth" + delimiter + std::to_string(gearMinWidth)) + endLine
    + ("gearMaxWidth" + delimiter + std::to_string(gearMaxWidth)) + endLine
    + ("gearMinHeight" + delimiter + std::to_string(gearMinHeight)) + endLine
    + ("gearMaxHeight" + delimiter + std::to_string(gearMaxHeight)) + endLine
    + ("gearMinSolidity" + delimiter + std::to_string(gearMinSolidity)) + endLine
    + ("gearMaxSolidity" + delimiter + std::to_string(gearMaxSolidity)) + endLine
    + ("gearMinVertices" + delimiter + std::to_string(gearMinVertices)) + endLine
    + ("gearMaxVertices" + delimiter + std::to_string(gearMaxVertices)) + endLine
    + ("gearMinRatio" + delimiter + std::to_string(gearMinRatio)) + endLine
    + ("gearMaxRatio" + delimiter + std::to_string(gearMaxRatio)) + endLine
    + ("goalProcCameraBrightness" + delimiter + std::to_string(goalProcCameraBrightness)) + endLine
    + ("goalProcCameraContrast" + delimiter + std::to_string(goalProcCameraContrast)) + endLine
    + ("goalProcCameraSaturation" + delimiter + std::to_string(goalProcCameraSaturation)) + endLine
    + ("goalProcCameraHue" + delimiter + std::to_string(goalProcCameraHue)) + endLine
    + ("goalProcCameraAutoWB" + delimiter + std::to_string(goalProcCameraAutoWB)) + endLine
    + ("goalProcCameraExposure" + delimiter + std::to_string(goalProcCameraExposure)) + endLine
    + ("goalProcCameraAutoGain" + delimiter + std::to_string(goalProcCameraAutoGain)) + endLine
    + ("goalProcCameraGain" + delimiter + std::to_string(goalProcCameraGain)) + endLine
    + ("goalProcCameraVFlip" + delimiter + std::to_string(goalProcCameraVFlip)) + endLine
    + ("goalProcCameraHFlip" + delimiter + std::to_string(goalProcCameraHFlip)) + endLine
    + ("goalProcCameraManualExposure" + delimiter + std::to_string(goalProcCameraManualExposure)) + endLine
    + ("gearProcCameraBrightness" + delimiter + std::to_string(gearProcCameraBrightness)) + endLine
    + ("gearProcCameraContrast" + delimiter + std::to_string(gearProcCameraContrast)) + endLine
    + ("gearProcCameraSaturation" + delimiter + std::to_string(gearProcCameraSaturation)) + endLine
    + ("gearProcCameraHue" + delimiter + std::to_string(gearProcCameraHue)) + endLine
    + ("gearProcCameraAutoWB" + delimiter + std::to_string(gearProcCameraAutoWB)) + endLine
    + ("gearProcCameraExposure" + delimiter + std::to_string(gearProcCameraExposure)) + endLine
    + ("gearProcCameraAutoGain" + delimiter + std::to_string(gearProcCameraAutoGain)) + endLine
    + ("gearProcCameraGain" + delimiter + std::to_string(gearProcCameraGain)) + endLine
    + ("gearProcCameraVFlip" + delimiter + std::to_string(gearProcCameraVFlip)) + endLine
    + ("gearProcCameraHFlip" + delimiter + std::to_string(gearProcCameraHFlip)) + endLine
    + ("gearProcCameraManualExposure" + delimiter + std::to_string(gearProcCameraManualExposure)) + endLine
    + ("goalStreamCameraBrightness" + delimiter + std::to_string(goalStreamCameraBrightness)) + endLine
    + ("goalStreamCameraContrast" + delimiter + std::to_string(goalStreamCameraContrast)) + endLine
    + ("goalStreamCameraSaturation" + delimiter + std::to_string(goalStreamCameraSaturation)) + endLine
    + ("goalStreamCameraHue" + delimiter + std::to_string(goalStreamCameraHue)) + endLine
    + ("goalStreamCameraAutoWB" + delimiter + std::to_string(goalStreamCameraAutoWB)) + endLine
    + ("goalStreamCameraExposure" + delimiter + std::to_string(goalStreamCameraExposure)) + endLine
    + ("goalStreamCameraAutoGain" + delimiter + std::to_string(goalStreamCameraAutoGain)) + endLine
    + ("goalStreamCameraGain" + delimiter + std::to_string(goalStreamCameraGain)) + endLine
    + ("goalStreamCameraVFlip" + delimiter + std::to_string(goalStreamCameraVFlip)) + endLine
    + ("goalStreamCameraHFlip" + delimiter + std::to_string(goalStreamCameraHFlip)) + endLine
    + ("goalStreamCameraManualExposure" + delimiter + std::to_string(goalStreamCameraManualExposure)) + endLine
    + ("gearStreamCameraBrightness" + delimiter + std::to_string(gearStreamCameraBrightness)) + endLine
    + ("gearStreamCameraContrast" + delimiter + std::to_string(gearStreamCameraContrast)) + endLine
    + ("gearStreamCameraSaturation" + delimiter + std::to_string(gearStreamCameraSaturation)) + endLine
    + ("gearStreamCameraHue" + delimiter + std::to_string(gearStreamCameraHue)) + endLine
    + ("gearStreamCameraAutoWB" + delimiter + std::to_string(gearStreamCameraAutoWB)) + endLine
    + ("gearStreamCameraExposure" + delimiter + std::to_string(gearStreamCameraExposure)) + endLine
    + ("gearStreamCameraAutoGain" + delimiter + std::to_string(gearStreamCameraAutoGain)) + endLine
    + ("gearStreamCameraGain" + delimiter + std::to_string(gearStreamCameraGain)) + endLine
    + ("gearStreamCameraVFlip" + delimiter + std::to_string(gearStreamCameraVFlip)) + endLine
    + ("gearStreamCameraHFlip" + delimiter + std::to_string(gearStreamCameraHFlip)) + endLine
    + ("gearStreamCameraManualExposure" + delimiter + std::to_string(gearStreamCameraManualExposure))
    ;

    return toReturn;
}

bool Configuration::operator==(const Configuration &config) {
    return (goalProcDeviceNumber == config.goalProcDeviceNumber &&
            gearProcDeviceNumber == config.gearProcDeviceNumber &&
            useGoalCamera == config.useGoalCamera &&
            useGearCamera == config.useGearCamera &&
            goalProcFOV == config.goalProcFOV &&
            gearProcFOV == config.gearProcFOV &&
            goalProcFocalLength == config.goalProcFocalLength &&
            gearProcFocalLength == config.gearProcFocalLength &&
            streamDeviceNumber == config.streamDeviceNumber &&
            networkBasePort == config.networkBasePort &&
            showDebugWindows == config.showDebugWindows &&
            showDebugText == config.showDebugText &&
            runDebugFunctions == config.runDebugFunctions &&
            streamCompression == config.streamCompression &&
            goalProcHLower == config.goalProcHLower &&
            goalProcSLower == config.goalProcSLower &&
            goalProcVLower == config.goalProcVLower &&
            goalProcHUpper == config.goalProcHUpper &&
            goalProcSUpper == config.goalProcSUpper &&
            goalProcVUpper == config.goalProcVUpper &&
            gearProcHLower == config.gearProcHLower &&
            gearProcSLower == config.gearProcSLower &&
            gearProcVLower == config.gearProcVLower &&
            gearProcHUpper == config.gearProcHUpper &&
            gearProcSUpper == config.gearProcSUpper &&
            gearProcVUpper == config.gearProcVUpper &&
            goalMinArea == config.goalMinArea &&
            goalMinPerimeter == config.goalMinPerimeter &&
            goalMinWidth == config.goalMinWidth &&
            goalMaxWidth == config.goalMaxWidth &&
            goalMinHeight == config.goalMinHeight &&
            goalMaxHeight == config.goalMaxHeight &&
            goalMinSolidity == config.goalMinSolidity &&
            goalMaxSolidity == config.goalMaxSolidity &&
            goalMinVertices == config.goalMinVertices &&
            goalMaxVertices == config.goalMaxVertices &&
            goalMinRatio == config.goalMinRatio &&
            goalMaxRatio == config.goalMaxRatio &&
            gearMinArea == config.gearMinArea &&
            gearMinPerimeter == config.gearMinPerimeter &&
            gearMinWidth == config.gearMinWidth &&
            gearMaxWidth == config.gearMaxWidth &&
            gearMinHeight == config.gearMinHeight &&
            gearMaxHeight == config.gearMaxHeight &&
            gearMinSolidity == config.gearMinSolidity &&
            gearMaxSolidity == config.gearMaxSolidity &&
            gearMinVertices == config.gearMinVertices &&
            gearMaxVertices == config.gearMaxVertices &&
            gearMinRatio == config.gearMinRatio &&
            gearMaxRatio == config.gearMaxRatio &&
            goalProcCameraBrightness == config.goalProcCameraBrightness &&
            goalProcCameraContrast == config.goalProcCameraContrast &&
            goalProcCameraSaturation == config.goalProcCameraSaturation &&
            goalProcCameraHue == config.goalProcCameraHue &&
            goalProcCameraAutoWB == config.goalProcCameraAutoWB &&
            goalProcCameraExposure == config.goalProcCameraExposure &&
            goalProcCameraAutoGain == config.goalProcCameraAutoGain &&
            goalProcCameraGain == config.goalProcCameraGain &&
            goalProcCameraVFlip == config.goalProcCameraVFlip &&
            goalProcCameraHFlip == config.goalProcCameraHFlip &&
            goalProcCameraManualExposure == config.goalProcCameraManualExposure &&
            gearProcCameraBrightness == config.gearProcCameraBrightness &&
            gearProcCameraContrast == config.gearProcCameraContrast &&
            gearProcCameraSaturation == config.gearProcCameraSaturation &&
            gearProcCameraHue == config.gearProcCameraHue &&
            gearProcCameraAutoWB == config.gearProcCameraAutoWB &&
            gearProcCameraExposure == config.gearProcCameraExposure &&
            gearProcCameraAutoGain == config.gearProcCameraAutoGain &&
            gearProcCameraGain == config.gearProcCameraGain &&
            gearProcCameraVFlip == config.gearProcCameraVFlip &&
            gearProcCameraHFlip == config.gearProcCameraHFlip &&
            gearProcCameraManualExposure == config.gearProcCameraManualExposure &&
            goalStreamCameraBrightness == config.goalStreamCameraBrightness &&
            goalStreamCameraContrast == config.goalStreamCameraContrast &&
            goalStreamCameraSaturation == config.goalStreamCameraSaturation &&
            goalStreamCameraHue == config.goalStreamCameraHue &&
            goalStreamCameraAutoWB == config.goalStreamCameraAutoWB &&
            goalStreamCameraExposure == config.goalStreamCameraExposure &&
            goalStreamCameraAutoGain == config.goalStreamCameraAutoGain &&
            goalStreamCameraGain == config.goalStreamCameraGain &&
            goalStreamCameraVFlip == config.goalStreamCameraVFlip &&
            goalStreamCameraHFlip == config.goalStreamCameraHFlip &&
            goalStreamCameraManualExposure == config.goalStreamCameraManualExposure &&
            gearStreamCameraBrightness == config.gearStreamCameraBrightness &&
            gearStreamCameraContrast == config.gearStreamCameraContrast &&
            gearStreamCameraSaturation == config.gearStreamCameraSaturation &&
            gearStreamCameraHue == config.gearStreamCameraHue &&
            gearStreamCameraAutoWB == config.gearStreamCameraAutoWB &&
            gearStreamCameraExposure == config.gearStreamCameraExposure &&
            gearStreamCameraAutoGain == config.gearStreamCameraAutoGain &&
            gearStreamCameraGain == config.gearStreamCameraGain &&
            gearStreamCameraVFlip == config.gearStreamCameraVFlip &&
            gearStreamCameraHFlip == config.gearStreamCameraHFlip &&
            gearStreamCameraManualExposure == config.gearStreamCameraManualExposure);
}

bool Configuration::operator!=(const Configuration &config) {
    return !operator==(config);
}

void Configuration::writeToFile(std::string fileName, bool moveOldFile) {
    if (moveOldFile) { //If we should move the old file
        std::string oldFileName = fileName + ".old";
        std::rename(fileName.c_str(), oldFileName.c_str()); //Rename the old file to "[name].old"
    }

    std::ofstream newFile;
    newFile.open(fileName); //Create the new file
    newFile << hash(true); //Write the data to the file
    newFile.close(); //Close the file
}