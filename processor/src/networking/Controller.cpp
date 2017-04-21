//
// Created by cameronearle on 1/20/17.
//

#include "Controller.hpp"
#include "zhelpers.hpp"
#include <boost/thread/thread.hpp>
#include <linux/v4l2-controls.h>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "../utility/Log.hpp"
#include "../utility/ConfigParser.hpp"

Controller::Controller(Configuration config_, Camera *goalCamera_, Camera *gearCamera_, Processor *goalProc_, Processor *gearProc_, Streamer *streamer_, int port_) {
    config = config_;
    goalCamera = goalCamera_;
    gearCamera = gearCamera_;
    goalProc = goalProc_;
    gearProc = gearProc_;
    streamer = streamer_;
    port = port_;
    storedSettings = config; //Assign the stored settings to the original settings from the config
    goalCameraMode = PROC;
    gearCameraMode = PROC;
}

Configuration Controller::getCurrentSettings() {
    return storedSettings;
}

Controller::ParsedCommand Controller::parseCommand(std::string input) {
    std::vector<string> commandSplit;
    std::vector<string> argsList;
    std::vector<string> argsSplit;
    std::map<string, string> args;

    ParsedCommand toReturn;

    //EXAMPLE: SETTINGNAME#ARG1TAG:ARG1VAL,ARG2TAG:ARG2VAL
    //OPER 1: ["SETTINGNAME", "ARG1TAG:ARG1VAL,ARG2TAG:ARG2VAL"]
    //OPER 2: "SETTINGNAME", ["ARG1TAG:ARG1VAL", "ARG2TAG:ARG2VAL"]
    //OPER 3: "SETTINGNAME", ["ARG1TAG":"ARG1VAL", "ARG2TAG":"ARG2VAL"]

    boost::split(commandSplit, input, boost::is_any_of("#"));
    if (commandSplit.size() >= 1) { //If the command is valid
        toReturn.command = commandMapping[commandSplit[0]];
        toReturn.valid = true;
        if (commandSplit.size() >= 2) { //If the command has args
            boost::split(argsList, commandSplit[1], boost::is_any_of(",")); //Split the args
            for (std::string s : argsList) {
                argsSplit.clear();
                boost::split(argsSplit, s, boost::is_any_of(":"));
                if (argsSplit.size() == 2) {
                    args.insert(std::make_pair(argsSplit[0], argsSplit[1]));
                }
            }
            toReturn.args = args;
        }
    } else {
        toReturn.valid = false;
    }
    return toReturn;
}

void Controller::setGoalCamera(CameraMode mode) {
    switch (mode) {
        case PROC:
            goalCameraMode = PROC;
            goalCamera->setProperty(V4L2_CID_EXPOSURE_AUTO, storedSettings.goalProcCameraManualExposure);
            goalCamera->setProperty(V4L2_CID_AUTOGAIN, storedSettings.goalProcCameraAutoGain);
            goalCamera->setProperty(V4L2_CID_AUTO_WHITE_BALANCE, storedSettings.goalProcCameraAutoWB);
            goalCamera->setProperty(V4L2_CID_BRIGHTNESS, storedSettings.goalProcCameraBrightness);
            goalCamera->setProperty(V4L2_CID_CONTRAST, storedSettings.goalProcCameraContrast);
            goalCamera->setProperty(V4L2_CID_SATURATION, storedSettings.goalProcCameraSaturation);
            goalCamera->setProperty(V4L2_CID_HUE, storedSettings.goalProcCameraHue);
            goalCamera->setProperty(V4L2_CID_EXPOSURE, storedSettings.goalProcCameraExposure);
            goalCamera->setProperty(V4L2_CID_GAIN, storedSettings.goalProcCameraGain);
            goalCamera->setProperty(V4L2_CID_VFLIP, storedSettings.goalProcCameraVFlip);
            goalCamera->setProperty(V4L2_CID_HFLIP, storedSettings.goalProcCameraHFlip);
            break;
        case STREAM:
            goalCameraMode = STREAM;
            goalCamera->setProperty(V4L2_CID_AUTOGAIN, storedSettings.goalStreamCameraAutoGain);
            goalCamera->setProperty(V4L2_CID_AUTO_WHITE_BALANCE, storedSettings.goalStreamCameraAutoWB);
            goalCamera->setProperty(V4L2_CID_EXPOSURE_AUTO, storedSettings.goalStreamCameraManualExposure);
            goalCamera->setProperty(V4L2_CID_BRIGHTNESS, storedSettings.goalStreamCameraBrightness);
            goalCamera->setProperty(V4L2_CID_CONTRAST, storedSettings.goalStreamCameraContrast);
            goalCamera->setProperty(V4L2_CID_SATURATION, storedSettings.goalStreamCameraSaturation);
            goalCamera->setProperty(V4L2_CID_HUE, storedSettings.goalStreamCameraHue);
            goalCamera->setProperty(V4L2_CID_EXPOSURE, storedSettings.goalStreamCameraExposure);
            goalCamera->setProperty(V4L2_CID_GAIN, storedSettings.goalStreamCameraGain);
            goalCamera->setProperty(V4L2_CID_VFLIP, storedSettings.goalStreamCameraVFlip);
            goalCamera->setProperty(V4L2_CID_HFLIP, storedSettings.goalStreamCameraHFlip);
            break;
    }
}

void Controller::setGearCamera(CameraMode mode) {
    switch (mode) {
        case PROC:
            gearCamera->setProperty(V4L2_CID_EXPOSURE_AUTO, storedSettings.gearProcCameraManualExposure);
            gearCamera->setProperty(V4L2_CID_AUTO_WHITE_BALANCE, storedSettings.gearProcCameraAutoWB);
            gearCamera->setProperty(V4L2_CID_AUTOGAIN, storedSettings.gearProcCameraAutoGain);
            gearCamera->setProperty(V4L2_CID_BRIGHTNESS, storedSettings.gearProcCameraBrightness);
            gearCamera->setProperty(V4L2_CID_CONTRAST, storedSettings.gearProcCameraContrast);
            gearCamera->setProperty(V4L2_CID_SATURATION, storedSettings.gearProcCameraSaturation);
            gearCamera->setProperty(V4L2_CID_HUE, storedSettings.gearProcCameraHue);
            gearCamera->setProperty(V4L2_CID_GAIN, storedSettings.gearProcCameraGain);
            gearCamera->setProperty(V4L2_CID_VFLIP, storedSettings.gearProcCameraVFlip);
            gearCamera->setProperty(V4L2_CID_HFLIP, storedSettings.gearProcCameraHFlip);
            gearCamera->setProperty(V4L2_CID_EXPOSURE, storedSettings.gearProcCameraExposure);
            gearCameraMode = PROC;
            break;
        case STREAM:
            gearCamera->setProperty(V4L2_CID_AUTO_WHITE_BALANCE, storedSettings.gearStreamCameraAutoWB);
            gearCamera->setProperty(V4L2_CID_AUTOGAIN, storedSettings.gearStreamCameraAutoGain);
            gearCamera->setProperty(V4L2_CID_EXPOSURE_AUTO, storedSettings.gearStreamCameraManualExposure);
            gearCamera->setProperty(V4L2_CID_BRIGHTNESS, storedSettings.gearStreamCameraBrightness);
            gearCamera->setProperty(V4L2_CID_CONTRAST, storedSettings.gearStreamCameraContrast);
            gearCamera->setProperty(V4L2_CID_SATURATION, storedSettings.gearStreamCameraSaturation);
            gearCamera->setProperty(V4L2_CID_HUE, storedSettings.gearStreamCameraHue);
            gearCamera->setProperty(V4L2_CID_GAIN, storedSettings.gearStreamCameraGain);
            gearCamera->setProperty(V4L2_CID_VFLIP, storedSettings.gearStreamCameraVFlip);
            gearCamera->setProperty(V4L2_CID_HFLIP, storedSettings.gearStreamCameraHFlip);
            gearCamera->setProperty(V4L2_CID_EXPOSURE, storedSettings.gearStreamCameraExposure);
            gearCameraMode = STREAM;
            break;
    }
}

void Controller::react(ParsedCommand command) {
    try {
        if (command.valid) { //If the given command is valid
            switch (command.command) { //Switch on the command
                case INIT:
                    break;
                case SETTINGS_GOAL_PROC_CAMERA:
                    storedSettings.goalProcCameraBrightness = boost::lexical_cast<int>(command.args["goalProcCameraBrightness"]);
                    storedSettings.goalProcCameraContrast = boost::lexical_cast<int>(command.args["goalProcCameraContrast"]);
                    storedSettings.goalProcCameraSaturation = boost::lexical_cast<int>(command.args["goalProcCameraSaturation"]);
                    storedSettings.goalProcCameraHue = boost::lexical_cast<int>(command.args["goalProcCameraHue"]);
                    storedSettings.goalProcCameraAutoWB = boost::lexical_cast<bool>(command.args["goalProcCameraAutoWB"]);
                    storedSettings.goalProcCameraExposure = boost::lexical_cast<int>(command.args["goalProcCameraExposure"]);
                    storedSettings.goalProcCameraAutoGain = boost::lexical_cast<bool>(command.args["goalProcCameraAutoGain"]);
                    storedSettings.goalProcCameraGain = boost::lexical_cast<int>(command.args["goalProcCameraGain"]);
                    storedSettings.goalProcCameraVFlip = boost::lexical_cast<bool>(command.args["goalProcCameraVFlip"]);
                    storedSettings.goalProcCameraHFlip = boost::lexical_cast<bool>(command.args["goalProcCameraHFlip"]);
                    storedSettings.goalProcCameraManualExposure = boost::lexical_cast<bool>(command.args["goalProcCameraManualExposure"]);
                    break;
                case SETTINGS_GEAR_PROC_CAMERA:
                    storedSettings.gearProcCameraBrightness = boost::lexical_cast<int>(command.args["gearProcCameraBrightness"]);
                    storedSettings.gearProcCameraContrast = boost::lexical_cast<int>(command.args["gearProcCameraContrast"]);
                    storedSettings.gearProcCameraSaturation = boost::lexical_cast<int>(command.args["gearProcCameraSaturation"]);
                    storedSettings.gearProcCameraHue = boost::lexical_cast<int>(command.args["gearProcCameraHue"]);
                    storedSettings.gearProcCameraAutoWB = boost::lexical_cast<bool>(command.args["gearProcCameraAutoWB"]);
                    storedSettings.gearProcCameraExposure = boost::lexical_cast<int>(command.args["gearProcCameraExposure"]);
                    storedSettings.gearProcCameraAutoGain = boost::lexical_cast<bool>(command.args["gearProcCameraAutoGain"]);
                    storedSettings.gearProcCameraGain = boost::lexical_cast<int>(command.args["gearProcCameraGain"]);
                    storedSettings.gearProcCameraVFlip = boost::lexical_cast<bool>(command.args["gearProcCameraVFlip"]);
                    storedSettings.gearProcCameraHFlip = boost::lexical_cast<bool>(command.args["gearProcCameraHFlip"]);
                    storedSettings.gearProcCameraManualExposure = boost::lexical_cast<bool>(command.args["gearProcCameraManualExposure"]);
                    break;
                case SETTINGS_GOAL_STREAM_CAMERA:
                    storedSettings.goalStreamCameraBrightness = boost::lexical_cast<int>(command.args["goalStreamCameraBrightness"]);
                    storedSettings.goalStreamCameraContrast = boost::lexical_cast<int>(command.args["goalStreamCameraContrast"]);
                    storedSettings.goalStreamCameraSaturation = boost::lexical_cast<int>(command.args["goalStreamCameraSaturation"]);
                    storedSettings.goalStreamCameraHue = boost::lexical_cast<int>(command.args["goalStreamCameraHue"]);
                    storedSettings.goalStreamCameraAutoWB = boost::lexical_cast<bool>(command.args["goalStreamCameraAutoWB"]);
                    storedSettings.goalStreamCameraExposure = boost::lexical_cast<int>(command.args["goalStreamCameraExposure"]);
                    storedSettings.goalStreamCameraAutoGain = boost::lexical_cast<bool>(command.args["goalStreamCameraAutoGain"]);
                    storedSettings.goalStreamCameraGain = boost::lexical_cast<int>(command.args["goalStreamCameraGain"]);
                    storedSettings.goalStreamCameraVFlip = boost::lexical_cast<bool>(command.args["goalStreamCameraVFlip"]);
                    storedSettings.goalStreamCameraHFlip = boost::lexical_cast<bool>(command.args["goalStreamCameraHFlip"]);
                    storedSettings.goalStreamCameraManualExposure = boost::lexical_cast<bool>(command.args["goalStreamCameraManualExposure"]);
                    break;
                case SETTINGS_GEAR_STREAM_CAMERA:
                    storedSettings.gearStreamCameraBrightness = boost::lexical_cast<int>(command.args["gearStreamCameraBrightness"]);
                    storedSettings.gearStreamCameraContrast = boost::lexical_cast<int>(command.args["gearStreamCameraContrast"]);
                    storedSettings.gearStreamCameraSaturation = boost::lexical_cast<int>(command.args["gearStreamCameraSaturation"]);
                    storedSettings.gearStreamCameraHue = boost::lexical_cast<int>(command.args["gearStreamCameraHue"]);
                    storedSettings.gearStreamCameraAutoWB = boost::lexical_cast<bool>(command.args["gearStreamCameraAutoWB"]);
                    storedSettings.gearStreamCameraExposure = boost::lexical_cast<int>(command.args["gearStreamCameraExposure"]);
                    storedSettings.gearStreamCameraAutoGain = boost::lexical_cast<bool>(command.args["gearStreamCameraAutoGain"]);
                    storedSettings.gearStreamCameraGain = boost::lexical_cast<int>(command.args["gearStreamCameraGain"]);
                    storedSettings.gearStreamCameraVFlip = boost::lexical_cast<bool>(command.args["gearStreamCameraVFlip"]);
                    storedSettings.gearStreamCameraHFlip = boost::lexical_cast<bool>(command.args["gearStreamCameraHFlip"]);
                    storedSettings.gearStreamCameraManualExposure = boost::lexical_cast<bool>(command.args["gearStreamCameraManualExposure"]);
                    break;
                case SETTINGS_GOAL_PROC:
                    storedSettings.goalProcHLower = boost::lexical_cast<int>(command.args["goalProcHLower"]);
                    storedSettings.goalProcSLower = boost::lexical_cast<int>(command.args["goalProcSLower"]);
                    storedSettings.goalProcVLower = boost::lexical_cast<int>(command.args["goalProcVLower"]);
                    storedSettings.goalProcHUpper = boost::lexical_cast<int>(command.args["goalProcHUpper"]);
                    storedSettings.goalProcSUpper = boost::lexical_cast<int>(command.args["goalProcSUpper"]);
                    storedSettings.goalProcVUpper = boost::lexical_cast<int>(command.args["goalProcVUpper"]);
                    storedSettings.goalMinArea = boost::lexical_cast<double>(command.args["goalMinArea"]);
                    storedSettings.goalMinPerimeter = boost::lexical_cast<double>(command.args["goalMinPerimeter"]);
                    storedSettings.goalMinWidth = boost::lexical_cast<double>(command.args["goalMinWidth"]);
                    storedSettings.goalMaxWidth = boost::lexical_cast<double>(command.args["goalMaxWidth"]);
                    storedSettings.goalMinHeight = boost::lexical_cast<double>(command.args["goalMinHeight"]);
                    storedSettings.goalMaxHeight = boost::lexical_cast<double>(command.args["goalMaxHeight"]);
                    storedSettings.goalMinSolidity = boost::lexical_cast<double>(command.args["goalMinSolidity"]);
                    storedSettings.goalMaxSolidity = boost::lexical_cast<double>(command.args["goalMaxSolidity"]);
                    storedSettings.goalMinVertices = boost::lexical_cast<double>(command.args["goalMinVertices"]);
                    storedSettings.goalMaxVertices = boost::lexical_cast<double>(command.args["goalMaxVertices"]);
                    storedSettings.goalMinRatio = boost::lexical_cast<double>(command.args["goalMinRatio"]);
                    storedSettings.goalMaxRatio = boost::lexical_cast<double>(command.args["goalMaxRatio"]);
                    break;
                case SETTINGS_GEAR_PROC:
                    storedSettings.gearProcHLower = boost::lexical_cast<int>(command.args["gearProcHLower"]);
                    storedSettings.gearProcSLower = boost::lexical_cast<int>(command.args["gearProcSLower"]);
                    storedSettings.gearProcVLower = boost::lexical_cast<int>(command.args["gearProcVLower"]);
                    storedSettings.gearProcHUpper = boost::lexical_cast<int>(command.args["gearProcHUpper"]);
                    storedSettings.gearProcSUpper = boost::lexical_cast<int>(command.args["gearProcSUpper"]);
                    storedSettings.gearProcVUpper = boost::lexical_cast<int>(command.args["gearProcVUpper"]);
                    storedSettings.gearMinArea = boost::lexical_cast<double>(command.args["gearMinArea"]);
                    storedSettings.gearMinPerimeter = boost::lexical_cast<double>(command.args["gearMinPerimeter"]);
                    storedSettings.gearMinWidth = boost::lexical_cast<double>(command.args["gearMinWidth"]);
                    storedSettings.gearMaxWidth = boost::lexical_cast<double>(command.args["gearMaxWidth"]);
                    storedSettings.gearMinHeight = boost::lexical_cast<double>(command.args["gearMinHeight"]);
                    storedSettings.gearMaxHeight = boost::lexical_cast<double>(command.args["gearMaxHeight"]);
                    storedSettings.gearMinSolidity = boost::lexical_cast<double>(command.args["gearMinSolidity"]);
                    storedSettings.gearMaxSolidity = boost::lexical_cast<double>(command.args["gearMaxSolidity"]);
                    storedSettings.gearMinVertices = boost::lexical_cast<double>(command.args["gearMinVertices"]);
                    storedSettings.gearMaxVertices = boost::lexical_cast<double>(command.args["gearMaxVertices"]);
                    storedSettings.gearMinRatio = boost::lexical_cast<double>(command.args["gearMinRatio"]);
                    storedSettings.gearMaxRatio = boost::lexical_cast<double>(command.args["gearMaxRatio"]);
                    break;
                case SETTINGS_STREAM_COMPRESSION:
                    storedSettings.streamCompression = boost::lexical_cast<int>(command.args["streamCompression"]);
                    break;
                case MODE_GOAL_PROC:
                    setGoalCamera(PROC);
                    break;
                case MODE_GOAL_STREAM:
                    setGoalCamera(STREAM);
                    break;
                case MODE_GEAR_PROC:
                    setGearCamera(PROC);
                    break;
                case MODE_GEAR_STREAM:
                    setGearCamera(STREAM);
                    break;
                case MODE_STREAMER_OFF:
                    streamer->setMode(Streamer::StreamType::OFF);
                    break;
                case MODE_STREAMER_GOAL:
                    streamer->setMode(Streamer::StreamType::GOAL);
                    break;
                case MODE_STREAMER_GEAR:
                    streamer->setMode(Streamer::StreamType::GEAR);
                    break;
                case ACTION_WRITE_CONFIG:
                    storedSettings.writeToFile("config.txt"); //Write the config out to the file
                    break;
                case ACTION_RESET_CONFIG:
                    storedSettings = config; //Reset the stored settings to the originals
                    goalProc->subConfig(storedSettings);
                    gearProc->subConfig(storedSettings);
                    setGoalCamera(goalCameraMode);
                    setGearCamera(gearCameraMode);
                    break;

            }
        }
    //LCOV_EXCL_START
        //This should never run, so we exclude it from coverage
    } catch (...) { //Handle any errors gracefully
        Log::w(ld, "Invalid request of type [" + std::to_string(command.command) + "]");
    }
    //LCOV_EXCL_STOP
}

void Controller::postAction(ParsedCommand command) {
    if (!(storedSettings == lastSettings)) { //If any settings have changed
        try {
            switch (command.command) {
                case SETTINGS_GOAL_PROC_CAMERA:
                    if (goalCameraMode == PROC) { //If the goal camera is already in proc mode
                        setGoalCamera(PROC); //Update the settings
                    }
                    break;
                case SETTINGS_GEAR_PROC_CAMERA:
                    if (gearCameraMode == PROC) { //If the gear camera is already in proc mode
                        setGearCamera(PROC); //Update the settings
                    }
                    break;
                case SETTINGS_GOAL_STREAM_CAMERA:
                    if (goalCameraMode == STREAM) { //If the goal camera is already in stream mode
                        setGoalCamera(STREAM); //Update the settings
                    }
                    break;
                case SETTINGS_GEAR_STREAM_CAMERA:
                    if (gearCameraMode == STREAM) { //If the gear camera is already in stream mode
                        setGearCamera(STREAM); //Update the settings
                    }
                    break;
                case SETTINGS_GOAL_PROC:
                    goalProc->subConfig(storedSettings); //Update the config in the goal processor
                    break;
                case SETTINGS_GEAR_PROC:
                    gearProc->subConfig(storedSettings); //Update the config in the gear processor
                    break;
                case SETTINGS_STREAM_COMPRESSION:
                    streamer->setCompression(storedSettings.streamCompression);
                    break;
            }
        //LCOV_EXCL_START
            //This should never run, so we exclude it from coverage
        } catch (...) {
            Log::w(ld, "Error running post actions for [" + std::to_string(command.command) + "]");
        }
        //LCOV_EXCL_STOP
    }
}

void Controller::run() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.setsockopt(ZMQ_RCVTIMEO, 30);
    socket.bind("tcp://*:" + std::to_string(port));
    std::string latestRaw;
    ParsedCommand latest;
    std::string response;
    while(!boost::this_thread::interruption_requested()) {
        latestRaw = s_recv(socket);
        Log::d(ld, "Got Request: [" + latestRaw + "]");
        if (latestRaw != "") { //If there wasn't a timeout
            lastSettings = storedSettings; //Store the last settings so we can compare
            latest = parseCommand(latestRaw); //Parse the command
            if (latest.command == PING) { //If the latest request is a ping request
                response = "PONG#"; //Respond to a ping
            } else {
                react(latest); //React to the command
                postAction(latest); //Run any post actions
                response = storedSettings.hash(); //Respond to the command (we always respond with a list of our current settings)
            }
            s_send(socket, response);
        }
    }
}