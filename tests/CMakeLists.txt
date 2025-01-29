# Enable testing for this directory
enable_testing()

# Add Unity library
add_library(unity STATIC
    Unity/unity.c
)
target_include_directories(unity PUBLIC unity)

# Function to create test targets
function(add_unit_test test_name test_file)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE unity ${PROJECT_NAME}_lib)
    target_include_directories(${test_name} PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

# Add test files
add_unit_test(test_main test.c) 