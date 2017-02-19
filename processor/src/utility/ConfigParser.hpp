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
            make_pair("gearProcAspectRange", "-1")
    };
    map<string, string> finalSettings;
    template <class T>
    T configFind(string key_);
    bool validity;
    string filePath;
    string ld = "ConfigParser";
};


#endif //PROJECT_CONFIGPARSER_HPP
