cmake_minimum_required (VERSION 3.10)
project (ectert)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(lib/tinyobjloader)
include_directories(lib/stb)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)
