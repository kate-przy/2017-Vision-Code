#include "gtest/gtest.h"
#include "../../processor/src/abstraction/Camera.hpp"
#include "../../processor/src/utility/ConfigParser.hpp"
#include <fstream>

/* Test: camera_setup_test_simple
 * Description: Attempts to set up a camera from an index, located in "res/cameraNum"
 * Assertion: "testResult = camera.setup()": DOES NOT EXIT
 * Assertion: "testResult": TRUE
 */
TEST(hardware_camera_tests, camera_setup_test_simple) {
    std::ifstream file("res/cameraNum"); //Open the cameraNum file to get the index for testing
    std::string readData; //String to hold the data read from the file
    file >> readData; //Read the number in string form from the file
    int cameraNum = std::stoi(readData); //Convert the string to an integer (note, failure is possible here, make sure the file is correct)
    bool testResult = false;
    Camera camera(cameraNum); //Create the camera object
    ASSERT_NO_FATAL_FAILURE(testResult = camera.setup()); //Assert that setup succeeds
    ASSERT_TRUE(testResult);
    camera.close();
}

/* Test: camera_stream_setup_test_fromconfig
 * Description: Attempts to set up the STREAM camera from the config, located in "res/cameraConfig.txt"
 * Assertion: "testResult = camera.setup()": DOES NOT EXIT
 * Assertion: "testResult": TRUE
 */
TEST(hardware_camera_tests, camera_stream_setup_test_fromconfig) {
    Configuration cameraConfig = ConfigParser(vector<string>(), "res/cameraConfig.txt").getSettings();
    Camera camera(cameraConfig, Camera::CameraType::STREAM);
    bool testResult = false;
    EXPECT_NO_FATAL_FAILURE(testResult = camera.setup());
    EXPECT_TRUE(testResult);
    camera.close();
}

/* Test: camera_proc_setup_test_fromconfig
 * Description: Attempts to set up the PROCESSING camera from the config, located in "res/cameraConfig.txt"
 * Assertion: "testResult = camera.setup()": DOES NOT EXIT
 * Assertion: "testResult": TRUE
 */
TEST(hardware_camera_tests, camera_goal_proc_setup_test_fromconfig) {
    Configuration cameraConfig = ConfigParser(vector<string>(), "res/cameraConfig.txt").getSettings(); //Parse the config in "res/cameraConfig.txt" to test complex setup
    Camera camera(cameraConfig, Camera::CameraType::GOAL_PROCESSING);
    bool testResult = false;
    ASSERT_NO_FATAL_FAILURE(testResult = camera.setup());
    ASSERT_TRUE(testResult);
    camera.close();
}

/* Test: camera_proc2_setup_test_fromconfig
 * Description: Attempts to set up the PROCESSING2 camera from the config, located in "res/cameraConfig.txt"
 * Assertion: "testResult = camera.setup()": DOES NOT EXIT
 * Assertion: "testResult": TRUE
 */
TEST(hardware_camera_tests, camera_gear_proc_setup_test_fromconfig) {
    Configuration cameraConfig = ConfigParser(vector<string>(), "res/cameraConfig.txt").getSettings();
    Camera camera(cameraConfig, Camera::CameraType::GEAR_PROCESSING);
    bool testResult = false;
    ASSERT_NO_FATAL_FAILURE(testResult = camera.setup());
    ASSERT_TRUE(testResult);
    camera.close();
}