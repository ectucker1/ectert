cmake_minimum_required(VERSION 3.10)
project(ectert)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -ftree-slp-vectorize")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)

aux_source_directory(lib/lua LUA_SOURCES)
add_library(lua STATIC ${LUA_SOURCES})
include_directories(lib/lua)

add_subdirectory(lib/sol2)

include_directories(lib/imgui)

include_directories(lib/tinyobjloader)
include_directories(lib/stb)

include_directories(src)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(lib/googletest)

add_subdirectory(src)
add_subdirectory(test)
