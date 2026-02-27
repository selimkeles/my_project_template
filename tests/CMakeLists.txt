enable_testing()

add_library(unity STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/unity/unity.c
)
target_include_directories(unity PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/unity
)

# Non-main sources from src/ so test targets can call project functions
file(GLOB_RECURSE PROJECT_SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
list(REMOVE_ITEM PROJECT_SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/main.c"
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
)

# Usage: add_unit_test(name src1 [src2 ...])
function(add_unit_test test_name)
    add_executable(${test_name} ${ARGN} ${PROJECT_SRC_FILES})
    target_link_libraries(${test_name} PRIVATE unity)
    target_include_directories(${test_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
    )
    
    # Set C++11 for test executables
    set_target_properties(${test_name} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
    )
    
    add_test(
        NAME ${test_name}
        COMMAND ${test_name}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    
    # Set test properties
    set_tests_properties(${test_name} PROPERTIES
        TIMEOUT 30  # Timeout in seconds
        WILL_FAIL FALSE
    )
endfunction()

add_unit_test(test_main
    ${CMAKE_CURRENT_SOURCE_DIR}/test.c
)
