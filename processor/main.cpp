//
// Created by cameronearle on 12/25/16.
//

#include <opencv2/videoio.hpp>
#include <cv.hpp>

#include "boost/thread/thread.hpp"
#include "src/utility/Log.hpp"
#include "src/utility/ConfigParser.hpp"
#include "src/utility/Debug.hpp"
#include "src/abstraction/Camera.hpp"
#include "src/networking/DataStreamer.hpp"
#include "src/networking/Controller.hpp"
#include "src/networking/Streamer.hpp"
#include "src/processing/GoalProc.hpp"
#include "src/processing/GearProc.hpp"

#include <boost/algorithm/string.hpp>

#include <unistd.h>
#include <termios.h>
#include <linux/v4l2-controls.h>


/**
 * A linux port of the windows method getch, which captures a single character from cin, and returns automatically.
 * Characters stack as more are input
 * @return The character gotten
 */
char getch() {
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    return buf;
}

/**
 * Main method, entry and exit point for this program
 * @param argc Number of command line arguments present
 * @param argv List of command line arguments
 * @return Exit code
 */
int main(int argc, char *argv[]) {
    std::string ld = "MAIN";

    //BASIC INIT
    Log::init(Log::Level::INFO, true); //Initialize the logger to record info and higher messages and use a file

    ConfigParser parser(vector<string>(argv+1, argv + argc)); //Initialize a configuration parser
    Configuration config = parser.getSettings(); //Get the settings from the config parser

    Log::i(ld, "Finished parsing config");

    Log::setDoDebug(config.showDebugText);
    Debug::init(config); //Initialize the debug manager

    //THREADING INIT
    boost::thread_group providerGroup;   //Thread group for provider threads
    boost::thread_group networkingGroup; //Thread group for networking threads
    boost::thread_group processingGroup; //Thread group for processing threads

    //OBJECT INIT
    Camera goalProcCamera(config, Camera::CameraType::GOAL_PROCESSING); //Set up the processing camera from the config
    Camera gearProcCamera(config, Camera::CameraType::GEAR_PROCESSING);
    if (config.useGoalCamera) { //If we are using the goal camera
        goalProcCamera.setup(); //Set it up
    }
    if (config.useGearCamera) { //If we are using the gear camera
        gearProcCamera.setup(); //Set it up
    }
    MatProvider goalProcProvider = goalProcCamera.getProvider(); //Get a MatProvider for the processing camera
    MatProvider gearProcProvider = gearProcCamera.getProvider();
    goalProcProvider.setName("GoalProc"); //Set the names of the MatProviders for logging purposes
    gearProcProvider.setName("GearProc");

    DataStreamer dataStreamer(config.networkBasePort + 1); //Creates a data streamer to send processing data to the RIO
    GoalProc goalProc(config, &goalProcProvider, &dataStreamer); //Creates a processor to be run in a thread that processes images and sends output to the dataStreamer
    GearProc gearProc(config, &gearProcProvider, &dataStreamer);
    Streamer streamer(config.networkBasePort + 2, &goalProcProvider, &gearProcProvider, config.streamCompression);
    Controller controller(config, &goalProcCamera, &gearProcCamera, &goalProc, &gearProc, &streamer, config.networkBasePort + 3);

    Log::i(ld, "Initialization Complete!");

    //THREADING START
    providerGroup.create_thread(boost::bind(&MatProvider::run, &goalProcProvider)); //Start the thread for the processing matprovider
    providerGroup.create_thread(boost::bind(&MatProvider::run, &gearProcProvider));

    networkingGroup.create_thread(boost::bind(&DataStreamer::run, &dataStreamer)); //Start the thread for the network data streamer
    networkingGroup.create_thread(boost::bind(&Streamer::run, &streamer));
    networkingGroup.create_thread(boost::bind(&Controller::run, &controller));
    processingGroup.create_thread(boost::bind(&GoalProc::run, &goalProc)); //Start the main processing thread
    processingGroup.create_thread(boost::bind(&GearProc::run, &gearProc));

    //AT THIS POINT IT IS ASSUMED THAT ALL THREADS ARE STARTED OR IN THE PROCESS OF STARTING
    Log::i(ld, "VISION STARTED, GOOD LUCK 401!!!");

    bool loop = true;
    int exitCode = 1;
    while (loop) { //Loop the main thread to keep it alive
        switch (getch()) {
            case 'q':
                loop = false; //Break this loop
                exitCode = 0; //Set the exit code to standard exit
                break;
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(10)); //Keep the processor happy
    }

    Log::i(ld, "Stop signal recieved, exiting with code " + std::to_string(exitCode));

    //AT THIS POINT IT IS ASSUMED THAT ALL THREADS SHOULD BE SIGNALED TO STOP

    processingGroup.interrupt_all(); //Signal all processing threads to stop
    processingGroup.join_all(); //Wait for all processing threads to stop

    dataStreamer.addToQueue(StreamData::Type::SHUTDOWN); //Tell the robot we are shutting down

    //It is now safe to stop networking, since all processing has stopped
    networkingGroup.interrupt_all(); //Signal all networking threads to stop
    networkingGroup.join_all(); //Wait for all networking threads to stop

    //It is now safe to stop provider threads, since all streaming has stopped
    providerGroup.interrupt_all(); //Signal all provider threads to stop
    providerGroup.join_all(); //Wait for all provider threads to stop

    //Finally, tell all camera instances to close
    goalProcCamera.close();
    //gearProcCamera.close();

    Log::i(ld, "All threads terminated, shutting down!");

    return exitCode; //Allow signaling to the loop script for auto restart

}