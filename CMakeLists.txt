cmake_minimum_required(VERSION 2.8)

option(GEN_TESTS "Should we build the test suite?" ON)
option(GEN_COVERAGE "Should we build with coverage?" ON)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH cmake_modules)

if(GEN_COVERAGE)
    message(STATUS "BUILDING WITH COVERAGE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

add_subdirectory(main)


if(GEN_TESTS)
    message(STATUS "BUILDING WITH TESTS")
    add_subdirectory(tests)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")