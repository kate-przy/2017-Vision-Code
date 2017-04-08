include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}) #Link the google test headers for easy use
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR}) #Link the google mock headers for easy use

include(../../cmake/GTestFunctions.cmake)

file(GLOB 2017_VISION_PROCESSOR_TESTS_SRC
        "*.cpp"
        "*.hpp"
        ) #Find all source files in this folder

#file(COPY res DESTINATION ./) #Copy the resources folder to the build

add_executable(2017-Vision-processor-tests ${2017_VISION_PROCESSOR_TESTS_SRC})
target_link_libraries(2017-Vision-processor-tests gtest gtest_main gmock gmock_main 2017-Vision-processor-lib ${OpenCV_LIBS} ${Boost_LIBRARIES} ${ZMQ_LIBRARY} ${LIBV4L2_LIBRARY})

GTEST_ADD_TESTS(2017-Vision-processor-tests "" ${2017_VISION_PROCESSOR_TESTS_SRC}) #Add each test to the CTest list