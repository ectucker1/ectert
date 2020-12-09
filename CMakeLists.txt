cmake_minimum_required (VERSION 3.10)
project (ectert)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ftree-slp-vectorize")

include_directories(src)
include_directories(lib/tinyobjloader)
include_directories(lib/stb)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)
