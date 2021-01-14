set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

# Probably the wrong way to do this, but it works
aux_source_directory(../lib/imgui SOURCES)
set(SOURCES ${SOURCES} ../lib/imgui/backends/imgui_impl_glfw.cpp ../lib/imgui/backends/imgui_impl_opengl2.cpp)

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(ectert_lib PRIVATE ${OPENGL_LIBRARIES} Threads::Threads glfw sol2 lua)
target_link_libraries(ectert_run PRIVATE ${OPENGL_LIBRARIES} Threads::Threads glfw sol2 lua)
