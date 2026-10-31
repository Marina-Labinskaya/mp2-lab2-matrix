#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2;
	m[1][0] = 3; m[1][1] = 4;

	TDynamicMatrix<int> mcopy(m);

	EXPECT_EQ(m, mcopy);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 52;

	TDynamicMatrix<int> mcopy(m);
	mcopy[0][0] = 67;

	EXPECT_NE(m[0][0], mcopy[0][0]);
	EXPECT_NE(&m[0][0], &mcopy[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(3);

	EXPECT_EQ(3, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(3);
	m[1][1] = 5;

    EXPECT_EQ(5, m[1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(3);

	ASSERT_ANY_THROW(m.at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(3);

	ASSERT_ANY_THROW(m.at(7));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 10;m[0][1] = 20;m[0][2] = 30;
	m[1][0] = 40;m[1][1] = 50;m[1][2] = 60;
	m[2][0] = 70;m[2][1] = 80;m[2][2] = 90;
	ASSERT_NO_THROW(m = m);

	EXPECT_EQ(10, m[0][0]);
	EXPECT_EQ(20, m[0][1]);
	EXPECT_EQ(30, m[0][2]);
	EXPECT_EQ(40, m[1][0]);
	EXPECT_EQ(50, m[1][1]);
	EXPECT_EQ(60, m[1][2]);
	EXPECT_EQ(70, m[2][0]);
	EXPECT_EQ(80, m[2][1]);
	EXPECT_EQ(90, m[2][2]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 6;m1[0][1] = 7;
	m1[1][0] = 5;m1[1][1] = 2;

	ASSERT_NO_THROW(m1 = m2);

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(2), m2(5);

	m2 = m1;

	EXPECT_EQ(2, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(2), m2(4);
	m1[0][0] = 7;

	m2 = m1;

	EXPECT_EQ(m1, m2);
	EXPECT_EQ(2, m2.size());
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][0] = 3; m1[1][1] = 4;

	m2[0][0] = 1; m2[0][1] = 2;
	m2[1][0] = 3; m2[1][1] = 4;

	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 4;m[0][1] = 2;
	m[1][0] = 2;m[1][1] = 4;

	EXPECT_TRUE(m == m);
}


TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(2), m2(3);

	EXPECT_FALSE(m1 == m2);
	EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][0] = 3; m1[1][1] = 4;

	m2[0][0] = 10; m2[0][1] = 20;
	m2[1][0] = 30; m2[1][1] = 40;

	TDynamicMatrix<int> res = m1 + m2;

	EXPECT_EQ(11, res[0][0]);
	EXPECT_EQ(22, res[0][1]);
	EXPECT_EQ(33, res[1][0]);
	EXPECT_EQ(44, res[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(3);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 15; m1[0][1] = 25;
	m1[1][0] = 35; m1[1][1] = 45;

	m2[0][0] = 5;  m2[0][1] = 10;
	m2[1][0] = 15; m2[1][1] = 20;

	TDynamicMatrix<int> res = m1 - m2;

	EXPECT_EQ(10, res[0][0]);
	EXPECT_EQ(15, res[0][1]);
	EXPECT_EQ(20, res[1][0]);
	EXPECT_EQ(25, res[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(3);

	ASSERT_ANY_THROW(m1 - m2);
}

