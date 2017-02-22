//Team 401 Vision Processing
//(Ported from the preseason code)
//File: ConfigParser.cpp
//Description: Parses the configuration and provides a configuration object containing the settings
//Author: Cameron Earle and Liam Lawrence

#include "ConfigParser.hpp"

#include <ios>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "Log.hpp"
using namespace std;


/**
 * Splits a string on a delimeter
 * @param str The string to split
 * @param delimiter The delimiter to split on, default '='
 * @return A vector of split elements
 */
vector<string> ConfigParser::splitElements(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string tok;

    while (getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

/**
 * Parses the config based on the passed override arguments and the file path provided
 * @param clargs The override arguments to override config file data
 * @param filePath_ The path to the config file, default relative "config.txt"
 */
ConfigParser::ConfigParser(vector<string> clargs, string filePath_) {
    vector<string> splitArgs; //Variable to hold the split elements from each command line arg
    for (string s : clargs) {
        splitArgs = splitElements(s); //Split the element by '='
        if (splitArgs.size() == 2) { //If this isn't true, the argument is invalid, and should be ignored
            Log::i(ld, "Found command line argument [" + splitArgs[0] + "] with value [" + splitArgs[1] + "]");
            finalSettings.insert(make_pair(splitArgs[0], splitArgs[1])); //Add the valid argument to our map
        }
    }
    Log::d(ld, "Parsing Config");
    filePath = filePath_;
    file.open(filePath_); //Open the config file for reading
    if (!file.good()) { //If the config file doesn't exist
        Log::w(ld, "Config doesn't exist, creating it!");
        ofstream writeFile;
        writeFile.open(filePath_);
        for (pair<string, string> toAppend : defaults) {
            writeFile << toAppend.first << "=" << toAppend.second << "\n"; //Append the default value for each setting to the config
        }
        writeFile.close();
        Log::d(ld, "Config created with defaults");
        finalSettings = defaults;
        return;
    }
    string currentLine; //Variable to hold the current line of the config
    vector<string> splitLine; //Variable to hold the split element from each line
    while (getline(file, currentLine)) { //Iterate the file by lines
        splitLine = splitElements(currentLine); //Split the elements by '='
        if (splitLine.size() == 2) { //If this isn't true, the element is invalid and should be ignored
            if (finalSettings.find(splitLine[0]) == finalSettings.end()) { //Make sure we aren't overriding command line args
                finalSettings.insert(make_pair(splitLine[0], splitLine[1])); //Put each line into a map
            }
        }
    }
    file.close();
    Log::d(ld, "Config read successfully");
}

/**
 * Finds an option from the config map, or substitutes a default if none is found
 * @tparam T The type to cast the found data to
 * @param key_ The key for the data
 * @return The value for the data
 */
template <class T>
T ConfigParser::configFind(string key_) {
    if (finalSettings.find(key_) != finalSettings.end()) { //If the requested item is in the map
        Log::d(ld, "Found value [" + finalSettings[key_] + "] for key [" + key_ + "]");
        try {
            return boost::lexical_cast<T>(finalSettings[key_]); //Try to cast to the requested type
        } catch (...) { //Casting failed
            Log::e(ld, "Couldn't lexically cast key [" + key_ + "] to class [" + typeid(T).name() + "]");
            return 0; //Zero is a safe thing to return for any primitive type, which is all this can handle
        }
    } else { //We couldn't find the value in the map
        Log::w(ld, "Couldn't find value with key [" + key_ + "], using default");
        if (defaults.find(key_) == defaults.end()) { //This should never happen
            Log::wtfomgy(ld, "Couldn't find value with key [" + key_ + "] in defaults. This is a problem!");
            return 0;
        }
        ofstream writeFile;
        writeFile.open(filePath, ios::app);
        writeFile << key_ << "=" << defaults[key_] << "\n"; //Write the missing value to the config as default
        writeFile.close();
        Log::d(ld, "Wrote missing value [" + defaults[key_] + "] for key [" + key_ + "] to the config");
        try {
            return boost::lexical_cast<T>(defaults[key_]); //Return the default we just wrote
        } catch (...) {
            Log::e(ld, "Couldn't lexically cast DEFAULT key [" + key_ + "] to class [" + typeid(T).name() + "]");
            return 0;
        }
    }
}

/**
 * Gets a fully set up Configuration object from the config map
 * @return The Configuration object
 */
Configuration ConfigParser::getSettings() { //GET SETTINGS
    //This is all pretty self explanatory
    //We use configFind() to get each value
    //And set the appropriate value in the config object
    Configuration configuration;

    configuration.goalProcDeviceNumber = configFind<int>("goalProcDeviceNumber");
    configuration.gearProcDeviceNumber = configFind<int>("gearProcDeviceNumber");
    configuration.goalProcFOV = configFind<int>("goalProcFOV");
    configuration.gearProcFOV = configFind<int>("gearProcFOV");
    configuration.streamDeviceNumber = configFind<int>("streamDeviceNumber");
    configuration.networkBasePort = configFind<int>("networkBasePort");
    configuration.showDebugWindows = configFind<bool>("showDebugWindows");
    configuration.showDebugText = configFind<bool>("showDebugText");
    configuration.runDebugFunctions = configFind<bool>("runDebugFunctions");

    configuration.streamCompression = configFind<int>("streamCompression");

    configuration.goalProcHBase = configFind<int>("goalProcHBase");
    configuration.goalProcSBase = configFind<int>("goalProcSBase");
    configuration.goalProcVBase = configFind<int>("goalProcVBase");
    configuration.goalProcHRange = configFind<int>("goalProcHRange");
    configuration.goalProcSRange = configFind<int>("goalProcSRange");
    configuration.goalProcVRange = configFind<int>("goalProcVRange");

    configuration.gearProcHBase = configFind<int>("gearProcHBase");
    configuration.gearProcSBase = configFind<int>("gearProcSBase");
    configuration.gearProcVBase = configFind<int>("gearProcVBase");
    configuration.gearProcHRange = configFind<int>("gearProcHRange");
    configuration.gearProcSRange = configFind<int>("gearProcSRange");
    configuration.gearProcVRange = configFind<int>("gearProcVRange");

    configuration.goalProcAspect = configFind<double>("goalProcAspect");
    configuration.gearProcAspect = configFind<double>("gearProcAspect");
    configuration.goalProcAspectRange = configFind<double>("goalProcAspectRange");
    configuration.gearProcAspectRange = configFind<double>("gearProcAspectRange");

    configuration.goalProcCameraBrightness = configFind<int>("goalProcCameraBrightness");
    configuration.goalProcCameraContrast = configFind<int>("goalProcCameraContrast");
    configuration.goalProcCameraSaturation = configFind<int>("goalProcCameraSaturation");
    configuration.goalProcCameraHue = configFind<int>("goalProcCameraHue");
    configuration.goalProcCameraAutoWB = configFind<bool>("goalProcCameraAutoWB");
    configuration.goalProcCameraExposure = configFind<int>("goalProcCameraExposure");
    configuration.goalProcCameraAutoGain = configFind<bool>("goalProcCameraAutoGain");
    configuration.goalProcCameraGain = configFind<int>("goalProcCameraGain");
    configuration.goalProcCameraVFlip = configFind<bool>("goalProcCameraVFlip");
    configuration.goalProcCameraHFlip = configFind<bool>("goalProcCameraHFlip");
    configuration.goalProcCameraManualExposure = configFind<bool>("goalProcCameraManualExposure");

    configuration.gearProcCameraBrightness = configFind<int>("gearProcCameraBrightness");
    configuration.gearProcCameraContrast = configFind<int>("gearProcCameraContrast");
    configuration.gearProcCameraSaturation = configFind<int>("gearProcCameraSaturation");
    configuration.gearProcCameraHue = configFind<int>("gearProcCameraHue");
    configuration.gearProcCameraAutoWB = configFind<bool>("gearProcCameraAutoWB");
    configuration.gearProcCameraExposure = configFind<int>("gearProcCameraExposure");
    configuration.gearProcCameraAutoGain = configFind<bool>("gearProcCameraAutoGain");
    configuration.gearProcCameraGain = configFind<int>("gearProcCameraGain");
    configuration.gearProcCameraVFlip = configFind<bool>("gearProcCameraVFlip");
    configuration.gearProcCameraHFlip = configFind<bool>("gearProcCameraHFlip");
    configuration.gearProcCameraManualExposure = configFind<bool>("gearProcCameraManualExposure");

    configuration.goalStreamCameraBrightness = configFind<int>("goalStreamCameraBrightness");
    configuration.goalStreamCameraContrast = configFind<int>("goalStreamCameraContrast");
    configuration.goalStreamCameraSaturation = configFind<int>("goalStreamCameraSaturation");
    configuration.goalStreamCameraHue = configFind<int>("goalStreamCameraHue");
    configuration.goalStreamCameraAutoWB = configFind<bool>("goalStreamCameraAutoWB");
    configuration.goalStreamCameraExposure = configFind<int>("goalStreamCameraExposure");
    configuration.goalStreamCameraAutoGain = configFind<bool>("goalStreamCameraAutoGain");
    configuration.goalStreamCameraGain = configFind<int>("goalStreamCameraGain");
    configuration.goalStreamCameraVFlip = configFind<bool>("goalStreamCameraVFlip");
    configuration.goalStreamCameraHFlip = configFind<bool>("goalStreamCameraHFlip");
    configuration.goalStreamCameraManualExposure = configFind<bool>("goalStreamCameraManualExposure");

    configuration.gearStreamCameraBrightness = configFind<int>("gearStreamCameraBrightness");
    configuration.gearStreamCameraContrast = configFind<int>("gearStreamCameraContrast");
    configuration.gearStreamCameraSaturation = configFind<int>("gearStreamCameraSaturation");
    configuration.gearStreamCameraHue = configFind<int>("gearStreamCameraHue");
    configuration.gearStreamCameraAutoWB = configFind<bool>("gearStreamCameraAutoWB");
    configuration.gearStreamCameraExposure = configFind<int>("gearStreamCameraExposure");
    configuration.gearStreamCameraAutoGain = configFind<bool>("gearStreamCameraAutoGain");
    configuration.gearStreamCameraGain = configFind<int>("gearStreamCameraGain");
    configuration.gearStreamCameraVFlip = configFind<bool>("gearStreamCameraVFlip");
    configuration.gearStreamCameraHFlip = configFind<bool>("gearStreamCameraHFlip");
    configuration.gearStreamCameraManualExposure = configFind<bool>("gearStreamCameraManualExposure");

    return configuration;
}
