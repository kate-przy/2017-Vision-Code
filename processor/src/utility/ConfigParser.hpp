//Team 401 Vision Processing
//(Ported from the preseason code)
//File: ConfigParser.hpp
//Description: Parses the configuration and provides a configuration object containing the settings
//Author: Cameron Earle and Liam Lawrence

#ifndef PROJECT_CONFIGPARSER_HPP
#define PROJECT_CONFIGPARSER_HPP


#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "Configuration.hpp"

using namespace std;

class ConfigParser {
public :
    ConfigParser(vector<string> clargs, string filePath_="config.txt");
    Configuration getSettings();
private:
    vector<string> splitElements(string str, char delimiter='=');
    ifstream file;
    map<string, string> defaults = { //DEFAULTS LIST
            make_pair("goalProcDeviceNumber", "0"),
            make_pair("gearProcDeviceNumber", "1"),
            make_pair("useGoalCamera", "1"),
            make_pair("useGearCamera", "0"),
            make_pair("goalProcFOV", "75"),
            make_pair("gearProcFOV", "75"),
            make_pair("goalProcFocalLength", "0"),
            make_pair("gearProcFocalLength", "0"),
            make_pair("streamDeviceNumber", "2"),
            make_pair("networkBasePort", "5800"),
            make_pair("showDebugWindows", "0"),
            make_pair("showDebugText", "0"),
            make_pair("runDebugFunctions", "0"),

            make_pair("streamCompression", "30"),

            make_pair("goalProcHLower", "58"),
            make_pair("goalProcSLower", "253"),
            make_pair("goalProcVLower", "120"),
            make_pair("goalProcHUpper", "62"),
            make_pair("goalProcSUpper", "255"),
            make_pair("goalProcVUpper", "175"),

            make_pair("gearProcHLower", "58"),
            make_pair("gearProcSLower", "253"),
            make_pair("gearProcVLower", "120"),
            make_pair("gearProcHUpper", "62"),
            make_pair("gearProcSUpper", "255"),
            make_pair("gearProcVUpper", "185"),

            make_pair("goalMinArea", "57"),
            make_pair("goalMinPerimeter", "50"),
            make_pair("goalMinWidth", "25"),
            make_pair("goalMaxWidth", "1000"),
            make_pair("goalMinHeight", "4"),
            make_pair("goalMaxHeight", "1000"),
            make_pair("goalMinSolidity", "62"),
            make_pair("goalMaxSolidity", "100"),
            make_pair("goalMinVertices", "4"),
            make_pair("goalMaxVertices", "1000000"),
            make_pair("goalMinRatio", "1"),
            make_pair("goalMaxRatio", "6"),

            make_pair("gearMinArea", "0"),
            make_pair("gearMinPerimeter", "0"),
            make_pair("gearMinWidth", "0"),
            make_pair("gearMaxWidth", "1000"),
            make_pair("gearMinHeight", "0"),
            make_pair("gearMaxHeight", "1000"),
            make_pair("gearMinSolidity", "0"),
            make_pair("gearMaxSolidity", "100"),
            make_pair("gearMinVertices", "0"),
            make_pair("gearMaxVertices", "1000000"),
            make_pair("gearMinRatio", "2"),
            make_pair("gearMaxRatio", "1000"),

            make_pair("goalProcCameraBrightness", "0"),
            make_pair("goalProcCameraContrast", "0"),
            make_pair("goalProcCameraSaturation", "255"),
            make_pair("goalProcCameraHue", "0"),
            make_pair("goalProcCameraAutoWB", "0"),
            make_pair("goalProcCameraExposure", "20"),
            make_pair("goalProcCameraAutoGain", "0"),
            make_pair("goalProcCameraGain", "15"),
            make_pair("goalProcCameraVFlip", "0"),
            make_pair("goalProcCameraHFlip", "0"),
            make_pair("goalProcCameraManualExposure", "1"),

            make_pair("gearProcCameraBrightness", "0"),
            make_pair("gearProcCameraContrast", "0"),
            make_pair("gearProcCameraSaturation", "255"),
            make_pair("gearProcCameraHue", "0"),
            make_pair("gearProcCameraAutoWB", "0"),
            make_pair("gearProcCameraExposure", "20"),
            make_pair("gearProcCameraAutoGain", "0"),
            make_pair("gearProcCameraGain", "15"),
            make_pair("gearProcCameraVFlip", "1"),
            make_pair("gearProcCameraHFlip", "0"),
            make_pair("gearProcCameraManualExposure", "1"),

            make_pair("goalStreamCameraBrightness", "0"),
            make_pair("goalStreamCameraContrast", "32"),
            make_pair("goalStreamCameraSaturation", "64"),
            make_pair("goalStreamCameraHue", "0"),
            make_pair("goalStreamCameraAutoWB", "1"),
            make_pair("goalStreamCameraExposure", "120"),
            make_pair("goalStreamCameraAutoGain", "1"),
            make_pair("goalStreamCameraGain", "20"),
            make_pair("goalStreamCameraVFlip", "0"),
            make_pair("goalStreamCameraHFlip", "0"),
            make_pair("goalStreamCameraManualExposure", "0"),

            make_pair("gearStreamCameraBrightness", "0"),
            make_pair("gearStreamCameraContrast", "32"),
            make_pair("gearStreamCameraSaturation", "64"),
            make_pair("gearStreamCameraHue", "0"),
            make_pair("gearStreamCameraAutoWB", "1"),
            make_pair("gearStreamCameraExposure", "120"),
            make_pair("gearStreamCameraAutoGain", "1"),
            make_pair("gearStreamCameraGain", "20"),
            make_pair("gearStreamCameraVFlip", "0"),
            make_pair("gearStreamCameraHFlip", "0"),
            make_pair("gearStreamCameraManualExposure", "0")
    };
    map<string, string> finalSettings;
    template <class T>
    T configFind(string key_);
    bool validity;
    string filePath;
    string ld = "ConfigParser";
};


#endif //PROJECT_CONFIGPARSER_HPP
