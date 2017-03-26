cmake_minimum_required(VERSION 2.8)


option(GEN_TESTS "Should we build the test suite?" ON)
option(GEN_COVERAGE "Should we build with coverage?" OFF)


set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}") #Use STL 11

#INCLUDE LIBS
include(cmake/FindZMQ.cmake)
include(cmake/FindOpenCV.cmake)
include(cmake/FindBoost.cmake)
include(cmake/FindV4L.cmake)

if(GEN_COVERAGE) #If the coverage flag is true
    message(STATUS "BUILDING WITH COVERAGE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") #Enable coverage
endif()

add_subdirectory(processor)


if(GEN_TESTS) #If the test flag is true
    message(STATUS "BUILDING WITH TESTS")
    enable_testing() #Enable CTest for "make test" target
    add_subdirectory(tests) #Include the tests
endif()

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
