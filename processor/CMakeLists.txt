project(2017-Vision-processor)

add_subdirectory(src)

include(../cmake/FindZMQ.cmake)
include(../cmake/FindOpenCV.cmake)
include(../cmake/FindBoost.cmake)
include(../cmake/FindV4L.cmake)

file(COPY res DESTINATION ./) #Copy the resources to the build folder

set(2017_VISION_PROCESSOR_SRC main.cpp)

add_executable(2017-Vision-processor ${2017_VISION_PROCESSOR_SRC})
target_link_libraries(2017-Vision-processor 2017-Vision-processor-lib ${OpenCV_LIBS} ${Boost_LIBRARIES} ${ZMQ_LIBRARY} ${LIBV4L2_LIBRARY})