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
            make_pair("goalProcFOV", "75"),
            make_pair("gearProcFOV", "75"),
            make_pair("streamDeviceNumber", "2"),
            make_pair("networkBasePort", "5800"),
            make_pair("showDebugWindows", "1"),
            make_pair("showDebugText", "1"),
            make_pair("runDebugFunctions", "1"),

            make_pair("streamCompression", "30"),

            make_pair("goalProcHBase", "60"),
            make_pair("goalProcSBase", "255"),
            make_pair("goalProcVBase", "170"),
            make_pair("goalProcHRange", "2"),
            make_pair("goalProcSRange", "2"),
            make_pair("goalProcVRange", "80"),

            make_pair("gearProcHBase", "60"),
            make_pair("gearProcSBase", "255"),
            make_pair("gearProcVBase", "170"),
            make_pair("gearProcHRange", "2"),
            make_pair("gearProcSRange", "2"),
            make_pair("gearProcVRange", "80"),

            make_pair("goalProcAspect", "-1"),
            make_pair("gearProcAspect", "-1"),
            make_pair("goalProcAspectRange", "-1"),
            make_pair("gearProcAspectRange", "-1"),

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
