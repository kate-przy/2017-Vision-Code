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
            make_pair("streamDeviceNumber", "2"),
            make_pair("showDebugWindows", "1"),
            make_pair("showDebugText", "1")
    };
    map<string, string> finalSettings;
    template <class T>
    T configFind(string key_);
    bool validity;
    string filePath;
    string ld = "ConfigParser";
};


#endif //PROJECT_CONFIGPARSER_HPP
