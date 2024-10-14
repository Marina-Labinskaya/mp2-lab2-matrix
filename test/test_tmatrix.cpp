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
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;
	TDynamicMatrix<int> m1(m);

	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int>* pm = &m;
	TDynamicMatrix<int> m1(m);
	TDynamicMatrix<int>* pm1 = &m1;

	EXPECT_NE(pm, pm1);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);

	EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	m[0][2] = 10;

	EXPECT_EQ(10, m[0][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	ASSERT_ANY_THROW(m.at(-1).at(-2) = 10);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	ASSERT_ANY_THROW(m.at(10).at(12) = 10);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;
	m = m;

	EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;
	TDynamicMatrix<int> m1(5);
	m1[0] = vrow1; m1[1] = vrow2; m1[2] = vrow3; m1[3] = vrow4; m1[4] = vrow0;

	m = m1;

	EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;
	int* row00 = new int[4] {0, 1, 2, 3};
	TDynamicVector<int> vrow00(row00, 4);
	int* row10 = new int[4] {5, 6, 7, 8};
	TDynamicVector<int> vrow10(row10, 4);
	int* row20 = new int[4] {10, 11, 12, 14};
	TDynamicVector<int> vrow20(row20, 4);
	int* row30 = new int[4] {15, 16, 17, 18};
	TDynamicVector<int> vrow30(row30, 4);
	TDynamicMatrix<int> m1(4);
	m1[0] = vrow00; m1[1] = vrow10; m1[2] = vrow20; m1[3] = vrow30;

	m = m1;

	EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;
	int* row00 = new int[3] {0, 1, 2};
	TDynamicVector<int> vrow00(row00, 3);
	int* row10 = new int[3] {5, 6, 7};
	TDynamicVector<int> vrow10(row10, 3);
	int* row20 = new int[3] {10, 11, 12};
	TDynamicVector<int> vrow20(row20, 3);
	TDynamicMatrix<int> m1(3);
	m1[0] = vrow00; m1[1] = vrow10; m1[2] = vrow20;

	m = m1;

	EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;
	TDynamicMatrix<int> m1(5);
	m1[0] = vrow0; m1[1] = vrow1; m1[2] = vrow2; m1[3] = vrow3; m1[4] = vrow4;

	EXPECT_EQ(1, m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	EXPECT_EQ(1, m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;
	int* row00 = new int[3] {0, 1, 2};
	TDynamicVector<int> vrow00(row00, 3);
	int* row10 = new int[3] {5, 6, 7};
	TDynamicVector<int> vrow10(row10, 3);
	int* row20 = new int[3] {10, 11, 12};
	TDynamicVector<int> vrow20(row20, 3);
	TDynamicMatrix<int> m1(3);
	m1[0] = vrow00; m1[1] = vrow10; m1[2] = vrow20;

	EXPECT_EQ(0, m==m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;
	TDynamicMatrix<int> m1(5);
	m1[0] = vrow1; m1[1] = vrow2; m1[2] = vrow3; m1[3] = vrow4; m1[4] = vrow0;
	TDynamicMatrix<int> m2(5);
	m2 = m + m1;
	int* row00 = new int[5] {5, 7, 9, 11, 13};
	TDynamicVector<int> vrow00(row00, 5);
	int* row10 = new int[5] {15, 17, 19, 21, 23};
	TDynamicVector<int> vrow10(row10, 5);
	int* row20 = new int[5] {25, 27, 29, 31, 33};
	TDynamicVector<int> vrow20(row20, 5);
	int* row30 = new int[5] {35, 37, 39, 41, 43};
	TDynamicVector<int> vrow30(row30, 5);
	int* row40 = new int[5] {20, 22, 24, 26, 28};
	TDynamicVector<int> vrow40(row40, 5);
	TDynamicMatrix<int> m3(5);
	m3[0] = vrow00; m3[1] = vrow10; m3[2] = vrow20; m3[3] = vrow30; m3[4] = vrow40;

	EXPECT_EQ(m3,m2);
	
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;
	int* row00 = new int[3] {0, 1, 2};
	TDynamicVector<int> vrow00(row00, 3);
	int* row10 = new int[3] {5, 6, 7};
	TDynamicVector<int> vrow10(row10, 3);
	int* row20 = new int[3] {10, 11, 12};
	TDynamicVector<int> vrow20(row20, 3);
	TDynamicMatrix<int> m1(3);
	m1[0] = vrow00; m1[1] = vrow10; m1[2] = vrow20;

	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;
	TDynamicMatrix<int> m1(5);
	m1[0] = vrow1; m1[1] = vrow2; m1[2] = vrow3; m1[3] = vrow4; m1[4] = vrow0;
	TDynamicMatrix<int> m2(5);
	m2 = m - m1;
	int* row00 = new int[5] {-5, -5, -5, -5, -5};
	TDynamicVector<int> vrow00(row00, 5);
	int* row10 = new int[5] {-5, -5, -5, -5, -5};
	TDynamicVector<int> vrow10(row10, 5);
	int* row20 = new int[5] {-5, -5, -5, -5, -5};
	TDynamicVector<int> vrow20(row20, 5);
	int* row30 = new int[5] {-5, -5, -5, -5, -5};
	TDynamicVector<int> vrow30(row30, 5);
	int* row40 = new int[5] {20, 20, 20, 20, 20};
	TDynamicVector<int> vrow40(row40, 5);
	TDynamicMatrix<int> m3(5);
	m3[0] = vrow00; m3[1] = vrow10; m3[2] = vrow20; m3[3] = vrow30; m3[4] = vrow40;

	EXPECT_EQ(m3, m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	TDynamicVector<int> vrow0(row0, 5);
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	TDynamicVector<int> vrow1(row1, 5);
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	TDynamicVector<int> vrow2(row2, 5);
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	TDynamicVector<int> vrow3(row3, 5);
	int* row4 = new int[5] {20, 21, 22, 23, 24};
	TDynamicVector<int> vrow4(row4, 5);
	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;
	int* row00 = new int[3] {0, 1, 2};
	TDynamicVector<int> vrow00(row00, 3);
	int* row10 = new int[3] {5, 6, 7};
	TDynamicVector<int> vrow10(row10, 3);
	int* row20 = new int[3] {10, 11, 12};
	TDynamicVector<int> vrow20(row20, 3);
	TDynamicMatrix<int> m1(3);
	m1[0] = vrow00; m1[1] = vrow10; m1[2] = vrow20;

	ASSERT_ANY_THROW(m - m1);
}

