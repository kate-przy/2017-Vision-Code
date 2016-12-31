//
// Created by cameronearle on 12/26/16.
//

#include "gtest/gtest.h"
#include "../../main/src/SayHello.hpp"

TEST(say_hello_tests, say_hello_test) {
    ASSERT_NO_FATAL_FAILURE(SayHello::sayHello());
}