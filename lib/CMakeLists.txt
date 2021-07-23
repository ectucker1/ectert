# Set binary name
set(BINARY ${CMAKE_PROJECT_NAME})
set(SOURCES ${SOURCES})

# Gather ImGui sources to compile
aux_source_directory(imgui SOURCES)
aux_source_directory(imgui/misc/cpp SOURCES)
set(SOURCES ${SOURCES} ../lib/imgui/backends/imgui_impl_glfw.cpp ../lib/imgui/backends/imgui_impl_opengl2.cpp)

# Create library of libraries
add_library(${BINARY}_lib STATIC ${SOURCES})

# Add header library includes
target_include_directories(${BINARY}_lib PUBLIC imgui)
target_include_directories(${BINARY}_lib PUBLIC imgui/misc/cpp)
target_include_directories(${BINARY}_lib PUBLIC stb)

# Add GLFW library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)
target_link_libraries(${BINARY}_lib PUBLIC glfw)

# Add GLM library
add_subdirectory(glm)
target_link_libraries(${BINARY}_lib PUBLIC glm)
target_include_directories(${BINARY}_lib PUBLIC glm/glm)

# Add Threads library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${BINARY}_lib PUBLIC Threads::Threads)

# Add OpenGL library
find_package(OpenGL REQUIRED)
target_include_directories(${BINARY}_lib PUBLIC ${OPENGL_INCLUDE_DIRS})
target_link_libraries(${BINARY}_lib PUBLIC ${OPENGL_LIBRARIES})
