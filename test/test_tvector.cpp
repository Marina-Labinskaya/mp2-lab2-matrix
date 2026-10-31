#include "tmatrix.h"
#include <gtest.h>

TEST(TDynamicVectorTests, create_vector_with_positive_size_success)
{
  ASSERT_NO_THROW(TDynamicVector<int> vec(6));
}

TEST(TDynamicVectorTests, create_vector_with_overflow_size_throws)
{
  ASSERT_ANY_THROW(TDynamicVector<int> vec(MAX_VECTOR_SIZE + 2));
}

TEST(TDynamicVectorTests, create_vector_with_negative_size_throws)
{
  ASSERT_ANY_THROW(TDynamicVector<int> vec(-6));
}

TEST(TDynamicVectorTests, copy_constructor_copies_correctly)
{
  TDynamicVector<int> originalVec(12);
  ASSERT_NO_THROW(TDynamicVector<int> copiedVec(originalVec));
}

TEST(TDynamicVectorTests, copied_vector_elements_are_equal_to_source)
{
  TDynamicVector<int> originalVec(4);
  originalVec[0] = 45;
  originalVec[1] = 90;
  TDynamicVector<int> copiedVec(originalVec);
  EXPECT_TRUE(copiedVec == originalVec);
}

TEST(TDynamicVectorTests, copied_vector_has_allocated_distinct_memory)
{
  TDynamicVector<int> originalVec(5);
  originalVec[1] = 15;
  ASSERT_EQ(15, originalVec[1]);
  
  TDynamicVector<int> copiedVec(originalVec);
  copiedVec[1] = 30;
  
  ASSERT_EQ(30, copiedVec[1]);
  ASSERT_EQ(15, originalVec[1]);
}

TEST(TDynamicVectorTests, size_getter_returns_valid_length)
{
  TDynamicVector<int> vec(8);
  EXPECT_EQ(8, vec.size());
}

TEST(TDynamicVectorTests, element_access_set_and_get_value_success)
{
  TDynamicVector<int> vec(5);
  vec[3] = 71;
  EXPECT_EQ(71, vec[3]);
}

TEST(TDynamicVectorTests, index_out_of_bounds_negative_index_throws)
{
  TDynamicVector<int> vec(4);
  EXPECT_ANY_THROW(vec[-1] = 10);
}

TEST(TDynamicVectorTests, index_out_of_bounds_large_index_throws)
{
  TDynamicVector<int> vec(4);
  EXPECT_ANY_THROW(vec[4] = 10);
}

TEST(TDynamicVectorTests, self_assignment_preserves_vector_state)
{
  TDynamicVector<int> vec(3);
  vec[0] = 11;
  vec = vec;
  EXPECT_EQ(11, vec[0]);
}

TEST(TDynamicVectorTests, assignment_of_equal_sized_vectors_transfers_data)
{
  TDynamicVector<int> vec1(4), vec2(4);
  vec1[2] = 53;
  vec2 = vec1;
  EXPECT_TRUE(vec2 == vec1);
  vec2[2] = 80;
  EXPECT_EQ(53, vec1[2]);
}

TEST(TDynamicVectorTests, assignment_operator_modifies_destination_size)
{
  TDynamicVector<int> vecSmall(2), vecMedium(5), vecLarge(7);
  vecSmall = vecMedium;
  EXPECT_EQ(5, vecSmall.size());
  vecLarge = vecSmall;
  EXPECT_EQ(5, vecLarge.size());
}

TEST(TDynamicVectorTests, assignment_of_different_sized_vectors_works)
{
  TDynamicVector<int> vec1(3), vec2(6);
  vec1[1] = 44;
  vec2 = vec1;
  EXPECT_TRUE(vec2 == vec1);
  vec2[1] = 12;
  EXPECT_EQ(44, vec1[1]);
}

TEST(TDynamicVectorTests, identical_vectors_comparison_returns_true)
{
  TDynamicVector<int> vec1(3), vec2(3);
  EXPECT_TRUE(vec1 == vec2);
  EXPECT_FALSE(vec1 != vec2);
  
  vec2[0] = 5;
  EXPECT_TRUE(vec1 != vec2);
  EXPECT_FALSE(vec1 == vec2);
}

TEST(TDynamicVectorTests, standard_identity_comparison_returns_true)
{
  TDynamicVector<int> vec(4);
  EXPECT_TRUE(vec == vec);
}

TEST(TDynamicVectorTests, incompatible_sized_vectors_are_never_equal)
{
  TDynamicVector<int> vec1(3), vec2(6);
  EXPECT_TRUE(vec1 != vec2);
  EXPECT_FALSE(vec1 == vec2);
}

TEST(TDynamicVectorTests, scalar_addition_creates_correct_vector)
{
  TDynamicVector<int> vec(2), res(2);
  vec[0] = 10; vec[1] = 20;
  res = vec + 5;
  EXPECT_EQ(15, res[0]);
  EXPECT_EQ(25, res[1]);
}

TEST(TDynamicVectorTests, scalar_subtraction_creates_correct_vector)
{
  TDynamicVector<int> vec(2), res(2);
  vec[0] = 30; vec[1] = 40;
  res = vec - 10;
  EXPECT_EQ(20, res[0]);
  EXPECT_EQ(30, res[1]);
}

TEST(TDynamicVectorTests, scalar_multiplication_creates_correct_vector)
{
  TDynamicVector<int> vec(2), res(2);
  vec[0] = 4; vec[1] = 7;
  res = vec * 3;
  EXPECT_EQ(12, res[0]);
  EXPECT_EQ(21, res[1]);
}

TEST(TDynamicVectorTests, addition_of_compatible_vectors_sums_components)
{
  TDynamicVector<int> vec1(2), vec2(2), res(2);
  vec1[0] = 1; vec1[1] = 2;
  vec2[0] = 10; vec2[1] = 20;
  res = vec1 + vec2;
  EXPECT_EQ(11, res[0]);
  EXPECT_EQ(22, res[1]);
}

TEST(TDynamicVectorTests, addition_mismatch_dimensions_throws)
{
  TDynamicVector<int> vec1(3), vec2(5);
  EXPECT_ANY_THROW(vec1 + vec2);
}

TEST(TDynamicVectorTests, subtraction_of_compatible_vectors_diffs_components)
{
  TDynamicVector<int> vec1(2), vec2(2), res(2);
  vec1[0] = 50; vec1[1] = 60;
  vec2[0] = 10; vec2[1] = 20;
  res = vec1 - vec2;
  EXPECT_EQ(40, res[0]);
  EXPECT_EQ(40, res[1]);
}

TEST(TDynamicVectorTests, subtraction_mismatch_dimensions_throws)
{
  TDynamicVector<int> vec1(2), vec2(4);
  EXPECT_ANY_THROW(vec1 - vec2);
}

TEST(TDynamicVectorTests, vector_multiplication_calculates_valid_dot_product)
{
  TDynamicVector<int> vec1(2), vec2(2);
  vec1[0] = 2; vec1[1] = 3;
  vec2[0] = 4; vec2[1] = 5;
  int dotProduct = vec1 * vec2;
  EXPECT_EQ(23, dotProduct);
}

TEST(TDynamicVectorTests, dot_product_mismatch_dimensions_throws)
{
  TDynamicVector<int> vec1(3), vec2(6);
  EXPECT_ANY_THROW(vec1 * vec2);
}