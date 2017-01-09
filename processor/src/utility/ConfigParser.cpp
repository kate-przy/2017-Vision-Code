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


/* splitElements
 * Takes in a string and a delimiter character,
 * and returns a vector containing the split
 * parts.  Returns an empty vector if nothing is found
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

/* ConfigParser()
 * Constructor for a parser object.  Reads config file,
 * command line args, and writes them to a map.
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

/* configFind()
 * Function to find elements from the map,
 * substitute defaults if elements are not found,
 * and convert elements to the correct type
 * as set by the template
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

/* getSettings()
 * Returns a fully set up ConfigSettings object
 * for reading by other parts of the program.
 * When adding new config values, we must
 * put them here as well
 */
Configuration ConfigParser::getSettings() { //GET SETTINGS
    //This is all pretty self explanatory
    //We use configFind() to get each value
    //And set the appropriate value in the config object
    Configuration configuration;

    configuration.procDeviceNumber = configFind<int>("procDeviceNumber");
    configuration.streamDeviceNumber = configFind<int>("streamDeviceNumber");
    configuration.showDebugWindows = configFind<bool>("showDebugWindows");

    return configuration;
}