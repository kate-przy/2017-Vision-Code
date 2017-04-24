//
// Created by cameronearle on 3/26/17.
//

#include <gtest/gtest.h>
#include <zhelpers.hpp>
#include <boost/thread/thread.hpp>
#include "TestingConstants.hpp"
#include "../../processor/src/networking/DataStreamer.hpp"
#include "../../processor/src/networking/Streamer.hpp"
#include "MockCamera.hpp"
#include "MockProcessor.hpp"
#include "MockStreamer.hpp"
#include "../../processor/src/networking/Controller.hpp"
#include <libv4l2.h>
#include <linux/v4l2-controls.h>
#include <iostream>
#include <fstream>


void addStreamData(DataStreamer *streamer, StreamData data) {
    while (!boost::this_thread::interruption_requested()) {
        streamer->addToQueue(data);
        boost::this_thread::sleep(boost::posix_time::milliseconds(500));
    }
}

TEST(networking, data_streamer_goal_invalid) {
    /// EXPECTATIONS
    std::string EXPECTED_RESPONSE = "GOAL_DATA_INVALID#";

    /// TEST
    zmq::context_t context(1);                     //SOCKET SETUP
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT); //Wait up to 1 second
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT)); //Connect the socket

    DataStreamer dataStreamer(TestingConstants::Networking::TEST_PORT); //Set up the data streamer
    boost::thread dataStreamerThread(boost::bind(&DataStreamer::run, &dataStreamer)); //Start the data streamer

    StreamData toSend(StreamData::Type::GOAL_DATA_INVALID);
    boost::thread dataAdderThread(boost::bind(&addStreamData, &dataStreamer, toSend));
    std::string response = s_recv(socket);
    dataAdderThread.interrupt();
    dataAdderThread.join();
    socket.close();
    dataStreamerThread.interrupt();
    dataStreamerThread.join();
    ASSERT_EQ(response, EXPECTED_RESPONSE);
}

TEST(networking, data_streamer_goal_valid) {
    /// EXPECTATIONS
    double distance = 40.1;
    double pitch = 4.01;
    double yaw = .401;
    std::string EXPECTED_RESPONSE = "GOAL_DATA#distance:40.100000,pitch:4.010000,yaw:0.401000";

    /// TEST
    zmq::context_t context(1);                     //SOCKET SETUP
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT); //Wait up to 1 second
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT)); //Connect the socket

    DataStreamer dataStreamer(TestingConstants::Networking::TEST_PORT); //Set up the data streamer
    boost::thread dataStreamerThread(boost::bind(&DataStreamer::run, &dataStreamer)); //Start the data streamer

    StreamData toSend(distance, pitch, yaw);
    boost::thread dataAdderThread(boost::bind(&addStreamData, &dataStreamer, toSend));
    std::string response = s_recv(socket);
    dataAdderThread.interrupt();
    dataAdderThread.join();
    socket.close();
    dataStreamerThread.interrupt();
    dataStreamerThread.join();
    ASSERT_EQ(response, EXPECTED_RESPONSE);
}

TEST(networking, data_streamer_gear_invalid) {
    /// EXPECTATIONS
    std::string EXPECTED_RESPONSE = "GEAR_DATA_INVALID#";

    /// TEST
    zmq::context_t context(1);                     //SOCKET SETUP
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT); //Wait up to 1 second
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT)); //Connect the socket

    DataStreamer dataStreamer(TestingConstants::Networking::TEST_PORT); //Set up the data streamer
    boost::thread dataStreamerThread(boost::bind(&DataStreamer::run, &dataStreamer)); //Start the data streamer

    StreamData toSend(StreamData::Type::GEAR_DATA_INVALID);
    boost::thread dataAdderThread(boost::bind(&addStreamData, &dataStreamer, toSend));
    std::string response = s_recv(socket);
    dataAdderThread.interrupt();
    dataAdderThread.join();
    socket.close();
    dataStreamerThread.interrupt();
    dataStreamerThread.join();
    ASSERT_EQ(response, EXPECTED_RESPONSE);
}

TEST(networking, data_streamer_gear_valid) {
    /// EXPECTATIONS
    double distance = 40.1;
    StreamData::Strafe strafe = StreamData::Strafe::RIGHT; //Because why not?  Maybe make this random in the future
    double yaw = 4.01;
    std::string EXPECTED_RESPONSE = "GEAR_DATA#distance40.100000,yaw:4.010000,strafe:1";

    /// TEST
    zmq::context_t context(1);                     //SOCKET SETUP
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT); //Wait up to 1 second
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT)); //Connect the socket

    DataStreamer dataStreamer(TestingConstants::Networking::TEST_PORT); //Set up the data streamer
    boost::thread dataStreamerThread(boost::bind(&DataStreamer::run, &dataStreamer)); //Start the data streamer

    StreamData toSend(distance, yaw, strafe);
    boost::thread dataAdderThread(boost::bind(&addStreamData, &dataStreamer, toSend));
    std::string response = s_recv(socket);
    dataAdderThread.interrupt();
    dataAdderThread.join();
    socket.close();
    dataStreamerThread.interrupt();
    dataStreamerThread.join();
    ASSERT_EQ(response, EXPECTED_RESPONSE);
}

TEST(networking, data_streamer_invalid) {
    /// EXPECTATIONS
    std::string EXPECTED_RESPONSE = "INVALID#";

    /// TEST
    zmq::context_t context(1);                     //SOCKET SETUP
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT); //Wait up to 1 second
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT)); //Connect the socket

    DataStreamer dataStreamer(TestingConstants::Networking::TEST_PORT); //Set up the data streamer
    boost::thread dataStreamerThread(boost::bind(&DataStreamer::run, &dataStreamer)); //Start the data streamer

    StreamData toSend;
    boost::thread dataAdderThread(boost::bind(&addStreamData, &dataStreamer, toSend));
    std::string response = s_recv(socket);
    dataAdderThread.interrupt();
    dataAdderThread.join();
    socket.close();
    dataStreamerThread.interrupt();
    dataStreamerThread.join();
    ASSERT_EQ(response, EXPECTED_RESPONSE);
}

TEST(networking, data_streamer_shutdown) {
    /// EXPECTATIONS
    std::string EXPECTED_RESPONSE = "SHUTDOWN#";

    /// TEST
    zmq::context_t context(1);                     //SOCKET SETUP
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT); //Wait up to 1 second
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT)); //Connect the socket

    DataStreamer dataStreamer(TestingConstants::Networking::TEST_PORT); //Set up the data streamer
    boost::thread dataStreamerThread(boost::bind(&DataStreamer::run, &dataStreamer)); //Start the data streamer

    StreamData toSend(StreamData::Type::SHUTDOWN);
    boost::thread dataAdderThread(boost::bind(&addStreamData, &dataStreamer, toSend));
    std::string response = s_recv(socket);
    dataAdderThread.interrupt();
    dataAdderThread.join();
    socket.close();
    dataStreamerThread.interrupt();
    dataStreamerThread.join();
    ASSERT_EQ(response, EXPECTED_RESPONSE);
}

TEST(networking, data_streamer_operators) {
    StreamData invalid1;
    StreamData invalid2;
    StreamData shutdown1(StreamData::Type::SHUTDOWN);
    StreamData shutdown2(StreamData::Type::SHUTDOWN);
    StreamData goalInvalid1(StreamData::Type::GOAL_DATA_INVALID);
    StreamData goalInvalid2(StreamData::Type::GOAL_DATA_INVALID);
    StreamData gearInvalid1(StreamData::Type::GEAR_DATA_INVALID);
    StreamData gearInvalid2(StreamData::Type::GEAR_DATA_INVALID);
    StreamData goal1(1, 2, 3);
    StreamData goal2(1, 2, 3);
    StreamData goal3(1.1, 2, 3);
    StreamData gear1(1, 2, StreamData::Strafe::LEFT);
    StreamData gear2(1, 2, StreamData::Strafe::LEFT);
    StreamData gear3(1, 2, StreamData::Strafe::RIGHT);

    ASSERT_TRUE(invalid1 == invalid2);
    ASSERT_TRUE(shutdown1 == shutdown2);
    ASSERT_TRUE(goalInvalid1 == goalInvalid2);
    ASSERT_TRUE(gearInvalid1 == gearInvalid2);

    ASSERT_TRUE(goal1 == goal2);
    ASSERT_TRUE(goal1 != goal3);
    ASSERT_TRUE(gear1 == gear2);
    ASSERT_TRUE(gear1 != gear3);

    ASSERT_TRUE(goalInvalid1 != gearInvalid1); //Make sure type checking works
    ASSERT_TRUE(goal1 != gear1);
}

TEST(networking, frame_streamer_unusable) {
    Streamer streamer;
    boost::thread(boost::bind(&Streamer::run, &streamer)).join();
    //This test will lock up if it fails
}

TEST(networking, frame_streamer_usable) {
    MatProvider goalProvider;
    MatProvider gearProvider;
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT); //Wait up to 10 seconds
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT));
    Streamer streamer(TestingConstants::Networking::TEST_PORT, &goalProvider, &gearProvider);
    boost::thread streamerThread(boost::bind(&Streamer::run, &streamer));
    ASSERT_TRUE(s_recv(socket) != ""); //Ensure that we get some kind of data back
    streamerThread.interrupt();
    streamerThread.join();
    socket.close();
}

TEST(networking, frame_streamer_compression) {
    Streamer streamer(0, nullptr, nullptr);
    ASSERT_EQ(streamer.getCompression(), 30); //Ensure that the default compression is 30
    streamer.setCompression(0);
    ASSERT_EQ(streamer.getCompression(), 0);
    streamer.setCompression(100);
    ASSERT_EQ(streamer.getCompression(), 100);
    streamer.setCompression(110); //This is out of bounds, it should still be 100
    ASSERT_FALSE(streamer.getCompression() > 100);
    streamer.setCompression(-10);
    ASSERT_FALSE(streamer.getCompression() < 0);
}

TEST(networking, frame_streamer_modes) {
    MatProvider goalProvider;
    MatProvider gearProvider;
    Streamer streamer(TestingConstants::Networking::TEST_PORT, &goalProvider, &gearProvider);
    boost::thread streamerThread(boost::bind(&Streamer::run, &streamer));
    boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    streamer.setMode(Streamer::StreamType::OFF);
    boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    streamer.setMode(Streamer::StreamType::GOAL);
    boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    streamer.setMode(Streamer::StreamType::GEAR);
    boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    streamerThread.interrupt();
    streamerThread.join();
}

TEST(networking, controller_init_ping) {
    /// EXPECTATIONS
    std::string pingResponse = "PONG#";

    /// TEST
    std::string response;
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT);
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT)); //Connect the socket

    Configuration config;

    Controller controller(config, nullptr, nullptr, nullptr, nullptr, nullptr, TestingConstants::Networking::TEST_PORT);
    boost::thread controllerThread(boost::bind(&Controller::run, &controller)); //Start the thread
    s_send(socket, "INIT#");
    response = s_recv(socket);
    ASSERT_TRUE(response.length() > 7); //Ensure that we got something back, and it is at least "CONFIG#"
    s_send(socket, "PING#");
    response = s_recv(socket);
    ASSERT_EQ(response, pingResponse);
    socket.close();
    controllerThread.interrupt();
    controllerThread.join();
}

TEST(networking, controller_camera_set) {
    MockProcessor goalProc;
    MockProcessor gearProc;
    MockCamera goalCamera;
    MockCamera gearCamera;
    MockStreamer streamer;
    Configuration config;

    zmq::context_t context(1);                     //SOCKET SETUP
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT); //Wait up to 1 second
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT)); //Connect the socket

    Controller controller(config, &goalCamera, &gearCamera, &goalProc, &gearProc, &streamer, TestingConstants::Networking::TEST_PORT);
    boost::thread controllerThread(boost::bind(&Controller::run, &controller)); //Start the controller thread
    EXPECT_CALL(streamer, setMode(Streamer::StreamType::OFF));
    s_send(socket, "MODE_STREAMER_OFF#");
    s_recv(socket); //Wait up to one second
    EXPECT_CALL(streamer, setMode(Streamer::StreamType::GOAL));
    s_send(socket, "MODE_STREAMER_GOAL#");
    s_recv(socket);
    EXPECT_CALL(streamer, setMode(Streamer::StreamType::GEAR));
    s_send(socket, "MODE_STREAMER_GEAR#");
    s_recv(socket);
    socket.close(); //Close the socket
    controllerThread.interrupt();
    controllerThread.join();
}

TEST(networking, controller_goal_proc_camera_settings) {
    TestingConstants::setRand();
    /// EXPECTATIONS
    int brightness = TestingConstants::randInt(256);
    int contrast = TestingConstants::randInt(256);
    int saturation = TestingConstants::randInt(256);
    int hue = TestingConstants::randInt(256);
    bool autoWB = TestingConstants::randInt(2);
    int exposure = TestingConstants::randInt(256);
    bool autoGain = TestingConstants::randInt(2);
    int gain = TestingConstants::randInt(256);
    bool vFlip = TestingConstants::randInt(2);
    bool hFlip = TestingConstants::randInt(2);
    bool manualExposure = TestingConstants::randInt(2);

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT);
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT));

    MockCamera goalCamera;
    Configuration config;
    Controller controller(config, &goalCamera, nullptr, nullptr, nullptr, nullptr, TestingConstants::Networking::TEST_PORT);
    boost::thread controllerThread(boost::bind(&Controller::run, &controller));
    s_send(socket, "MODE_GOAL_PROC#");
    s_recv(socket);
    std::string request = "SETTINGS_GOAL_PROC_CAMERA#";
    request += "goalProcCameraBrightness:" + std::to_string(brightness) + ",";
    request += "goalProcCameraContrast:" + std::to_string(contrast) + ",";
    request += "goalProcCameraSaturation:" + std::to_string(saturation) + ",";
    request += "goalProcCameraHue:" + std::to_string(hue) + ",";
    request += "goalProcCameraAutoWB:" + std::to_string(autoWB) + ",";
    request += "goalProcCameraExposure:" + std::to_string(exposure) + ",";
    request += "goalProcCameraAutoGain:" + std::to_string(autoGain) + ",";
    request += "goalProcCameraGain:" + std::to_string(gain) + ",";
    request += "goalProcCameraVFlip:" + std::to_string(vFlip) + ",";
    request += "goalProcCameraHFlip:" + std::to_string(hFlip) + ",";
    request += "goalProcCameraManualExposure:" + std::to_string(manualExposure);

    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_BRIGHTNESS, brightness));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_CONTRAST, contrast));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_SATURATION, saturation));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_HUE, hue));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_AUTO_WHITE_BALANCE, autoWB));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_EXPOSURE, exposure));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_AUTOGAIN, autoGain));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_GAIN, gain));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_VFLIP, vFlip));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_HFLIP, hFlip));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_EXPOSURE_AUTO, manualExposure));

    s_send(socket, request);
    s_recv(socket);
    socket.close();
    controllerThread.interrupt();
    controllerThread.join();
}

TEST(networking, controller_gear_proc_camera_settings) {
    TestingConstants::setRand();
    /// EXPECTATIONS
    int brightness = TestingConstants::randInt(256);
    int contrast = TestingConstants::randInt(256);
    int saturation = TestingConstants::randInt(256);
    int hue = TestingConstants::randInt(256);
    bool autoWB = TestingConstants::randInt(2);
    int exposure = TestingConstants::randInt(256);
    bool autoGain = TestingConstants::randInt(2);
    int gain = TestingConstants::randInt(256);
    bool vFlip = TestingConstants::randInt(2);
    bool hFlip = TestingConstants::randInt(2);
    bool manualExposure = TestingConstants::randInt(2);

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT);
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT));

    MockCamera gearCamera;
    Configuration config;
    Controller controller(config, nullptr, &gearCamera, nullptr, nullptr, nullptr, TestingConstants::Networking::TEST_PORT);
    boost::thread controllerThread(boost::bind(&Controller::run, &controller));
    s_send(socket, "MODE_GEAR_PROC#");
    s_recv(socket);
    std::string request = "SETTINGS_GEAR_PROC_CAMERA#";
    request += "gearProcCameraBrightness:" + std::to_string(brightness) + ",";
    request += "gearProcCameraContrast:" + std::to_string(contrast) + ",";
    request += "gearProcCameraSaturation:" + std::to_string(saturation) + ",";
    request += "gearProcCameraHue:" + std::to_string(hue) + ",";
    request += "gearProcCameraAutoWB:" + std::to_string(autoWB) + ",";
    request += "gearProcCameraExposure:" + std::to_string(exposure) + ",";
    request += "gearProcCameraAutoGain:" + std::to_string(autoGain) + ",";
    request += "gearProcCameraGain:" + std::to_string(gain) + ",";
    request += "gearProcCameraVFlip:" + std::to_string(vFlip) + ",";
    request += "gearProcCameraHFlip:" + std::to_string(hFlip) + ",";
    request += "gearProcCameraManualExposure:" + std::to_string(manualExposure);

    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_BRIGHTNESS, brightness));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_CONTRAST, contrast));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_SATURATION, saturation));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_HUE, hue));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_AUTO_WHITE_BALANCE, autoWB));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_EXPOSURE, exposure));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_AUTOGAIN, autoGain));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_GAIN, gain));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_VFLIP, vFlip));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_HFLIP, hFlip));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_EXPOSURE_AUTO, manualExposure));

    s_send(socket, request);
    s_recv(socket);
    socket.close();
    controllerThread.interrupt();
    controllerThread.join();
}

TEST(networking, controller_goal_stream_camera_settings) {
    TestingConstants::setRand();
    /// EXPECTATIONS
    int brightness = TestingConstants::randInt(256);
    int contrast = TestingConstants::randInt(256);
    int saturation = TestingConstants::randInt(256);
    int hue = TestingConstants::randInt(256);
    bool autoWB = TestingConstants::randInt(2);
    int exposure = TestingConstants::randInt(256);
    bool autoGain = TestingConstants::randInt(2);
    int gain = TestingConstants::randInt(256);
    bool vFlip = TestingConstants::randInt(2);
    bool hFlip = TestingConstants::randInt(2);
    bool manualExposure = TestingConstants::randInt(2);

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT);
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT));

    MockCamera goalCamera;
    Configuration config;
    Controller controller(config, &goalCamera, nullptr, nullptr, nullptr, nullptr, TestingConstants::Networking::TEST_PORT);
    boost::thread controllerThread(boost::bind(&Controller::run, &controller));
    s_send(socket, "MODE_GOAL_STREAM#");
    s_recv(socket);
    std::string request = "SETTINGS_GOAL_STREAM_CAMERA#";
    request += "goalStreamCameraBrightness:" + std::to_string(brightness) + ",";
    request += "goalStreamCameraContrast:" + std::to_string(contrast) + ",";
    request += "goalStreamCameraSaturation:" + std::to_string(saturation) + ",";
    request += "goalStreamCameraHue:" + std::to_string(hue) + ",";
    request += "goalStreamCameraAutoWB:" + std::to_string(autoWB) + ",";
    request += "goalStreamCameraExposure:" + std::to_string(exposure) + ",";
    request += "goalStreamCameraAutoGain:" + std::to_string(autoGain) + ",";
    request += "goalStreamCameraGain:" + std::to_string(gain) + ",";
    request += "goalStreamCameraVFlip:" + std::to_string(vFlip) + ",";
    request += "goalStreamCameraHFlip:" + std::to_string(hFlip) + ",";
    request += "goalStreamCameraManualExposure:" + std::to_string(manualExposure);

    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_BRIGHTNESS, brightness));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_CONTRAST, contrast));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_SATURATION, saturation));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_HUE, hue));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_AUTO_WHITE_BALANCE, autoWB));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_EXPOSURE, exposure));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_AUTOGAIN, autoGain));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_GAIN, gain));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_VFLIP, vFlip));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_HFLIP, hFlip));
    EXPECT_CALL(goalCamera, setProperty(V4L2_CID_EXPOSURE_AUTO, manualExposure));

    s_send(socket, request);
    s_recv(socket);
    socket.close();
    controllerThread.interrupt();
    controllerThread.join();
}

TEST(networking, controller_gear_stream_camera_settings) {
    TestingConstants::setRand();
    /// EXPECTATIONS
    int brightness = TestingConstants::randInt(256);
    int contrast = TestingConstants::randInt(256);
    int saturation = TestingConstants::randInt(256);
    int hue = TestingConstants::randInt(256);
    bool autoWB = TestingConstants::randInt(2);
    int exposure = TestingConstants::randInt(256);
    bool autoGain = TestingConstants::randInt(2);
    int gain = TestingConstants::randInt(256);
    bool vFlip = TestingConstants::randInt(2);
    bool hFlip = TestingConstants::randInt(2);
    bool manualExposure = TestingConstants::randInt(2);

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT);
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT));

    MockCamera gearCamera;
    Configuration config;
    Controller controller(config, nullptr, &gearCamera, nullptr, nullptr, nullptr, TestingConstants::Networking::TEST_PORT);
    boost::thread controllerThread(boost::bind(&Controller::run, &controller));
    s_send(socket, "MODE_GEAR_STREAM#");
    s_recv(socket);
    std::string request = "SETTINGS_GEAR_STREAM_CAMERA#";
    request += "gearStreamCameraBrightness:" + std::to_string(brightness) + ",";
    request += "gearStreamCameraContrast:" + std::to_string(contrast) + ",";
    request += "gearStreamCameraSaturation:" + std::to_string(saturation) + ",";
    request += "gearStreamCameraHue:" + std::to_string(hue) + ",";
    request += "gearStreamCameraAutoWB:" + std::to_string(autoWB) + ",";
    request += "gearStreamCameraExposure:" + std::to_string(exposure) + ",";
    request += "gearStreamCameraAutoGain:" + std::to_string(autoGain) + ",";
    request += "gearStreamCameraGain:" + std::to_string(gain) + ",";
    request += "gearStreamCameraVFlip:" + std::to_string(vFlip) + ",";
    request += "gearStreamCameraHFlip:" + std::to_string(hFlip) + ",";
    request += "gearStreamCameraManualExposure:" + std::to_string(manualExposure);

    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_BRIGHTNESS, brightness));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_CONTRAST, contrast));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_SATURATION, saturation));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_HUE, hue));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_AUTO_WHITE_BALANCE, autoWB));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_EXPOSURE, exposure));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_AUTOGAIN, autoGain));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_GAIN, gain));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_VFLIP, vFlip));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_HFLIP, hFlip));
    EXPECT_CALL(gearCamera, setProperty(V4L2_CID_EXPOSURE_AUTO, manualExposure));

    s_send(socket, request);
    s_recv(socket);
    socket.close();
    controllerThread.interrupt();
    controllerThread.join();
}

TEST(networking, controller_goal_proc_settings) {
    TestingConstants::setRand();
    /// EXPECTATIONS
    int hLower = TestingConstants::randInt(180);
    int sLower = TestingConstants::randInt(256);
    int vLower = TestingConstants::randInt(256);
    int hUpper = TestingConstants::randInt(180);
    int sUpper = TestingConstants::randInt(256);
    int vUpper = TestingConstants::randInt(256);
    double minArea = TestingConstants::randInt(500);
    double minPerimeter = TestingConstants::randInt(500);
    double minWidth = TestingConstants::randInt(500);
    double maxWidth = minWidth + TestingConstants::randInt(500);
    double minHeight = TestingConstants::randInt(500);
    double maxHeight = minHeight + TestingConstants::randInt(500);
    double minSolidity = TestingConstants::randInt(500);
    double maxSolidity = minSolidity + TestingConstants::randInt(500);
    double minVertices = TestingConstants::randInt(500);
    double maxVertices = minVertices + TestingConstants::randInt(500);
    double minRatio = TestingConstants::randInt(500);
    double maxRatio = minRatio + TestingConstants::randInt(500);
    

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT);
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT));

    MockProcessor goalProc;
    Configuration config;
    Controller controller(config, nullptr, nullptr, &goalProc, nullptr, nullptr, TestingConstants::Networking::TEST_PORT);
    boost::thread controllerThread(boost::bind(&Controller::run, &controller));
    std::string request = "SETTINGS_GOAL_PROC#";
    request += "goalProcHLower:" + std::to_string(hLower) + ",";
    request += "goalProcSLower:" + std::to_string(sLower) + ",";
    request += "goalProcVLower:" + std::to_string(vLower) + ",";
    request += "goalProcHUpper:" + std::to_string(hUpper) + ",";
    request += "goalProcSUpper:" + std::to_string(sUpper) + ",";
    request += "goalProcVUpper:" + std::to_string(vUpper) + ",";
    request += "goalMinArea:" + std::to_string(minArea) + ",";
    request += "goalMinPerimeter:" + std::to_string(minPerimeter) + ",";
    request += "goalMinWidth:" + std::to_string(minWidth) + ",";
    request += "goalMaxWidth:" + std::to_string(maxWidth) + ",";
    request += "goalMinHeight:" + std::to_string(minHeight) + ",";
    request += "goalMaxHeight:" + std::to_string(maxHeight) + ",";
    request += "goalMinSolidity:" + std::to_string(minSolidity) + ",";
    request += "goalMaxSolidity:" + std::to_string(maxSolidity) + ",";
    request += "goalMinVertices:" + std::to_string(minVertices) + ",";
    request += "goalMaxVertices:" + std::to_string(maxVertices) + ",";
    request += "goalMinRatio:" + std::to_string(minRatio) + ",";
    request += "goalMaxRatio:" + std::to_string(maxRatio);

    EXPECT_CALL(goalProc, subConfig(::testing::_)); //Ensure that at least something gets subbed in

    s_send(socket, request);
    s_recv(socket);

    Configuration newSettings = controller.getCurrentSettings();
    ASSERT_EQ(newSettings.goalProcHLower, hLower);
    ASSERT_EQ(newSettings.goalProcSLower, sLower);
    ASSERT_EQ(newSettings.goalProcVLower, vLower);
    ASSERT_EQ(newSettings.goalProcHUpper, hUpper);
    ASSERT_EQ(newSettings.goalProcSUpper, sUpper);
    ASSERT_EQ(newSettings.goalProcVUpper, vUpper);
    ASSERT_EQ(newSettings.goalMinArea, minArea);
    ASSERT_EQ(newSettings.goalMinPerimeter, minPerimeter);
    ASSERT_EQ(newSettings.goalMinWidth, minWidth);
    ASSERT_EQ(newSettings.goalMaxWidth, maxWidth);
    ASSERT_EQ(newSettings.goalMinHeight, minHeight);
    ASSERT_EQ(newSettings.goalMaxHeight, maxHeight);
    ASSERT_EQ(newSettings.goalMinSolidity, minSolidity);
    ASSERT_EQ(newSettings.goalMaxSolidity, maxSolidity);
    ASSERT_EQ(newSettings.goalMinVertices, minVertices);
    ASSERT_EQ(newSettings.goalMaxVertices, maxVertices);
    ASSERT_EQ(newSettings.goalMinRatio, minRatio);
    ASSERT_EQ(newSettings.goalMaxRatio, maxRatio);

    socket.close();
    controllerThread.interrupt();
    controllerThread.join();
}

TEST(networking, controller_gear_proc_settings) {
    TestingConstants::setRand();
    /// EXPECTATIONS
    int hLower = TestingConstants::randInt(180);
    int sLower = TestingConstants::randInt(256);
    int vLower = TestingConstants::randInt(256);
    int hUpper = TestingConstants::randInt(180);
    int sUpper = TestingConstants::randInt(256);
    int vUpper = TestingConstants::randInt(256);
    double minArea = TestingConstants::randInt(500);
    double minPerimeter = TestingConstants::randInt(500);
    double minWidth = TestingConstants::randInt(500);
    double maxWidth = minWidth + TestingConstants::randInt(500);
    double minHeight = TestingConstants::randInt(500);
    double maxHeight = minHeight + TestingConstants::randInt(500);
    double minSolidity = TestingConstants::randInt(500);
    double maxSolidity = minSolidity + TestingConstants::randInt(500);
    double minVertices = TestingConstants::randInt(500);
    double maxVertices = minVertices + TestingConstants::randInt(500);
    double minRatio = TestingConstants::randInt(500);
    double maxRatio = minRatio + TestingConstants::randInt(500);


    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT);
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT));

    MockProcessor gearProc;
    Configuration config;
    Controller controller(config, nullptr, nullptr, nullptr, &gearProc, nullptr, TestingConstants::Networking::TEST_PORT);
    boost::thread controllerThread(boost::bind(&Controller::run, &controller));
    std::string request = "SETTINGS_GEAR_PROC#";
    request += "gearProcHLower:" + std::to_string(hLower) + ",";
    request += "gearProcSLower:" + std::to_string(sLower) + ",";
    request += "gearProcVLower:" + std::to_string(vLower) + ",";
    request += "gearProcHUpper:" + std::to_string(hUpper) + ",";
    request += "gearProcSUpper:" + std::to_string(sUpper) + ",";
    request += "gearProcVUpper:" + std::to_string(vUpper) + ",";
    request += "gearMinArea:" + std::to_string(minArea) + ",";
    request += "gearMinPerimeter:" + std::to_string(minPerimeter) + ",";
    request += "gearMinWidth:" + std::to_string(minWidth) + ",";
    request += "gearMaxWidth:" + std::to_string(maxWidth) + ",";
    request += "gearMinHeight:" + std::to_string(minHeight) + ",";
    request += "gearMaxHeight:" + std::to_string(maxHeight) + ",";
    request += "gearMinSolidity:" + std::to_string(minSolidity) + ",";
    request += "gearMaxSolidity:" + std::to_string(maxSolidity) + ",";
    request += "gearMinVertices:" + std::to_string(minVertices) + ",";
    request += "gearMaxVertices:" + std::to_string(maxVertices) + ",";
    request += "gearMinRatio:" + std::to_string(minRatio) + ",";
    request += "gearMaxRatio:" + std::to_string(maxRatio);

    EXPECT_CALL(gearProc, subConfig(::testing::_)); //Ensure that at least something gets subbed in

    s_send(socket, request);
    s_recv(socket);

    Configuration newSettings = controller.getCurrentSettings();
    ASSERT_EQ(newSettings.gearProcHLower, hLower);
    ASSERT_EQ(newSettings.gearProcSLower, sLower);
    ASSERT_EQ(newSettings.gearProcVLower, vLower);
    ASSERT_EQ(newSettings.gearProcHUpper, hUpper);
    ASSERT_EQ(newSettings.gearProcSUpper, sUpper);
    ASSERT_EQ(newSettings.gearProcVUpper, vUpper);
    ASSERT_EQ(newSettings.gearMinArea, minArea);
    ASSERT_EQ(newSettings.gearMinPerimeter, minPerimeter);
    ASSERT_EQ(newSettings.gearMinWidth, minWidth);
    ASSERT_EQ(newSettings.gearMaxWidth, maxWidth);
    ASSERT_EQ(newSettings.gearMinHeight, minHeight);
    ASSERT_EQ(newSettings.gearMaxHeight, maxHeight);
    ASSERT_EQ(newSettings.gearMinSolidity, minSolidity);
    ASSERT_EQ(newSettings.gearMaxSolidity, maxSolidity);
    ASSERT_EQ(newSettings.gearMinVertices, minVertices);
    ASSERT_EQ(newSettings.gearMaxVertices, maxVertices);
    ASSERT_EQ(newSettings.gearMinRatio, minRatio);
    ASSERT_EQ(newSettings.gearMaxRatio, maxRatio);

    socket.close();
    controllerThread.interrupt();
    controllerThread.join();
}

TEST(networking, controller_stream_compression) {
    TestingConstants::setRand();
    int compression = TestingConstants::randInt(101);  //Generates a random int for the compression

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT);
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT));

    MockStreamer streamer;
    Configuration config;
    Controller controller(config, nullptr, nullptr, nullptr, nullptr, &streamer, TestingConstants::Networking::TEST_PORT);
    boost::thread controllerThread(boost::bind(&Controller::run, &controller));
    std::string request = "SETTINGS_STREAM_COMPRESSION#streamCompression:" + std::to_string(compression);

    EXPECT_CALL(streamer, setCompression(compression));

    s_send(socket, request);
    s_recv(socket);

    socket.close();
    controllerThread.interrupt();
    controllerThread.join();
}

TEST(networking, controller_write_config) {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT);
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT));

    Configuration config;
    Controller controller(config, nullptr, nullptr, nullptr, nullptr, nullptr, TestingConstants::Networking::TEST_PORT);
    boost::thread controllerThread(boost::bind(&Controller::run, &controller));
    std::string request = "ACTION_WRITE_CONFIG#";

    s_send(socket, request);
    s_recv(socket);

    ASSERT_TRUE(config == controller.getCurrentSettings()); //Ensure that any settings didn't change after the save
    std::ifstream f("config.txt");
    ASSERT_TRUE(f.good()); //Make sure the file is written
    f.close();

    socket.close();
    controllerThread.interrupt();
    controllerThread.join();
}

TEST(networking, controller_reset_config) {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT);
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT));

    Configuration config;
    MockProcessor goalProc;
    MockProcessor gearProc;
    MockCamera goalCamera;
    MockCamera gearCamera;
    Controller controller(config, &goalCamera, &gearCamera, &goalProc, &gearProc, nullptr, TestingConstants::Networking::TEST_PORT);
    boost::thread controllerThread(boost::bind(&Controller::run, &controller));

    std::string request = "ACTION_RESET_CONFIG#";

    EXPECT_CALL(goalProc, subConfig(::testing::_));
    EXPECT_CALL(gearProc, subConfig(::testing::_));
    EXPECT_CALL(goalCamera, setProperty(::testing::_, ::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(gearCamera, setProperty(::testing::_, ::testing::_)).Times(::testing::AtLeast(1));

    s_send(socket, request);
    s_recv(socket);

    socket.close();
    controllerThread.interrupt();
    controllerThread.join();
}

TEST(networking, controller_invalid_data) {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.setsockopt(ZMQ_RCVTIMEO, TestingConstants::Networking::TIMEOUT);
    socket.connect("tcp://127.0.0.1:" + std::to_string(TestingConstants::Networking::TEST_PORT));

    Configuration config;
    Controller controller(config, nullptr, nullptr, nullptr, nullptr, nullptr, TestingConstants::Networking::TEST_PORT);
    boost::thread controllerThread(boost::bind(&Controller::run, &controller));

    std::string request = "INVALID_DATA";

    s_send(socket, request);
    s_recv(socket);

    socket.close();
    controllerThread.interrupt();
    controllerThread.join();
}