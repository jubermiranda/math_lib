find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(run_tests
  # test sources
  matrix/test_matrix_basics.cxx
  matrix/test_matrix_classification.cxx
  matrix/test_matrix_determinant.cxx
  point/test_point.cxx
  rational/test_double_to_rational.cxx
  rational/test_rational_constructors.cxx
  rational/test_rational_operations.cxx
  vector/test_vector_basics.cxx
  vector/test_vector_dimentions.cxx
  vector/test_vector_properties.cxx

  # utility files for testes
  utils.h
  utils.cxx
  test_utils.cxx
)

target_link_libraries(run_tests
  PRIVATE
    GTest::gtest_main
    math_lib
)

gtest_discover_tests(run_tests)
