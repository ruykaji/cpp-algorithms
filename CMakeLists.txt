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

# Add subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/data_structures)
