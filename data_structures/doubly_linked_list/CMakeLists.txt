# Set C++ standard for the target
add_executable(doubly_linked_list test.cpp)
target_compile_features(doubly_linked_list PRIVATE cxx_std_17)

# Include google test directory
target_include_directories(doubly_linked_list PRIVATE ${GTEST_INCLUDE_DIRS})

# Link google test, pthread and main project libraries
target_link_libraries(doubly_linked_list PRIVATE GTest::gtest pthread)

# Add test
add_test(NAME doubly_linked_list COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=minimalraw.log $<TARGET_FILE:doubly_linked_list>)