# Gtest setup
find_package(GTest REQUIRED)
enable_testing()
include(GoogleTest)

file(GLOB TEST_SOURCE "test_*.cxx")
file(GLOB IMPL_SOURCE "../src/*/*.cxx")

add_executable(test_matrix_lib ${IMPL_SOURCE} ${TEST_SOURCE})

target_link_libraries(
    test_matrix_lib
    GTest::gtest
    GTest::gtest_main
)

