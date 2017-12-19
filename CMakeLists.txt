# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.1)

# Project Name
project(graphy)

set(graphy_VERSION_MAJOR 1)
set(graphy_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 11)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(src)

