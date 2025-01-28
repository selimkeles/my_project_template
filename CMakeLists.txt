cmake_minimum_required(VERSION 3.10)
project(TemplateProject)        # ChangeThis

# Set compiler based on system
if(WIN32)
    set(CMAKE_C_COMPILER cl)
    set(CMAKE_CXX_COMPILER cl)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DEBUG /Od")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    # Set C C++ standard
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_CXX_STANDARD 17)
elseif(UNIX)
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)
    # Add custom compiler flags for each build type
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    # Set C C++ standard
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_CXX_STANDARD 17)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories
include_directories(include)
include_directories(lib)
include_directories(lib/TaskScheduler/include)
include_directories(lib/logger/include)
include_directories(lib/logger/storage/include)

# Source files
file(GLOB_RECURSE INCLUDE_SOURCES "include/*.cpp" "include/*.c")
file(GLOB_RECURSE LIB_SOURCES "lib/*.cpp" "lib/*.c")
file(GLOB_RECURSE SRC_SOURCES "src/*.cpp" "src/*.c")

# Main executable source files
set(MAIN_SOURCES ${INCLUDE_SOURCES} ${LIB_SOURCES} ${SRC_SOURCES})
set(TEST_SOURCES ${INCLUDE_SOURCES} ${LIB_SOURCES} ${SRC_SOURCES} ${CMAKE_SOURCE_DIR}/tests/test.c)
# Exclude src/main.c from TEST_SOURCES
list(REMOVE_ITEM TEST_SOURCES ${CMAKE_SOURCE_DIR}/src/main.c)

# Define custom configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Test" CACHE STRING "" FORCE)
# Define custom configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Test" CACHE STRING "" FORCE)

# Set linker flags for custom configurations
set(CMAKE_EXE_LINKER_FLAGS_TEST "" CACHE STRING "Linker flags for Test configuration" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_TEST "" CACHE STRING "Shared linker flags for Test configuration" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_TEST "" CACHE STRING "Module linker flags for Test configuration" FORCE)

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
