# Basic CMake config
cmake_minimum_required(VERSION 3.11)
project(ectert)

# Set C++ version
set(CMAKE_CXX_STANDARD 20)

# Set manual compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -ftree-slp-vectorize")

# Add libraries and project source
add_subdirectory(lib)
add_subdirectory(src)
