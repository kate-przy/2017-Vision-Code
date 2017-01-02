project(2017-Vision-lib)

file(GLOB 2017_VISION_LIB_SRC #Find all source and header files
        "*.hpp"
        "*.cpp"
        "*/*.hpp"
        "*/*.cpp"
        )

add_library(2017-Vision-lib ${2017_VISION_LIB_SRC})