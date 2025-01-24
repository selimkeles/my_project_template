cmake_minimum_required(VERSION 3.10)
project(TemplateProject)        # ChangeThis

# Set compiler based on system
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_GENERATOR "MinGW Makefiles")

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)
include_directories(lib)
include_directories(src)

# Source files
file(GLOB_RECURSE INCLUDE_SOURCES "include/*.[ch]pp" "include/*.c" "include/*.h")
file(GLOB_RECURSE LIB_SOURCES "lib/*.[ch]pp" "lib/*.c" "lib/*.h")
file(GLOB_RECURSE SRC_SOURCES "src/*.[ch]pp" "src/*.c"  "src/*.h")

# Main executable source files
set(MAIN_SOURCES ${INCLUDE_SOURCES} ${LIB_SOURCES} ${SRC_SOURCES})
set(TEST_SOURCES ${INCLUDE_SOURCES} ${LIB_SOURCES} ${SRC_SOURCES} ${CMAKE_SOURCE_DIR}/tests/test.c)

# Exclude src/main.c from TEST_SOURCES
list(REMOVE_ITEM TEST_SOURCES ${CMAKE_SOURCE_DIR}/src/main.c)

# Add custom compiler flags for each build type
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Define custom configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Test" CACHE STRING "" FORCE)

# Conditionally add sources based on the build configuration
if(CMAKE_BUILD_TYPE STREQUAL "Test")
    add_executable(${PROJECT_NAME}_test ${TEST_SOURCES})
    target_compile_definitions(${PROJECT_NAME}_test PRIVATE TEST)
    add_test(NAME runTests COMMAND ${PROJECT_NAME}_test)
else()
    add_executable(${PROJECT_NAME} ${MAIN_SOURCES})
    target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:RELEASE>
                                                   $<$<CONFIG:Debug>:DEBUG>)
endif()

# Enable testing
enable_testing()
