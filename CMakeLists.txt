cmake_minimum_required(VERSION 3.10)
project(TemplateProject)

# Set compiler based on system
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_GENERATOR "MinGW Makefiles")

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/relwithdebinfo)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/minsizerel)

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

# Main executable
add_executable(TemplateProject ${INCLUDE_SOURCES} ${LIB_SOURCES} ${SRC_SOURCES})
target_sources(TemplateProject PRIVATE
    $<$<NOT:$<CONFIG:Test>>:src/main.c>
)
# target_compile_definitions(TemplateProject PRIVATE
#     $<$<CONFIG:Release>:RELEASE1>
#     $<$<CONFIG:Debug>:DEBUG>
# )

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