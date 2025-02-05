# Enable testing for this directory
enable_testing()

# Add Unity library
add_library(unity STATIC
    Unity/src/unity.c
)

target_include_directories(unity 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/Unity/src
)

# Function to create test targets
function(add_unit_test test_name test_file)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} 
        PRIVATE 
            unity 
            ${PROJECT_NAME}_lib
    )
    target_include_directories(${test_name} 
        PRIVATE 
            ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/Unity/src
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

# Add test executables
add_unit_test(test_main test.c)

# Create test labels
set_tests_properties(test_main PROPERTIES LABELS "unit;main") 