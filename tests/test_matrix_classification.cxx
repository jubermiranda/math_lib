#include <gtest/gtest.h>

#include "matrix_lib.h"
#include "utils.h"

using std::vector;
using std::string;


TEST(MatrixClassification, Identity) {
  Matrix<int> test_mtr;
  string result_class;

  test_mtr = Matrix<int>(4,4);
  test_mtr.set_elements(vector<int>{
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1
  });
  EXPECT_TRUE(Matrix<int>::is_square(test_mtr));
  EXPECT_TRUE(Matrix<int>::is_identity(test_mtr));


  test_mtr = Matrix<int>(2,2);
  test_mtr.set_elements(vector<int>{
    1,0,
    0,1
  });
  EXPECT_TRUE(Matrix<int>::is_identity(test_mtr));
  EXPECT_TRUE(Matrix<int>::is_square(test_mtr));
}


TEST(MatrixClassification, Null) {
  Matrix<int> test_mtr = Matrix<int>(4,2);

  test_mtr.set_elements(vector<int>{
    0,0,
    0,0,
    0,0,
    0,0
  });
  EXPECT_TRUE(Matrix<int>::is_null(test_mtr));

  test_mtr = Matrix<int>(2,4);
  test_mtr.set_elements(vector<int>{
    0,0,0,0,
    0,0,0,0
  });
  EXPECT_TRUE(Matrix<int>::is_null(test_mtr));
}

TEST(MatrixClassification, Column) {
  Matrix<int> test_mtr = Matrix<int>(4,2);
  string result_class;

  test_mtr.set_elements(vector<int>{
      1,1,
      1,1,
      1,1,
      1,1
      });
   EXPECT_FALSE(Matrix<int>::is_column(test_mtr));


   test_mtr = Matrix<int>(3,1);
   test_mtr.set_elements(vector<int>{
       0,
       0,
       0
       });
   EXPECT_TRUE(Matrix<int>::is_column(test_mtr));
}

TEST(MatrixClassification, Line) {
  Matrix<int> test_mtr = Matrix<int>(4,2);
  string result_class;

  test_mtr.set_elements(vector<int>{
      1,1,
      1,1,
      1,1,
      1,1
      });
   EXPECT_FALSE(Matrix<int>::is_row(test_mtr));

   test_mtr = Matrix<int>(1,3);
   test_mtr.set_elements(vector<int>{
       0,0,0
       });
   EXPECT_TRUE(Matrix<int>::is_row(test_mtr));
}

TEST(MatrixClassification, Diagonal) {
  Matrix<int> test_mtr = Matrix<int>(4,2);
  string result_class;

  test_mtr.set_elements(vector<int>{
      1,1,
      1,1,
      1,1,
      1,1
    });
  EXPECT_FALSE(Matrix<int>::is_diagonal(test_mtr));

  test_mtr = Matrix<int>(4,4);
  test_mtr.set_elements(vector<int>{
     1,1,1,1,
     1,1,1,1,
     1,1,1,1,
     1,1,1,1
     });
  EXPECT_FALSE(Matrix<int>::is_diagonal(test_mtr));


  test_mtr = Matrix<int>(4,4);
  test_mtr.set_elements(vector<int>{
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1
      });
  EXPECT_TRUE(Matrix<int>::is_diagonal(test_mtr));

  test_mtr = Matrix<int>(5,5);
  test_mtr.set_elements(vector<int>{
      1,0,0,0,0,
      0,2,0,0,0,
      0,0,3,0,0,
      0,0,0,4,0,
      0,0,0,0,5
    });
  EXPECT_TRUE(Matrix<int>::is_diagonal(test_mtr));

}

TEST(MatrixClassification, UpperTriangular) {
  Matrix<int> test_mtr(4,4);
  string result_class;

  test_mtr.set_elements(vector<int>{
       1,1,1,1,
       0,2,2,2,
       0,0,3,3,
       0,0,0,4
    });
  EXPECT_TRUE(Matrix<int>::is_upper_tri(test_mtr));

  test_mtr.set_elements(vector<int>{
       1,1,1,1,
       2,2,2,2,
       3,3,3,3,
       4,4,0,4
    });
  EXPECT_FALSE(Matrix<int>::is_upper_tri(test_mtr));
}

TEST(MatrixClassification, LowerTriangular) {
  Matrix<int> test_mtr(4,4);
  string result_class;

  test_mtr.set_elements(vector<int>{
       1,0,0,0,
       2,2,0,0,
       3,3,3,0,
       4,4,4,4
    });
  EXPECT_TRUE(Matrix<int>::is_lower_tri(test_mtr));

  test_mtr.set_elements(vector<int>{
       1,1,1,1,
       2,2,2,2,
       3,3,3,3,
       4,4,0,4
    });
  EXPECT_FALSE(Matrix<int>::is_lower_tri(test_mtr));
}

TEST(MatrixClassification, Symmetric) {
  Matrix<int> test_mtr(1,1);
  string result_class;

  test_mtr.set_elements(vector<int>{
      4
      });
  EXPECT_TRUE(Matrix<int>::is_symmetric(test_mtr));


  test_mtr = Matrix<int>(2,2);
  test_mtr.set_elements(vector<int>{
      4,2,
      2,4
      });
  EXPECT_TRUE(Matrix<int>::is_symmetric(test_mtr));

  test_mtr.set_elements(vector<int>{
      4,4,
      2,2
      });
  EXPECT_FALSE(Matrix<int>::is_symmetric(test_mtr));

  test_mtr = Matrix<int>(3,3);
  test_mtr.set_elements(vector<int>{
      4,2,1,
      2,3,5,
      1,5,7
      });
  EXPECT_TRUE(Matrix<int>::is_symmetric(test_mtr));

  test_mtr.set_elements(vector<int>{
      4,1,1,
      2,4,1,
      2,2,4
      });
  EXPECT_FALSE(Matrix<int>::is_symmetric(test_mtr));

}

TEST(MatrixClassification, AntiSymmetric) {
  Matrix<int> test_mtr(4,4);
  string result_class;

  test_mtr.set_elements(vector<int>{
      1,2,3,4,
      1,2,3,4,
      1,2,3,4,
      1,2,3,4
      });
  EXPECT_FALSE(Matrix<int>::is_antisymmetric(test_mtr));

  test_mtr.set_elements(vector<int>{
      0,2,3,4,
      1,0,3,4,
      1,2,0,4,
      1,2,3,0
      });
  EXPECT_TRUE(Matrix<int>::is_antisymmetric(test_mtr));
}


TEST(MatrixClassification, Scalar) {
  Matrix<int> test_mtr(4,4);
  string result_class;

  test_mtr.set_elements(vector<int>{
      1,2,3,4,
      1,2,3,4,
      1,2,3,4,
      1,2,3,4
      });
  EXPECT_FALSE(Matrix<int>::is_scalar(test_mtr));

  test_mtr.set_elements(vector<int>{
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1
      });
  EXPECT_TRUE(Matrix<int>::is_scalar(test_mtr));

  test_mtr = Matrix<int>(3,3);
  test_mtr.set_elements(vector<int>{
      3,0,0,
      0,3,0,
      0,0,3
      });
  EXPECT_TRUE(Matrix<int>::is_scalar(test_mtr));
}

TEST(MatrixClassification, Square) {
  Matrix<int> test_mtr = Matrix<int>(4,4);
  test_mtr.set_elements(vector<int>{
      2,2,2,2,
      2,2,2,2,
      2,2,2,2,
      2,2,2,2
  });
  EXPECT_TRUE(Matrix<int>::is_square(test_mtr));


  test_mtr = Matrix<int>(2,2);
  test_mtr.set_elements(vector<int>{
      4,4,
      4,4
  });
  EXPECT_TRUE(Matrix<int>::is_square(test_mtr));



  test_mtr = Matrix<int>(4,2);
  test_mtr.set_elements(vector<int>{
      4,2,
      4,2,
      4,2,
      4,2
  });
  EXPECT_FALSE(Matrix<int>::is_square(test_mtr));
}

