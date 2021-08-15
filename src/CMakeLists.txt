# Set binary name
set(BINARY ${CMAKE_PROJECT_NAME})

# Add project sources
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false CONFIGURE_DEPENDS  *.h *.cpp)

# Create library and executable
add_library(${BINARY}_src STATIC ${SOURCES})
add_executable(${BINARY}_run ${SOURCES})

# Add shaders directory
add_subdirectory(shader)
add_dependencies(${BINARY}_src ${BINARY}_shader)
add_dependencies(${BINARY}_run ${BINARY}_shader)

# Include sources as headers
target_include_directories(${BINARY}_src PRIVATE .)
target_include_directories(${BINARY}_run PRIVATE .)

# Link to dependencies
target_link_libraries(${BINARY}_src PRIVATE ${BINARY}_lib)
target_link_libraries(${BINARY}_run PRIVATE ${BINARY}_lib)
