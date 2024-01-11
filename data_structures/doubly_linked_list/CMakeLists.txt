# Set C++ standard for the target
# ==========================================================================
add_executable(doubly_linked_list test.cpp)
target_compile_features(doubly_linked_list PRIVATE cxx_std_17)

find_package(GTest CONFIG REQUIRED)
if(NOT GTest_FOUND)
    message(FATAL_ERROR "Google Test not found!")
endif()

# Include google test directory
# ==========================================================================
target_include_directories(doubly_linked_list PRIVATE ${GTEST_INCLUDE_DIRS})

# Link google test, pthread and main project libraries
# ==========================================================================
target_link_libraries(doubly_linked_list PRIVATE GTest::gtest pthread)

# Add test
# ==========================================================================
add_test(NAME doubly_linked_list COMMAND doubly_linked_list)