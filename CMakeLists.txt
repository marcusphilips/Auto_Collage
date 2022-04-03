CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(AUTO_COLLAGE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -std=c++17")

set(SOURCE_FILES bitmap.cpp main.cpp)

add_executable(auto_collage ${SOURCE_FILES})
add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )
find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})
target_link_libraries(auto_collage ${ImageMagick_LIBRARIES})