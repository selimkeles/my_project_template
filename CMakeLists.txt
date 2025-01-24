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
file(GLOB_RECURSE INCLUDE_SOURCES "include/*.[ch]pp" "include/*.c")
file(GLOB_RECURSE LIB_SOURCES "lib/*.[ch]pp" "lib/*.c")
file(GLOB_RECURSE SRC_SOURCES "src/*.[ch]pp" "src/*.c")

# Add custom compiler flags for each build type
# -g for Debug, and optimize for Release
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Main executable
add_executable(${PROJECT_NAME} ${INCLUDE_SOURCES} ${LIB_SOURCES} ${SRC_SOURCES})
target_sources(${PROJECT_NAME} PRIVATE
    $<$<NOT:$<CONFIG:Test>>:src/main.c>
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:RELEASE>
    $<$<CONFIG:Debug>:DEBUG>
)

# Enable testing
enable_testing()

# Test executable
add_executable(runTests ${INCLUDE_SOURCES} ${LIB_SOURCES} ${SRC_SOURCES})
target_sources(runTests PRIVATE
    $<$<CONFIG:Test>:tests/test.c>
)
target_compile_definitions(runTests PRIVATE
    $<$<CONFIG:Test>:TEST>
)
add_test(NAME runTests COMMAND runTests)