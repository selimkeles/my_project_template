cmake_minimum_required(VERSION 3.10)
project(TemplateProject)        # ChangeThis

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug, Release, etc.)" FORCE)
endif()

# Set compiler based on system
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DEBUG /Od")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()
    
# Set C C++ standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(include)
include_directories(lib)
include_directories(lib/TaskScheduler/include)

# Source files
file(GLOB_RECURSE INCLUDE_SOURCES  "include/*.c" "include/*.cpp")
file(GLOB_RECURSE LIB_SOURCES "lib/*.c" "lib/*.cpp")
file(GLOB_RECURSE SRC_SOURCES "src/*.c" "src/*.cpp")

# Main and test executable source files
set(MAIN_SOURCES ${INCLUDE_SOURCES} ${LIB_SOURCES} ${SRC_SOURCES})
set(TEST_SOURCES ${INCLUDE_SOURCES} ${LIB_SOURCES} ${SRC_SOURCES} ${CMAKE_SOURCE_DIR}/tests/test.c)
list(REMOVE_ITEM TEST_SOURCES ${CMAKE_SOURCE_DIR}/src/main.c)   # Exclude src/main.c from TEST_SOURCES

add_executable(${PROJECT_NAME} ${MAIN_SOURCES})
# Test executable
add_executable(${PROJECT_NAME}_test ${TEST_SOURCES})
target_compile_definitions(${PROJECT_NAME}_test PRIVATE TEST)
target_include_directories(${PROJECT_NAME}_test PRIVATE ${CMAKE_SOURCE_DIR}/tests/unity)

# Enable testing
enable_testing()
add_test(NAME runTests COMMAND ${PROJECT_NAME}_test)
