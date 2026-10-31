#include "tmatrix.h"
#include <gtest.h>

TEST(TDynamicMatrixTests, create_matrix_valid_size_success)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> mat(4));
}

TEST(TDynamicMatrixTests, create_matrix_overflow_size_throws)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> mat(MAX_MATRIX_SIZE + 2));
}

TEST(TDynamicMatrixTests, create_matrix_negative_size_throws)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> mat(-3));
}

TEST(TDynamicMatrixTests, copy_constructor_executes_without_error)
{
  TDynamicMatrix<int> originMat(6);
  ASSERT_NO_THROW(TDynamicMatrix<int> copiedMat(originMat));
}

TEST(TDynamicMatrixTests, copied_matrix_has_identical_elements)
{
  TDynamicMatrix<int> originMat(3);
  originMat[1][1] = 95;
  TDynamicMatrix<int> copiedMat(originMat);
  EXPECT_TRUE(copiedMat == originMat);
}

TEST(TDynamicMatrixTests, copied_matrix_allocates_isolated_memory_block)
{
  TDynamicMatrix<int> originMat(4);
  originMat[0][0] = 40;
  ASSERT_EQ(40, originMat[0][0]);
  
  TDynamicMatrix<int> copiedMat(originMat);
  copiedMat[0][0] = 88;
  
  ASSERT_EQ(88, copiedMat[0][0]); 
  ASSERT_EQ(40, originMat[0][0]);
}

TEST(TDynamicMatrixTests, size_getter_returns_correct_dimension)
{
  TDynamicMatrix<int> mat(7);
  EXPECT_EQ(7, mat.size());
}

TEST(TDynamicMatrixTests, element_access_set_and_get_correctly)
{
  TDynamicMatrix<int> mat(3);
  mat[1][1] = 14;
  EXPECT_EQ(14, mat[1][1]);
}

TEST(TDynamicMatrixTests, index_out_of_bounds_negative_throws)
{
  TDynamicMatrix<int> mat(3);
  EXPECT_ANY_THROW(mat[-1][0] = 5);
  EXPECT_ANY_THROW(mat[0][-2] = 5);
}

TEST(TDynamicMatrixTests, index_out_of_bounds_too_large_throws)
{
  TDynamicMatrix<int> mat(4);
  EXPECT_ANY_THROW(mat[4][0] = 5);
  EXPECT_ANY_THROW(mat[0][4] = 5);
}

TEST(TDynamicMatrixTests, assignment_to_self_maintains_integrity)
{
  TDynamicMatrix<int> mat(3);
  mat[0][0] = 55;
  mat = mat;
  EXPECT_EQ(mat[0][0], 55);
}

TEST(TDynamicMatrixTests, assignment_of_equal_sized_matrices_copies_values)
{
  TDynamicMatrix<int> mat1(3), mat2(3);
  mat1[0][0] = 12;
  mat2 = mat1;
  EXPECT_TRUE(mat2 == mat1);
  mat2[0][0] = 99;
  EXPECT_EQ(mat1[0][0], 12);
}

TEST(TDynamicMatrixTests, assignment_correctly_resizes_destination)
{
  TDynamicMatrix<int> smallMat(2), mediumMat(4), largeMat(6);
  smallMat = mediumMat;
  EXPECT_EQ(4, smallMat.size());
  largeMat = smallMat;
  EXPECT_EQ(4, largeMat.size());
}

TEST(TDynamicMatrixTests, assignment_of_different_sized_matrices_works)
{
  TDynamicMatrix<int> mat1(2), mat2(5);
  mat1[0][0] = 77;
  mat2 = mat1;
  EXPECT_TRUE(mat2 == mat1);
  mat2[0][0] = 11;
  EXPECT_EQ(mat1[0][0], 77);
}

TEST(TDynamicMatrixTests, equality_and_inequality_operators_return_correct_bool)
{
  TDynamicMatrix<int> mat1(3), mat2(3);
  EXPECT_TRUE(mat1 == mat2); 
  EXPECT_FALSE(mat1 != mat2);
  
  mat2[0][0] = 5;
  EXPECT_TRUE(mat1 != mat2); 
  EXPECT_FALSE(mat1 == mat2);
}

TEST(TDynamicMatrixTests, identity_comparison_returns_true)
{
  TDynamicMatrix<int> mat(3);
  EXPECT_TRUE(mat == mat);
}

TEST(TDynamicMatrixTests, dimension_mismatch_matrices_are_never_equal)
{
  TDynamicMatrix<int> mat1(2), mat2(5);
  EXPECT_TRUE(mat1 != mat2); 
  EXPECT_FALSE(mat1 == mat2);
}

TEST(TDynamicMatrixTests, addition_of_compatible_matrices_sums_elements)
{
  TDynamicMatrix<int> mat1(2), mat2(2), res(2);
  mat1[0][0] = 10; mat1[1][1] = 20;
  mat2[0][0] = 5;  mat2[1][1] = 15;
  
  EXPECT_NO_THROW(mat1 + mat2); 
  res = mat1 + mat2;
  
  EXPECT_EQ(res[0][0], 15); 
  EXPECT_EQ(res[1][1], 35);
}

TEST(TDynamicMatrixTests, addition_mismatch_dimensions_throws)
{
  TDynamicMatrix<int> mat1(3), mat2(4);
  EXPECT_ANY_THROW(mat1 + mat2);
}

TEST(TDynamicMatrixTests, subtraction_of_compatible_matrices_diffs_elements)
{
  TDynamicMatrix<int> mat1(2), mat2(2), res(2);
  mat1[0][0] = 30; mat1[1][1] = 40;
  mat2[0][0] = 10; mat2[1][1] = 15;
  
  EXPECT_NO_THROW(mat1 - mat2); 
  res = mat1 - mat2;
  
  EXPECT_EQ(res[0][0], 20); 
  EXPECT_EQ(res[1][1], 25);
}

TEST(TDynamicMatrixTests, subtraction_mismatch_dimensions_throws)
{
  TDynamicMatrix<int> mat1(2), mat2(5);
  EXPECT_ANY_THROW(mat1 - mat2);
}

TEST(TDynamicMatrixTests, matrix_multiplication_calculates_correct_dot_product)
{
  TDynamicMatrix<int> mat1(2), mat2(2), res(2);
  mat1[0][0] = 2; mat1[0][1] = 1;
  mat1[1][0] = 0; mat1[1][1] = 3;

  mat2[0][0] = 4; mat2[0][1] = 5;
  mat2[1][0] = 1; mat2[1][1] = 2;
  
  EXPECT_NO_THROW(mat1 * mat2); 
  res = mat1 * mat2;
  
  EXPECT_EQ(res[0][0], 9);  
  EXPECT_EQ(res[0][1], 12);
  EXPECT_EQ(res[1][0], 3);  
  EXPECT_EQ(res[1][1], 6);
}

TEST(TDynamicMatrixTests, matrix_multiplication_mismatch_dimensions_throws)
{
  TDynamicMatrix<int> mat1(3), mat2(6);
  EXPECT_ANY_THROW(mat1 * mat2);
}

TEST(TDynamicMatrixTests, constructor_boundaries_and_default_state) 
{
  TDynamicMatrix<int> defaultMat;
  ASSERT_EQ(1, defaultMat.size());
  EXPECT_EQ(0, defaultMat[0][0]);
  EXPECT_ANY_THROW(TDynamicMatrix<int> zeroMat(0));
}

TEST(TDynamicMatrixTests, scalar_operations_preserve_original_matrix) 
{
  TDynamicMatrix<int> originalMat(2);
  originalMat[0][0] = 2; originalMat[0][1] = 4;
  originalMat[1][0] = 6; originalMat[1][1] = 8;
  
  const TDynamicMatrix<int> checkpoint(originalMat);
  auto plusRes = originalMat + 3;
  auto minusRes = originalMat - 1;
  auto multiRes = originalMat * 2;
  
  for (size_t r = 0; r < 2; ++r) {
    for (size_t c = 0; c < 2; ++c) {
      EXPECT_EQ(checkpoint[r][c] + 3, plusRes[r][c]);
      EXPECT_EQ(checkpoint[r][c] - 1, minusRes[r][c]);
      EXPECT_EQ(checkpoint[r][c] * 2, multiRes[r][c]);
    }
  }
  EXPECT_EQ(originalMat, checkpoint);
}

TEST(TDynamicMatrixTests, matrix_vector_multiplication_returns_correct_vector) 
{
  TDynamicMatrix<int> mat(2);
  mat[0][0] = 2; mat[0][1] = 3;
  mat[1][0] = 1; mat[1][1] = 4;
  
  int rawData[] = {1, 2};
  TDynamicVector<int> vec(rawData, 2);
  const TDynamicMatrix<int> checkpoint(mat);
  
  auto resVec = mat * vec;
  ASSERT_EQ(2, resVec.size());
  EXPECT_EQ(8, resVec[0]); 
  EXPECT_EQ(9, resVec[1]);
  EXPECT_TRUE(mat == checkpoint);
}

TEST(TDynamicMatrixTests, vector_multiplication_dimension_mismatch_throws) 
{
  TDynamicMatrix<int> mat(2);
  TDynamicVector<int> invalidVec(5);
  EXPECT_ANY_THROW(mat * invalidVec);
}

TEST(TDynamicMatrixTests, matrix_stream_input_and_output_operators) 
{
  TDynamicMatrix<int> mat(2);
  std::istringstream streamIn("5 6 7 8");
  EXPECT_EQ(&streamIn, &(streamIn >> mat));
  EXPECT_FALSE(streamIn.fail());
  
  EXPECT_EQ(5, mat[0][0]); EXPECT_EQ(6, mat[0][1]);
  EXPECT_EQ(7, mat[1][0]); EXPECT_EQ(8, mat[1][1]);
  
  std::ostringstream streamOut;
  EXPECT_EQ(&streamOut, &(streamOut << mat));
  EXPECT_EQ("( 5 6 )\n( 7 8 )\n", streamOut.str());
  
  std::istringstream streamBad("5 6 invalidData 8");
  streamBad >> mat;
  EXPECT_TRUE(streamBad.fail());
}

TEST(TDynamicMatrixTests, explicit_matrix_destruction_clears_resources)
{
  auto* volatileMat = new TDynamicMatrix<int>(3);
  (*volatileMat)[0][0] = 100;
  EXPECT_NO_THROW(delete volatileMat);
}

