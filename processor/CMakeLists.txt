
project(2017-Vision-processor)

file(COPY res DESTINATION ./)

add_subdirectory(src)

set(2017_VISION_PROCESSOR_SRC main.cpp)

add_executable(2017-Vision-processor ${2017_VISION_PROCESSOR_SRC})
target_link_libraries(2017-Vision-processor 2017-Vision-processor-lib ${OpenCV_LIBS} ${Boost_LIBRARIES} ${ZMQ_LIBRARY} ${LIBV4L2_LIBRARY})