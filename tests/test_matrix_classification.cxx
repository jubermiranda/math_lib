#include <gtest/gtest.h>

#include "matrix_lib.h"
#include "utils.h"

using std::vector;
using std::string;


TEST(MatrixClassification, Identity) {
  Matrix test_mtr = Matrix(4,4);
  string result_class;

  test_mtr.set_elements(vector<float>{
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1
  });
  result_class = test_mtr.print_class().str();

  EXPECT_TRUE(t_utils::is_sub_str(result_class, "identity"));
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "square"));
  EXPECT_TRUE(test_mtr.is_square());
  EXPECT_TRUE(test_mtr.is_identity());



  test_mtr = Matrix(2,2);
  test_mtr.set_elements(vector<float>{
    1,0,
    0,1
  });
  result_class = test_mtr.print_class().str();

  EXPECT_TRUE(t_utils::is_sub_str(result_class, "identity"));
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "square"));
  EXPECT_TRUE(test_mtr.is_square());
  EXPECT_TRUE(test_mtr.is_identity());
}


TEST(MatrixClassification, Null) {
  Matrix test_mtr = Matrix(4,2);

  test_mtr.set_elements(vector<float>{
    0,0,
    0,0,
    0,0,
    0,0
  });
  string result_class = test_mtr.print_class().str();

  EXPECT_TRUE(t_utils::is_sub_str(result_class, "null"));
  EXPECT_TRUE(test_mtr.is_null());

  test_mtr = Matrix(2,4);
  test_mtr.set_elements(vector<float>{
    0,0,0,0,
    0,0,0,0
  });
  result_class = test_mtr.print_class().str();

  EXPECT_TRUE(t_utils::is_sub_str(result_class, "null"));
  EXPECT_TRUE(test_mtr.is_null());
}

TEST(MatrixClassification, Column) {
  Matrix test_mtr = Matrix(4,2);
  string result_class;

  test_mtr.set_elements(vector<float>{
      1,1,
      1,1,
      1,1,
      1,1
      });
   result_class = test_mtr.print_class().str();
   EXPECT_FALSE(t_utils::is_sub_str(result_class, "column"));
   EXPECT_FALSE(test_mtr.is_column());


   test_mtr = Matrix(3,1);
   test_mtr.set_elements(vector<float>{
       0,
       0,
       0
       });
   result_class = test_mtr.print_class().str();
   EXPECT_TRUE(t_utils::is_sub_str(result_class, "column"));
   EXPECT_TRUE(test_mtr.is_column());
}

TEST(MatrixClassification, Line) {
  Matrix test_mtr = Matrix(4,2);
  string result_class;

  test_mtr.set_elements(vector<float>{
      1,1,
      1,1,
      1,1,
      1,1
      });
   result_class = test_mtr.print_class().str();
   EXPECT_FALSE(t_utils::is_sub_str(result_class, "line"));
   EXPECT_FALSE(test_mtr.is_line());


   test_mtr = Matrix(1,3);
   test_mtr.set_elements(vector<float>{
       0,0,0
       });
   result_class = test_mtr.print_class().str();
   EXPECT_TRUE(t_utils::is_sub_str(result_class, "line"));
   EXPECT_TRUE(test_mtr.is_line());
}

TEST(MatrixClassification, Diagonal) {
  Matrix test_mtr = Matrix(4,2);
  string result_class;

  test_mtr.set_elements(vector<float>{
      1,1,
      1,1,
      1,1,
      1,1
    });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "diagonal"));
  EXPECT_FALSE(test_mtr.is_diagonal());

  test_mtr = Matrix(4,4);
  test_mtr.set_elements(vector<float>{
     1,1,1,1,
     1,1,1,1,
     1,1,1,1,
     1,1,1,1
     });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "diagonal"));
  EXPECT_FALSE(test_mtr.is_diagonal());



  test_mtr = Matrix(4,4);
  test_mtr.set_elements(vector<float>{
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "diagonal"));
  EXPECT_TRUE(test_mtr.is_diagonal());

  test_mtr = Matrix(5,5);
  test_mtr.set_elements(vector<float>{
      1,0,0,0,0,
      0,2,0,0,0,
      0,0,3,0,0,
      0,0,0,4,0,
      0,0,0,0,5
    });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "diagonal"));
  EXPECT_TRUE(test_mtr.is_diagonal());

}

TEST(MatrixClassification, UpperTriangular) {
  Matrix test_mtr(4,4);
  string result_class;

  test_mtr.set_elements(vector<float>{
       1,1,1,1,
       0,2,2,2,
       0,0,3,3,
       0,0,0,4
    });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "upper triangular"));
  EXPECT_TRUE(test_mtr.is_upper_tri());

  test_mtr.set_elements(vector<float>{
       1,1,1,1,
       2,2,2,2,
       3,3,3,3,
       4,4,0,4
    });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "upper triangular"));
  EXPECT_FALSE(test_mtr.is_upper_tri());
}

TEST(MatrixClassification, LowerTriangular) {
  Matrix test_mtr(4,4);
  string result_class;

  test_mtr.set_elements(vector<float>{
       1,0,0,0,
       2,2,0,0,
       3,3,3,0,
       4,4,4,4
    });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "lower triangular"));
  EXPECT_TRUE(test_mtr.is_lower_tri());

  test_mtr.set_elements(vector<float>{
       1,1,1,1,
       2,2,2,2,
       3,3,3,3,
       4,4,0,4
    });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "lower triangular"));
  EXPECT_FALSE(test_mtr.is_lower_tri());
}

TEST(MatrixClassification, Symmetric) {
  Matrix test_mtr(1,1);
  string result_class;

  test_mtr.set_elements(vector<float>{
      4
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "symmetric"));
  EXPECT_TRUE(test_mtr.is_symmetric());


  test_mtr = Matrix(2,2);
  test_mtr.set_elements(vector<float>{
      4,2,
      2,4
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(test_mtr.is_symmetric());
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "symmetric"));

  test_mtr.set_elements(vector<float>{
      4,4,
      2,2
      });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(test_mtr.is_symmetric());
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "symmetric"));

  test_mtr = Matrix(3,3);
  test_mtr.set_elements(vector<float>{
      4,2,1,
      2,3,5,
      1,5,7
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(test_mtr.is_symmetric());
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "symmetric"));

  test_mtr.set_elements(vector<float>{
      4,1,1,
      2,4,1,
      2,2,4
      });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(test_mtr.is_symmetric());
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "symmetric"));

}

TEST(MatrixClassification, AntiSymmetric) {
  Matrix test_mtr(4,4);
  string result_class;

  test_mtr.set_elements(vector<float>{
      1,2,3,4,
      1,2,3,4,
      1,2,3,4,
      1,2,3,4
      });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(test_mtr.is_antisymmetric());
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "antisymmetric"));

  test_mtr.set_elements(vector<float>{
      0,2,3,4,
      1,0,3,4,
      1,2,0,4,
      1,2,3,0
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(test_mtr.is_antisymmetric());
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "antisymmetric"));
}


TEST(MatrixClassification, Scalar) {
  Matrix test_mtr(4,4);
  string result_class;

  test_mtr.set_elements(vector<float>{
      1,2,3,4,
      1,2,3,4,
      1,2,3,4,
      1,2,3,4
      });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(test_mtr.is_scalar());
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "scalar"));

  test_mtr.set_elements(vector<float>{
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(test_mtr.is_scalar());
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "scalar"));

  test_mtr = Matrix(3,3);
  test_mtr.set_elements(vector<float>{
      3,0,0,
      0,3,0,
      0,0,3
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(test_mtr.is_scalar());
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "scalar"));
}

TEST(MatrixClassification, Square) {
  Matrix test_mtr = Matrix(4,4);
  test_mtr.set_elements(vector<float>{
      2,2,2,2,
      2,2,2,2,
      2,2,2,2,
      2,2,2,2
  });
  string result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "square"));
  EXPECT_TRUE(test_mtr.is_square());


  test_mtr = Matrix(2,2);
  test_mtr.set_elements(vector<float>{
      4,4,
      4,4
  });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "square"));
  EXPECT_TRUE(test_mtr.is_square());



  test_mtr = Matrix(4,2);
  test_mtr.set_elements(vector<float>{
      4,2,
      4,2,
      4,2,
      4,2
  });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "square"));
  EXPECT_FALSE(test_mtr.is_square());
}

