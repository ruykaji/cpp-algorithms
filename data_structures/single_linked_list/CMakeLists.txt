# Set C++ standard for the target
add_executable(single_linked_list test.cpp)
target_compile_features(single_linked_list PRIVATE cxx_std_20)

# Include google test directory
target_include_directories(single_linked_list PRIVATE ${GTEST_INCLUDE_DIRS})

# Link google test, pthread and main project libraries
target_link_libraries(single_linked_list PRIVATE GTest::gtest pthread)

# Add test
if(VALGRIND)
    add_test(NAME single_linked_list COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=minimalraw.log $<TARGET_FILE:single_linked_list>)
else()
    add_test(NAME single_linked_list COMMAND single_linked_list)
endif()