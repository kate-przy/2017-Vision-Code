include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}) #Link the google test headers for easy use

include(../../cmake/GTestFunctions.cmake)

file(GLOB 2017_VISION_MAIN_TESTS_SRC
        "*.cpp"
        ) #Find all source files in this folder

file(COPY res DESTINATION ./) #Copy the resources folder to the build

add_executable(2017-Vision-main-tests ${2017_VISION_MAIN_TESTS_SRC})
target_link_libraries(2017-Vision-main-tests gtest gtest_main 2017-Vision-lib)

GTEST_ADD_TESTS(2017-Vision-main-tests "" ${2017_VISION_MAIN_TESTS_SRC}) #Add each test to the CTest list