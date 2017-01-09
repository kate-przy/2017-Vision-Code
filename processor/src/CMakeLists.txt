project(2017-Vision-processor-lib)

file(GLOB 2017_VISION_PROCESSOR_LIB_SRC #Find all source and header files
        "*.hpp"
        "*.cpp"
        "*/*.hpp"
        "*/*.cpp"
        )

add_library(2017-Vision-processor-lib ${2017_VISION_PROCESSOR_LIB_SRC})