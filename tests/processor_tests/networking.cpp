//
// Created by cameronearle on 3/26/17.
//

#include <gtest/gtest.h>
#include <zhelpers.hpp>
#include <boost/thread/thread.hpp>
#include "TestingConstants.hpp"
#include "../../processor/src/networking/DataStreamer.hpp"


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