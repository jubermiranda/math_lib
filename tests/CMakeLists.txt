# Gtest setup
find_package(GTest REQUIRED)
enable_testing()
include(GoogleTest)

file(GLOB_RECURSE TEST_SOURCE
  "utils.cxx"
  "test_utils.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/**/test_*.cxx"
)

file(GLOB IMPL_SOURCE
  "${PROJECT_SOURCE_DIR}/src/*.cxx"
)

add_executable(test_${PROJECT_NAME}
  ${IMPL_SOURCE}
  ${TEST_SOURCE}
)

target_link_libraries(
    test_${PROJECT_NAME}
    GTest::gtest
    GTest::gtest_main
)

target_include_directories(test_${PROJECT_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
