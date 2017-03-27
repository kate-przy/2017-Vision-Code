//
// Created by cameronearle on 3/26/17.
//

#include <gtest/gtest.h>
#include <zhelpers.hpp>
#include <boost/thread/thread.hpp>
#include "TestingConstants.hpp"
#include "../../processor/src/networking/DataStreamer.hpp"
#include "../../processor/src/networking/Streamer.hpp"


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
    socket.setsockopt(ZMQ_RCVTIMEO, 1000); //Wait up to 1 second
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
    socket.setsockopt(ZMQ_RCVTIMEO, 1000); //Wait up to 1 second
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
    socket.setsockopt(ZMQ_RCVTIMEO, 1000); //Wait up to 1 second
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
    socket.setsockopt(ZMQ_RCVTIMEO, 1000); //Wait up to 1 second
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
    socket.setsockopt(ZMQ_RCVTIMEO, 1000); //Wait up to 1 second
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
    socket.setsockopt(ZMQ_RCVTIMEO, 1000); //Wait up to 1 second
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
    socket.setsockopt(ZMQ_RCVTIMEO, 10000); //Wait up to 10 seconds
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