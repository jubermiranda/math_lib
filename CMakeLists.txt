cmake_minimum_required(VERSION 3.14)
project(matrix_lib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_PROJECT "Build the main project" OFF)
option(BUILD_TESTS "Build project tests (with gtest)" ON)

enable_testing()

include_directories(include)

if(BUILD_PROJECT)
    add_executable(
        matrix_lib
        src/matrix_lib.cxx
    )
endif(BUILD_PROJECT)


if(BUILD_TESTS)
    add_subdirectory(tests)
    add_test(NAME test_matrix_lib COMMAND test_matrix_lib)
endif(BUILD_TESTS)
