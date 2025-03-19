# Gtest setup
find_package(GTest REQUIRED)
enable_testing()
include(GoogleTest)

file(GLOB TEST_SOURCE 
    "utils.cxx"
    "test_utils.cxx"

    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/*.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/vector/*.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/rational/*.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/point/*.cxx"
)
file(GLOB IMPL_SOURCE "../src/*.cxx")

add_executable(test_matrix_lib ${IMPL_SOURCE} ${TEST_SOURCE})

target_link_libraries(
    test_matrix_lib
    GTest::gtest
    GTest::gtest_main
)

