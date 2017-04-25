//
// Created by cameronearle on 4/24/17.
//


//
// Created by cameronearle on 12/25/16.
//

#include "gtest/gtest.h"
#include "../../processor/src/utility/Log.hpp"
#include "../../processor/src/utility/Base64.hpp"
#include "../../processor/src/utility/Configuration.hpp"
#include "TestingConstants.hpp"
#include "../../processor/src/utility/ConfigParser.hpp"

vector<string> splitElements(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string tok;

    while (getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

TEST(utility, log_setdebugmode_test) {
    testing::internal::CaptureStdout();
    Log::setDoDebug(false);
    string result = testing::internal::GetCapturedStdout();
    vector<string> resultsplit = splitElements(result, ' ');
    ASSERT_EQ(resultsplit[1], "[INFO]");
    ASSERT_EQ(resultsplit[2], "[Log]");
    ASSERT_EQ(resultsplit[3], "DEBUG");
    ASSERT_EQ(resultsplit[4], "messages");
    ASSERT_EQ(resultsplit[5], "are");
    ASSERT_EQ(resultsplit[6], "now");
    ASSERT_EQ(resultsplit[7], "disabled\n");
    testing::internal::CaptureStdout();
    Log::setDoDebug(true);
    result = testing::internal::GetCapturedStdout();
    resultsplit = splitElements(result, ' ');
    ASSERT_EQ(resultsplit[1], "[INFO]");
    ASSERT_EQ(resultsplit[2], "[Log]");
    ASSERT_EQ(resultsplit[3], "DEBUG");
    ASSERT_EQ(resultsplit[4], "messages");
    ASSERT_EQ(resultsplit[5], "are");
    ASSERT_EQ(resultsplit[6], "now");
    ASSERT_EQ(resultsplit[7], "enabled\n");
}

TEST(utility, log_debug_nofile_test) {
    Log::init(Log::Level::DEBUG, false);
    testing::internal::CaptureStdout();
    Log::d("ld", "data");
    string raw = testing::internal::GetCapturedStdout();
    vector<string> split = splitElements(raw, ' ');
    ASSERT_EQ(split[1], "[DEBUG]");
    ASSERT_EQ(split[2], "[ld]");
    ASSERT_EQ(split[3], "data\n");
    Log::close();
}

TEST(utility, log_debug_file_test) {
    Log::init(Log::Level::DEBUG, true, "testing.log");
    Log::d("ld", "data");
    Log::close();
    ifstream infile("testing.log");
    string fromfile0;
    string fromfile1;
    string fromfile2;
    string fromfile3;
    infile >> fromfile0 >> fromfile1 >> fromfile2 >> fromfile3;
    infile.close();
    remove("testing.log");
    ASSERT_EQ(fromfile1, "[DEBUG]");
    ASSERT_EQ(fromfile2, "[ld]");
    ASSERT_EQ(fromfile3, "data");
}

TEST(utility, log_info_nofile_test) {
    Log::init(Log::Level::DEBUG, false);
    testing::internal::CaptureStdout();
    Log::i("ld", "data");
    string raw = testing::internal::GetCapturedStdout();
    vector<string> split = splitElements(raw, ' ');
    ASSERT_EQ(split[1], "[INFO]");
    ASSERT_EQ(split[2], "[ld]");
    ASSERT_EQ(split[3], "data\n");
    Log::close();
}

TEST(utility, log_info_file_test) {
    Log::init(Log::Level::DEBUG, true, "testing.log");
    Log::i("ld", "data");
    Log::close();
    ifstream infile("testing.log");
    string fromfile0;
    string fromfile1;
    string fromfile2;
    string fromfile3;
    infile >> fromfile0 >> fromfile1 >> fromfile2 >> fromfile3;
    infile.close();
    remove("testing.log");
    ASSERT_EQ(fromfile1, "[INFO]");
    ASSERT_EQ(fromfile2, "[ld]");
    ASSERT_EQ(fromfile3, "data");
}

TEST(utility, log_warning_nofile_test) {
    Log::init(Log::Level::DEBUG, false);
    testing::internal::CaptureStderr();
    Log::w("ld", "data");
    string raw = testing::internal::GetCapturedStderr();
    vector<string> split = splitElements(raw, ' ');
    ASSERT_EQ(split[1], "[WARNING]");
    ASSERT_EQ(split[2], "[ld]");
    ASSERT_EQ(split[3], "data\n");
    Log::close();
}

TEST(utility, log_warning_file_test) {
    Log::init(Log::Level::DEBUG, true, "testing.log");
    Log::w("ld", "data");
    Log::close();
    ifstream infile("testing.log");
    string fromfile0;
    string fromfile1;
    string fromfile2;
    string fromfile3;
    infile >> fromfile0 >> fromfile1 >> fromfile2 >> fromfile3;
    infile.close();
    remove("testing.log");
    ASSERT_EQ(fromfile1, "[WARNING]");
    ASSERT_EQ(fromfile2, "[ld]");
    ASSERT_EQ(fromfile3, "data");
}

TEST(utility, log_error_nofile_test) {
    Log::init(Log::Level::DEBUG, false);
    testing::internal::CaptureStderr();
    Log::e("ld", "data");
    string raw = testing::internal::GetCapturedStderr();
    vector<string> split = splitElements(raw, ' ');
    ASSERT_EQ(split[1], "[ERROR]");
    ASSERT_EQ(split[2], "[ld]");
    ASSERT_EQ(split[3], "data\n");
    Log::close();
}

TEST(utility, log_error_file_test) {
    Log::init(Log::Level::DEBUG, true, "testing.log");
    Log::e("ld", "data");
    Log::close();
    ifstream infile("testing.log");
    string fromfile0;
    string fromfile1;
    string fromfile2;
    string fromfile3;
    infile >> fromfile0 >> fromfile1 >> fromfile2 >> fromfile3;
    infile.close();
    remove("testing.log");
    ASSERT_EQ(fromfile1, "[ERROR]");
    ASSERT_EQ(fromfile2, "[ld]");
    ASSERT_EQ(fromfile3, "data");
}

TEST(utility, log_exception_nofile_test) {
    Log::init(Log::Level::DEBUG, false);
    testing::internal::CaptureStderr();
    Log::x("ld", "data");
    string raw = testing::internal::GetCapturedStderr();
    vector<string> split = splitElements(raw, ' ');
    ASSERT_EQ(split[1], "[EXCEPTION]");
    ASSERT_EQ(split[2], "[ld]");
    ASSERT_EQ(split[3], "data\n");
    Log::close();
}

TEST(utility, log_exception_file_test) {
    Log::init(Log::Level::DEBUG, true, "testing.log");
    Log::x("ld", "data");
    Log::close();
    ifstream infile("testing.log");
    string fromfile0;
    string fromfile1;
    string fromfile2;
    string fromfile3;
    infile >> fromfile0 >> fromfile1 >> fromfile2 >> fromfile3;
    infile.close();
    remove("testing.log");
    ASSERT_EQ(fromfile1, "[EXCEPTION]");
    ASSERT_EQ(fromfile2, "[ld]");
    ASSERT_EQ(fromfile3, "data");
}

TEST(utility, log_wtfomgy_nofile_test) {
    Log::init(Log::Level::DEBUG, false);
    testing::internal::CaptureStderr();
    Log::wtfomgy("ld", "data");
    string raw = testing::internal::GetCapturedStderr();
    vector<string> split = splitElements(raw, ' ');
    ASSERT_EQ(split[1], "[WHAT");
    ASSERT_EQ(split[2], "THE");
    ASSERT_EQ(split[3], "FRICK,");
    ASSERT_EQ(split[4], "OH");
    ASSERT_EQ(split[5], "MY");
    ASSERT_EQ(split[6], "GOD");
    ASSERT_EQ(split[7], "WHY?]");
    ASSERT_EQ(split[8], "[ld]");
    ASSERT_EQ(split[9], "data\n");
    Log::close();
}

TEST(utility, log_wtfomgy_file_test) {
    Log::init(Log::Level::DEBUG, true, "testing.log");
    Log::wtfomgy("ld", "data");
    Log::close();
    ifstream infile("testing.log");
    string fromfile0;
    string fromfile1;
    string fromfile2;
    string fromfile3;
    string fromfile4;
    string fromfile5;
    string fromfile6;
    string fromfile7;
    string fromfile8;
    string fromfile9;
    infile >> fromfile0 >> fromfile1 >> fromfile2 >> fromfile3 >> fromfile4 >> fromfile5 >> fromfile6 >> fromfile7 >> fromfile8 >> fromfile9;
    infile.close();
    remove("testing.log");
    ASSERT_EQ(fromfile1, "[WHAT");
    ASSERT_EQ(fromfile2, "THE");
    ASSERT_EQ(fromfile3, "FRICK,");
    ASSERT_EQ(fromfile4, "OH");
    ASSERT_EQ(fromfile5, "MY");
    ASSERT_EQ(fromfile6, "GOD");
    ASSERT_EQ(fromfile7, "WHY?]");
    ASSERT_EQ(fromfile8, "[ld]");
    ASSERT_EQ(fromfile9, "data");
}

TEST(utility, base64_encode) {
    std::string toEncode = "team401";
    std::string encoded = Base64::encode(toEncode);
    std::string expectedEncode = "dGVhbTQwMQ==";
    ASSERT_EQ(encoded, expectedEncode);
}

TEST(utility, base64_decode) {
    std::string toDecode = "dGVhbTQwMQ==";
    std::string decoded = Base64::decode(toDecode);
    std::string expectedDecode = "team401";
    ASSERT_EQ(decoded, expectedDecode);
}

TEST(utility, config_operator_nequal) {
    Configuration config1;
    Configuration config2 = config1;
    config1.streamCompression = 0;
    config1.streamCompression = 1; //Set the two configs to have two different values for a key, this also runs the equals test
    ASSERT_TRUE(config1 != config2);
}

TEST(utility, config_parser_defaults) {
    std::vector<std::string> args;
    ConfigParser parser(args, "config_parser_defaults.cfg");
    ifstream f("config_parser_defaults.cfg");
    ASSERT_TRUE(f.good());
    remove("config_parser_defaults.cfg");
}

TEST(utility, config_parser_read) {
    std::vector<std::string> args;
    ConfigParser parser(args, "res/config_parser_read.cfg");
    Configuration config = parser.getSettings();
    ASSERT_EQ(config.streamCompression, 50);
}

TEST(utility, config_parser_clargs) {
    std::vector<std::string> args;
    args.push_back("streamCompression=60");
    ConfigParser parser(args, "res/config_parser_read.cfg");
    Configuration config = parser.getSettings();
    ASSERT_EQ(config.streamCompression, 60);
}