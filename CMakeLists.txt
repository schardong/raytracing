cmake_minimum_required(VERSION 3.1)

project(raytracer)

set(CMAKE_CXX_STANDARD 17)

set(BINARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(ext)
file(GLOB SRC "src/*.cpp")
add_executable(rt ${SRC})
