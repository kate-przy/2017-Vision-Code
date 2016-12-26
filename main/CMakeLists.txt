project(2017-Vision-main)

add_subdirectory(src)

set(2017_VISION_MAIN_SRC main.cpp)

add_executable(2017-Vision-main ${2017_VISION_MAIN_SRC})
target_link_libraries(2017-Vision-main 2017-Vision-lib)