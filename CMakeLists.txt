cmake_minimum_required(VERSION 3.19.0)
project(c_cpp_algorithms_and_data_structures LANGUAGES C CXX)

# Find google-test package
find_package(GTest CONFIG REQUIRED)
if(NOT GTest_FOUND)
    message(FATAL_ERROR "Google Test not found!")
endif()

# Find valgrind as program
find_program(VALGRIND "valgrind")
if(VALGRIND)
    # Remove optimization and set in debug mode for poroper memory leak managment
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")

    message(STATUS "Valgrind found: ${VALGRIND}")
else()
    message(STATUS "Valgrind not found")
endif()

# Enable testing
enable_testing()


macro(init_test)
    # Set C++ standard for the target
    add_executable(${ARGV0} test.cpp)
    target_compile_features(${ARGV0} PRIVATE cxx_std_20)

    # Include google test directory
    target_include_directories(${ARGV0} PRIVATE ${GTEST_INCLUDE_DIRS})

    # Link google test, pthread and main project libraries
    target_link_libraries(${ARGV0} PRIVATE GTest::gtest pthread)

    # Add test
    if(VALGRIND)
        add_test(NAME ${ARGV0} COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=minimalraw.log $<TARGET_FILE:${ARGV0}>)
    else()
        add_test(NAME ${ARGV0} COMMAND ${ARGV0})
    endif()
endmacro()

# Add subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/data_structures)
add_subdirectory(${CMAKE_SOURCE_DIR}/algorithms)