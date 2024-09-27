#include <gtest/gtest.h>

#include "matrix_lib.h"
#include "utils.h"

using namespace std;

class MatrixLibFixture : public ::testing::Test {
protected:
  void SetUp() override {
  }

  void TearDown() override {
  }

};


TEST_F(MatrixLibFixture, CreateGetLineColumns) {
  Matrix test_mtr = Matrix(4,2);

  EXPECT_EQ(test_mtr.get_lines(), 4);
  EXPECT_EQ(test_mtr.get_columns(), 2);
}

TEST_F(MatrixLibFixture, PrintMtrElements) {
  Matrix test_mtr = Matrix(4,4);
  vector<int> elements = {
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1
  };
  test_mtr.set_elements(elements);

  string mtr_string = test_mtr.print().str();

  unsigned expected_0_ocrr = 12;
  unsigned expected_1_ocrr = 4;

  unsigned mtr_0_ocrr = t_utils::count_ocr(mtr_string, "0");
  unsigned mtr_1_ocrr = t_utils::count_ocr(mtr_string, "1");

  EXPECT_EQ(expected_0_ocrr, mtr_0_ocrr);
  EXPECT_EQ(expected_1_ocrr, mtr_1_ocrr);
}


TEST_F(MatrixLibFixture, ClassIdentity) {
  string result_class;
  vector<int> mtr_elements;

  Matrix test_mtr = Matrix(4,4);
  mtr_elements = {
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1
  };
  test_mtr.set_elements(mtr_elements);
  result_class = test_mtr.print_class().str();

  EXPECT_TRUE(t_utils::is_sub_str(result_class, "identity"));
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "square"));
  EXPECT_TRUE(test_mtr.is_square());
  EXPECT_TRUE(test_mtr.is_identity());

  mtr_elements.clear();


  test_mtr = Matrix(2,2);
  mtr_elements = {
    1,0,
    0,1
  };
  test_mtr.set_elements(mtr_elements);
  result_class = test_mtr.print_class().str();

  EXPECT_TRUE(t_utils::is_sub_str(result_class, "identity"));
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "square"));
  EXPECT_TRUE(test_mtr.is_square());
  EXPECT_TRUE(test_mtr.is_identity());
}


TEST_F(MatrixLibFixture, ClassNull) {
  Matrix test_mtr = Matrix(4,2);
  vector<int> elements = {
    0,0,
    0,0,
    0,0,
    0,0
  };
  test_mtr.set_elements(elements);
  string result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "null"));
  EXPECT_TRUE(test_mtr.is_null());

  test_mtr = Matrix(2,4);
  elements.clear();
  elements = {
    0,0,0,0,
    0,0,0,0
  };
  test_mtr.set_elements(elements);
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "null"));
  EXPECT_TRUE(test_mtr.is_null());
}

TEST_F(MatrixLibFixture, ClassColumn) {
  Matrix test_mtr = Matrix(4,2);
  string result_class;

  test_mtr.set_elements(vector<int>{
      1,1,
      1,1,
      1,1,
      1,1
      });
   result_class = test_mtr.print_class().str();
   EXPECT_FALSE(t_utils::is_sub_str(result_class, "column"));
   EXPECT_FALSE(test_mtr.is_column());


   test_mtr = Matrix(3,1);
   test_mtr.set_elements(vector<int>{
       0,
       0,
       0
       });
   result_class = test_mtr.print_class().str();
   EXPECT_TRUE(t_utils::is_sub_str(result_class, "column"));
   EXPECT_TRUE(test_mtr.is_column());
}

TEST_F(MatrixLibFixture, ClassLine) {
  Matrix test_mtr = Matrix(4,2);
  string result_class;

  test_mtr.set_elements(vector<int>{
      1,1,
      1,1,
      1,1,
      1,1
      });
   result_class = test_mtr.print_class().str();
   EXPECT_FALSE(t_utils::is_sub_str(result_class, "line"));
   EXPECT_FALSE(test_mtr.is_line());


   test_mtr = Matrix(1,3);
   test_mtr.set_elements(vector<int>{
       0,0,0
       });
   result_class = test_mtr.print_class().str();
   EXPECT_TRUE(t_utils::is_sub_str(result_class, "line"));
   EXPECT_TRUE(test_mtr.is_line());
}

TEST_F(MatrixLibFixture, ClassDiagonal) {
  Matrix test_mtr = Matrix(4,2);
  string result_class;

  test_mtr.set_elements(vector<int>{
      1,1,
      1,1,
      1,1,
      1,1
    });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "diagonal"));
  EXPECT_FALSE(test_mtr.is_diagonal());

  test_mtr = Matrix(4,4);
  test_mtr.set_elements(vector<int>{
     1,1,1,1,
     1,1,1,1,
     1,1,1,1,
     1,1,1,1
     });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "diagonal"));
  EXPECT_FALSE(test_mtr.is_diagonal());



  test_mtr = Matrix(4,4);
  test_mtr.set_elements(vector<int>{
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "diagonal"));
  EXPECT_TRUE(test_mtr.is_diagonal());

  test_mtr = Matrix(5,5);
  test_mtr.set_elements(vector<int>{
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

TEST_F(MatrixLibFixture, ClassUpperTriangular) {
  Matrix test_mtr(4,4);
  string result_class;

  test_mtr.set_elements(vector<int>{
       1,1,1,1,
       0,2,2,2,
       0,0,3,3,
       0,0,0,4
    });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "upper triangular"));
  EXPECT_TRUE(test_mtr.is_upper_tri());

  test_mtr.set_elements(vector<int>{
       1,1,1,1,
       2,2,2,2,
       3,3,3,3,
       4,4,0,4
    });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "upper triangular"));
  EXPECT_FALSE(test_mtr.is_upper_tri());
}

TEST_F(MatrixLibFixture, ClassLowerTriangular) {
  Matrix test_mtr(4,4);
  string result_class;

  test_mtr.set_elements(vector<int>{
       1,0,0,0,
       2,2,0,0,
       3,3,3,0,
       4,4,4,4
    });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "lower triangular"));
  EXPECT_TRUE(test_mtr.is_lower_tri());

  test_mtr.set_elements(vector<int>{
       1,1,1,1,
       2,2,2,2,
       3,3,3,3,
       4,4,0,4
    });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "lower triangular"));
  EXPECT_FALSE(test_mtr.is_lower_tri());
}

TEST_F(MatrixLibFixture, ClassSymmetric) {
  Matrix test_mtr(1,1);
  string result_class;

  test_mtr.set_elements(vector<int>{
      4
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "symmetric"));
  EXPECT_TRUE(test_mtr.is_symmetric());


  test_mtr = Matrix(2,2);
  test_mtr.set_elements(vector<int>{
      4,2,
      2,4
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(test_mtr.is_symmetric());
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "symmetric"));

  test_mtr.set_elements(vector<int>{
      4,4,
      2,2
      });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(test_mtr.is_symmetric());
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "symmetric"));

  test_mtr = Matrix(3,3);
  test_mtr.set_elements(vector<int>{
      4,2,1,
      2,3,5,
      1,5,7
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(test_mtr.is_symmetric());
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "symmetric"));

  test_mtr.set_elements(vector<int>{
      4,1,1,
      2,4,1,
      2,2,4
      });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(test_mtr.is_symmetric());
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "symmetric"));

}

TEST_F(MatrixLibFixture, ClassAntiSymmetric) {
  Matrix test_mtr(4,4);
  string result_class;

  test_mtr.set_elements(vector<int>{
      1,2,3,4,
      1,2,3,4,
      1,2,3,4,
      1,2,3,4
      });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(test_mtr.is_antisymmetric());
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "antisymmetric"));

  test_mtr.set_elements(vector<int>{
      0,2,3,4,
      1,0,3,4,
      1,2,0,4,
      1,2,3,0
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(test_mtr.is_antisymmetric());
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "antisymmetric"));
}


TEST_F(MatrixLibFixture, ClassScalar) {
  Matrix test_mtr(4,4);
  string result_class;

  test_mtr.set_elements(vector<int>{
      1,2,3,4,
      1,2,3,4,
      1,2,3,4,
      1,2,3,4
      });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(test_mtr.is_scalar());
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "scalar"));

  test_mtr.set_elements(vector<int>{
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(test_mtr.is_scalar());
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "scalar"));

  test_mtr = Matrix(3,3);
  test_mtr.set_elements(vector<int>{
      3,0,0,
      0,3,0,
      0,0,3
      });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(test_mtr.is_scalar());
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "scalar"));
}

TEST_F(MatrixLibFixture, ClassSquare) {
  Matrix test_mtr = Matrix(4,4);
  test_mtr.set_elements(vector<int>{
      2,2,2,2,
      2,2,2,2,
      2,2,2,2,
      2,2,2,2
  });
  string result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "square"));
  EXPECT_TRUE(test_mtr.is_square());


  test_mtr = Matrix(2,2);
  test_mtr.set_elements(vector<int>{
      4,4,
      4,4
  });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "square"));
  EXPECT_TRUE(test_mtr.is_square());



  test_mtr = Matrix(4,2);
  test_mtr.set_elements(vector<int>{
      4,2,
      4,2,
      4,2,
      4,2
  });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "square"));
  EXPECT_FALSE(test_mtr.is_square());
}


TEST_F(MatrixLibFixture, MtrTranspose) {
  Matrix test_mtr = Matrix(4,4);
  test_mtr.set_elements(vector<int>{
      1,2,3,4,
      8,7,6,5,
      2,2,2,2,
      4,4,4,4
      });
  Matrix transposed_mtr = test_mtr.transpose();

  for(int i=0; i < 4; i++)
    for(int j=0; j < 4; j++)
      EXPECT_EQ(test_mtr.at(i, j), transposed_mtr.at(j, i));

}



TEST_F(MatrixLibFixture, MtrStroke) {
  Matrix test_mtr = Matrix(4,4);
  test_mtr.set_elements(vector<int>{
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1
      });
  EXPECT_EQ(4, test_mtr.stroke());

  test_mtr = Matrix(6,6);
  test_mtr.set_elements(vector<int> {
      7,0,0,0,0,0,
      0,7,0,0,0,0,
      0,0,7,0,0,0,
      0,0,0,7,0,0,
      0,0,0,0,7,0,
      0,0,0,0,0,7,
      });
  EXPECT_EQ(42, test_mtr.stroke());
}


TEST_F(MatrixLibFixture, MtrSum) {
  Matrix test_mtr1 = Matrix(4,4);
  test_mtr1.set_elements(vector<int>{
      2,2,2,2,
      2,2,2,2,
      2,2,2,2,
      2,2,2,2
      });
  Matrix test_mtr2 = Matrix(4,4);
  test_mtr2.set_elements(vector<int>{
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1
      });

  Matrix sum_result = test_mtr1 + test_mtr2;

  Matrix expected = Matrix(4,4);
  expected.set_elements(vector<int>{
      3,3,3,3,
      3,3,3,3,
      3,3,3,3,
      3,3,3,3
      });

  EXPECT_EQ(expected, sum_result);

}


TEST_F(MatrixLibFixture, MtrDiff) {
  Matrix test_mtr1 = Matrix(4,4);
  test_mtr1.set_elements(vector<int>{
      3,3,3,3,
      3,3,3,3,
      3,3,3,3,
      3,3,3,3
      });
  Matrix test_mtr2 = Matrix(4,4);
  test_mtr2.set_elements(vector<int>{
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1
      });

  Matrix diff_result = test_mtr1 - test_mtr2;

  Matrix expected = Matrix(4,4);
  expected.set_elements(vector<int>{
      2,2,2,2,
      2,2,2,2,
      2,2,2,2,
      2,2,2,2
      });

  EXPECT_EQ(expected, diff_result);

}


TEST_F(MatrixLibFixture, MtrMultiplScalar) {
  Matrix test_mtr = Matrix(6,6);
  test_mtr.set_elements(vector<int>{
      7,7,7,7,7,7,
      7,7,7,7,7,7,
      7,7,7,7,7,7,
      7,7,7,7,7,7,
      7,7,7,7,7,7,
      7,7,7,7,7,7
      });

  Matrix multpl_result = test_mtr * 6;

  Matrix expected = Matrix(6,6);
  expected.set_elements(vector<int>{
      42,42,42,42,42,42,
      42,42,42,42,42,42,
      42,42,42,42,42,42,
      42,42,42,42,42,42,
      42,42,42,42,42,42,
      42,42,42,42,42,42,
      });

  EXPECT_EQ(expected, multpl_result);
}


TEST_F(MatrixLibFixture, MtrMultiplMtr) {
  Matrix test_mtr1 = Matrix(4,4);
  Matrix test_mtr2 = Matrix(4,4);
  Matrix expected = Matrix(4,4);

  test_mtr1.set_elements(vector<int>{
      2,3,1,2,
      1,1,1,1,
      2,2,2,2,
      2,1,3,2
      });
  test_mtr2.set_elements(vector<int>{
      5,1,3,2,
      2,1,3,9,
      2,1,3,2,
      2,1,3,2
      });
  expected.set_elements({
      22, 8, 24, 37,
      11, 4, 12, 15,
      22, 8, 24, 30,
      22, 8, 24, 23
      });

  EXPECT_EQ(expected, test_mtr1 * test_mtr2);


  test_mtr1 = Matrix(2,4);
  test_mtr2 = Matrix(4,2);
  expected = Matrix(2,2);

  test_mtr1.set_elements(vector<int>{
      1,2,3,4,
      3,3,3,3
      });
  test_mtr2.set_elements(vector<int>{
      1,2,
      3,4,
      7,7,
      7,7,
      });
  expected.set_elements(vector<int>{
      56, 59,
      54, 60
      });

  EXPECT_EQ(expected, test_mtr1 * test_mtr2);
}

TEST_F(MatrixLibFixture, MtrComparator) {
  Matrix test_mtr1 = Matrix(4,4);
  Matrix test_mtr2 = Matrix(4,4);
  Matrix test_mtr3 = Matrix(4,4);
  Matrix test_mtr4 = Matrix(2,2);

  test_mtr1.set_elements(vector<int>{
      1,2,3,4,
      4,3,2,1,
      1,2,3,4,
      4,3,2,1,
      });
  test_mtr2.set_elements(vector<int>{
      1,2,3,4,
      4,3,2,1,
      1,2,3,4,
      4,3,2,1,
      });
  EXPECT_TRUE(test_mtr1 == test_mtr2);

  test_mtr3.set_elements(vector<int>{
      1,2,3,4,
      1,2,3,4,
      1,2,3,4,
      1,2,3,4,
      });
  EXPECT_FALSE(test_mtr1 == test_mtr3);

  test_mtr4.set_elements(vector<int>{
      1,1,
      1,1
      });
  EXPECT_FALSE(test_mtr1 == test_mtr4);
}


TEST_F(MatrixLibFixture, MtrDetOrder1) {
  Matrix test_mtr = Matrix(1,1);
  long expected_det;

  test_mtr.set_elements(vector<int>{
      40
      });
  expected_det = 40;

  EXPECT_EQ(expected_det, test_mtr.det());
}

TEST_F(MatrixLibFixture, MtrDetOrder2) {
  Matrix test_mtr = Matrix(2,2);
  long expected_det;

  test_mtr.set_elements(vector<int>{
      22, 11,
      2,  5
      });
  expected_det = 88;

  EXPECT_EQ(expected_det, test_mtr.det());
}

TEST_F(MatrixLibFixture, MtrDetOrder3) {
  Matrix test_mtr(3,3);
  long expected_det;

  test_mtr.set_elements(vector<int>{
      1,2,3,
      4,5,6,
      7,8,9
      });
  expected_det = 0;
  EXPECT_EQ(expected_det, test_mtr.det());

  test_mtr.set_elements(vector<int>{
      6, 1,  1,
      4, -2, 5,
      2, 8,  7
      });
  expected_det = -306;
  EXPECT_EQ(expected_det, test_mtr.det());

  test_mtr.set_elements(vector<int>{
      10, -7, 3,
      -3, 6, 2,
      5, 8, 9
      });
  expected_det = -41;
  EXPECT_EQ(expected_det, test_mtr.det());


  test_mtr.set_elements(vector<int>{
      1, 0, 0,
      0, 1, 0,
      0, 0, 1
      });
  expected_det = 1;
  EXPECT_EQ(expected_det, test_mtr.det());
}


// TEST_F(MatrixLibFixture, MtrDetOrderN) {
//   Matrix test_mtr(4,4);
//   test_mtr.set_elements(vector<int>{
//       1,2,3,4,
//       5,6,7,8,
//       9,10,11,12,
//       13,14,15,16
//       });
//   long expected_det;
// }
