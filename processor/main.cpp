//
// Created by cameronearle on 12/25/16.
//

#include <opencv2/videoio.hpp>
#include <cv.hpp>

#include "boost/thread/thread.hpp"
#include "src/abstraction/MatProvider.hpp"
#include "src/utility/Log.hpp"
#include "src/abstraction/Camera.hpp"
#include "src/processing/Processor.hpp"
#include "src/networking/Streamer.hpp"
#include "src/utility/OutWindows.hpp"
#include "src/utility/ConfigParser.hpp"
#include <vector>
#include <iostream>

#include <unistd.h>
#include <termios.h>

char getch() { //A function copied from StackOverflow to grab keypresses
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

int main(int argc, char *argv[]) {
    //INITIALIZATION
    Log::init(Log::Level::DEBUG, true); //Initialize the logger to record debug messages and use a file

    ConfigParser parser(vector<string>(argv+1, argv + argc)); //Initialize a configuration parser
    Configuration config = parser.getSettings(); //Get the settings from the config parser

    OutWindows::init(config.showDebugWindows, vector<string>{"Frame"}); //Initialize the debug window manager


    Camera processingCamera(0); //Initialize the processing camera
    //Camera processingCamera(config); //Initialize the processing camera

    //Camera streamCamera(config, Camera::CameraType::STREAM); //Initialize the stream camera

    processingCamera.setup(); //Set up the processing camera
    //streamCamera.setup(); //Set up the stream camera


    MatProvider processingProvider = processingCamera.getProvider(); //Get a MatProvider for the processing camera
    //MatProvider streamProvider = streamCamera.getProvider(); //Get a MatProvider for the stream camera

    processingProvider.setName("Processing"); //Set the names of the MatProviders for logging purposes
    //streamProvider.setName("Stream");

    boost::thread_group tgroup; //Create a group to hold our threads

    tgroup.create_thread(boost::bind(&MatProvider::run, processingProvider)); //Create a thread for the processing provider
    //tgroup.create_thread(boost::bind(&MatProvider::run, streamProvider)); //Create a thread for the stream provider

    Processor processor(config, processingProvider);

    tgroup.create_thread(boost::bind(&Processor::run, processor));

    Streamer streamer(5800, processingProvider);

    tgroup.create_thread(boost::bind(&Streamer::run, streamer));


    //AT THIS POINT IT IS ASSUMED THAT ALL THREADS ARE STARTED OR IN THE PROCESS OF STARTING

    while (true) { //Loop the main thread to keep it alive
        if (getch() == 'q') { //If q is pressed
            break; //Break this loop, at which point the program will begin shutting down
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(10)); //Keep the processor happy
    }

    //AT THIS POINT IT IS ASSUMED THAT ALL THREADS SHOULD BE SIGNALED TO STOP

    tgroup.interrupt_all(); //Tell all threads it's time to stop
    tgroup.join_all(); //Wait for the threads to stop

}