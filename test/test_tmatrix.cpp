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
	//------------Инициализация матрицы------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

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
	//------------Инициализация матрицы------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	EXPECT_EQ(vrow0, m[0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	//------------Инициализация матрицы------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	ASSERT_ANY_THROW(m.at(-1) = vrow0);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	//------------Инициализация матрицы------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	ASSERT_ANY_THROW(m.at(10) = vrow0);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	//------------Инициализация матрицы------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	m = m;

	EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	//------------Инициализация матрицы------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	TDynamicMatrix<int> m1(5);
	m1[0] = vrow1; m1[1] = vrow2; m1[2] = vrow3; m1[3] = vrow4; m1[4] = vrow0;

	m = m1;

	EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	//------------Инициализация матрицы1------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	//------------Инициализация матрицы2------------
	int* row00 = new int[4] {0, 1, 2, 3};
	int* row10 = new int[4] {5, 6, 7, 8};
	int* row20 = new int[4] {10, 11, 12, 14};
	int* row30 = new int[4] {15, 16, 17, 18};

	TDynamicVector<int> vrow00(row00, 4);
	TDynamicVector<int> vrow10(row10, 4);
	TDynamicVector<int> vrow20(row20, 4);
	TDynamicVector<int> vrow30(row30, 4);

	delete[] row00; delete[] row10; delete[] row20; delete[] row30;

	TDynamicMatrix<int> m1(4);
	m1[0] = vrow00; m1[1] = vrow10; m1[2] = vrow20; m1[3] = vrow30;
	//-----------------------------------------------

	m = m1;

	EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	//------------Инициализация матрицы1------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------
	
	//------------Инициализация матрицы2------------
	int* row00 = new int[4] {0, 1, 2, 3};
	int* row10 = new int[4] {5, 6, 7, 8};
	int* row20 = new int[4] {10, 11, 12, 14};
	int* row30 = new int[4] {15, 16, 17, 18};

	TDynamicVector<int> vrow00(row00, 4);
	TDynamicVector<int> vrow10(row10, 4);
	TDynamicVector<int> vrow20(row20, 4);
	TDynamicVector<int> vrow30(row30, 4);

	delete[] row00; delete[] row10; delete[] row20; delete[] row30;

	TDynamicMatrix<int> m1(4);
	m1[0] = vrow00; m1[1] = vrow10; m1[2] = vrow20; m1[3] = vrow30;
	//-----------------------------------------------

	m = m1;

	EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	//------------Инициализация матрицы------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	TDynamicMatrix<int> m1(5);
	m1[0] = vrow0; m1[1] = vrow1; m1[2] = vrow2; m1[3] = vrow3; m1[4] = vrow4;

	EXPECT_EQ(1, m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	//------------Инициализация матрицы------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	EXPECT_EQ(1, m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	//------------Инициализация матрицы1------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------
	
	//------------Инициализация матрицы2------------
	int* row00 = new int[4] {0, 1, 2, 3};
	int* row10 = new int[4] {5, 6, 7, 8};
	int* row20 = new int[4] {10, 11, 12, 14};
	int* row30 = new int[4] {15, 16, 17, 18};

	TDynamicVector<int> vrow00(row00, 4);
	TDynamicVector<int> vrow10(row10, 4);
	TDynamicVector<int> vrow20(row20, 4);
	TDynamicVector<int> vrow30(row30, 4);

	delete[] row00; delete[] row10; delete[] row20; delete[] row30;

	TDynamicMatrix<int> m1(4);
	m1[0] = vrow00; m1[1] = vrow10; m1[2] = vrow20; m1[3] = vrow30;
	//-----------------------------------------------

	EXPECT_EQ(0, m==m1);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_scalar)
{
	//------------Инициализация матрицы1------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	m = m * 2;

	//------------Инициализация матрицы2 - результат операции ------------
	int* row00 = new int[5] {0, 2, 4, 6, 8};
	int* row10 = new int[5] {10, 12, 14, 16, 18};
	int* row20 = new int[5] {20, 22, 24, 26, 28};
	int* row30 = new int[5] {30, 32, 34, 36, 38};
	int* row40 = new int[5] {40, 42, 44, 46, 48};

	TDynamicVector<int> vrow00(row00, 5);
	TDynamicVector<int> vrow10(row10, 5);
	TDynamicVector<int> vrow20(row20, 5);
	TDynamicVector<int> vrow30(row30, 5);
	TDynamicVector<int> vrow40(row40, 5);

	delete[] row00; delete[] row10; delete[] row20; delete[] row30; delete[] row40;

	TDynamicMatrix<int> m3(5);
	m3[0] = vrow00; m3[1] = vrow10; m3[2] = vrow20; m3[3] = vrow30; m3[4] = vrow40;

	//-----------------------------------------------------------------------

	EXPECT_EQ(m3, m);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_vectors_equal_dimensions)
{
	//------------Инициализация матрицы1------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	int* v = new int[5] {1, 0, 0, 0, 0};
	TDynamicVector<int> v1(v, 5);
	delete[] v;

	int* res = new int[5] {0, 5, 10, 15, 20};
	TDynamicVector<int> result(res,5);
	delete[] res;

	TDynamicVector<int> res1(5);
	res1 = m * v1;

	EXPECT_EQ(result, res1);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_vectors_non_equal_dimensions)
{
	//------------Инициализация матрицы1------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	int* v = new int[4] {1, 0, 0, 0};
	TDynamicVector<int> v1(v, 4);
	delete[] v;

	ASSERT_ANY_THROW(m * v1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	//------------Инициализация матрицы1------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	TDynamicMatrix<int> m1(5);
	m1[0] = vrow1; m1[1] = vrow2; m1[2] = vrow3; m1[3] = vrow4; m1[4] = vrow0;

	/* Matrix m1:
	5 6 7 8 9
	10 11 12 13 14
	15 16 17 18 19
	20 21 22 23 24
	0 1 2 3 4			*/

	TDynamicMatrix<int> m2(5);
	m2 = m + m1;

	//------------Инициализация матрицы4 - результат операции ------------
	int* row00 = new int[5] {5, 7, 9, 11, 13};
	int* row10 = new int[5] {15, 17, 19, 21, 23};
	int* row20 = new int[5] {25, 27, 29, 31, 33};
	int* row30 = new int[5] {35, 37, 39, 41, 43};
	int* row40 = new int[5] {20, 22, 24, 26, 28};

	TDynamicVector<int> vrow00(row00, 5);
	TDynamicVector<int> vrow10(row10, 5);
	TDynamicVector<int> vrow20(row20, 5);
	TDynamicVector<int> vrow30(row30, 5);
	TDynamicVector<int> vrow40(row40, 5);

	delete[] row00; delete[] row10; delete[] row20; delete[] row30; delete[] row40;

	TDynamicMatrix<int> m3(5);
	m3[0] = vrow00; m3[1] = vrow10; m3[2] = vrow20; m3[3] = vrow30; m3[4] = vrow40;

	//-----------------------------------------------------------------------

	EXPECT_EQ(m3,m2);
	
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	//------------Инициализация матрицы1------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	//------------Инициализация матрицы2------------
	int* row00 = new int[4] {0, 1, 2, 3};
	int* row10 = new int[4] {5, 6, 7, 8};
	int* row20 = new int[4] {10, 11, 12, 14};
	int* row30 = new int[4] {15, 16, 17, 18};

	TDynamicVector<int> vrow00(row00, 4);
	TDynamicVector<int> vrow10(row10, 4);
	TDynamicVector<int> vrow20(row20, 4);
	TDynamicVector<int> vrow30(row30, 4);

	delete[] row00; delete[] row10; delete[] row20; delete[] row30;

	TDynamicMatrix<int> m1(4);
	m1[0] = vrow00; m1[1] = vrow10; m1[2] = vrow20; m1[3] = vrow30;
	//-----------------------------------------------

	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	//------------Инициализация матрицы1------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	TDynamicMatrix<int> m1(5);
	m1[0] = vrow1; m1[1] = vrow2; m1[2] = vrow3; m1[3] = vrow4; m1[4] = vrow0;

	/* 
	Matrix m1:
	5 6 7 8 9
	10 11 12 13 14
	15 16 17 18 19
	20 21 22 23 24
	0 1 2 3 4		
	*/

	TDynamicMatrix<int> m2(5);
	m2 = m - m1;

	//------------Инициализация матрицы4 - результат операции ------------
	int* row00 = new int[5] {-5, -5, -5, -5, -5};
	int* row10 = new int[5] {-5, -5, -5, -5, -5};
	int* row20 = new int[5] {-5, -5, -5, -5, -5};
	int* row30 = new int[5] {-5, -5, -5, -5, -5};
	int* row40 = new int[5] {20, 20, 20, 20, 20};

	TDynamicVector<int> vrow00(row00, 5);
	TDynamicVector<int> vrow10(row10, 5);
	TDynamicVector<int> vrow20(row20, 5);
	TDynamicVector<int> vrow30(row30, 5);
	TDynamicVector<int> vrow40(row40, 5);

	delete[] row00; delete[] row10; delete[] row20; delete[] row30; delete[] row40;

	TDynamicMatrix<int> m3(5);
	m3[0] = vrow00; m3[1] = vrow10; m3[2] = vrow20; m3[3] = vrow30; m3[4] = vrow40;
	//-----------------------------------------------------------------------

	EXPECT_EQ(m3, m2);
}

TEST(TDynamicMatrix, cant_subtract_matrices_with_not_equal_size)
{
	//------------Инициализация матрицы1------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	//------------Инициализация матрицы2------------
	int* row00 = new int[4] {0, 1, 2, 3};
	int* row10 = new int[4] {5, 6, 7, 8};
	int* row20 = new int[4] {10, 11, 12, 14};
	int* row30 = new int[4] {15, 16, 17, 18};

	TDynamicVector<int> vrow00(row00, 4);
	TDynamicVector<int> vrow10(row10, 4);
	TDynamicVector<int> vrow20(row20, 4);
	TDynamicVector<int> vrow30(row30, 4);

	delete[] row00; delete[] row10; delete[] row20; delete[] row30;

	TDynamicMatrix<int> m1(4);
	m1[0] = vrow00; m1[1] = vrow10; m1[2] = vrow20; m1[3] = vrow30;
	//-----------------------------------------------

	ASSERT_ANY_THROW(m - m1);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	//------------Инициализация матрицы1------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	//------------Инициализация матрицы2 - результата операции ------------
	int* row00 = new int[5] {150, 160, 170, 180, 190};
	int* row10 = new int[5] {400, 435, 470, 505, 540};
	int* row20 = new int[5] {650, 710, 770, 830, 890};
	int* row30 = new int[5] {900, 985, 1070, 1155, 1240};
	int* row40 = new int[5] {1150, 1260, 1370, 1480, 1590};

	TDynamicVector<int> vrow00(row00, 5);
	TDynamicVector<int> vrow10(row10, 5);
	TDynamicVector<int> vrow20(row20, 5);
	TDynamicVector<int> vrow30(row30, 5);
	TDynamicVector<int> vrow40(row40, 5);

	delete[] row00; delete[] row10; delete[] row20; delete[] row30; delete[] row40;

	TDynamicMatrix<int> m1(5);
	m1[0] = vrow00; m1[1] = vrow10; m1[2] = vrow20; m1[3] = vrow30; m1[4] = vrow40;
	//------------------------------------------------------------------------

	EXPECT_EQ(m1, (m * m));
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
	//------------Инициализация матрицы1------------
	int* row0 = new int[5] {0, 1, 2, 3, 4};
	int* row1 = new int[5] {5, 6, 7, 8, 9};
	int* row2 = new int[5] {10, 11, 12, 13, 14};
	int* row3 = new int[5] {15, 16, 17, 18, 19};
	int* row4 = new int[5] {20, 21, 22, 23, 24};

	TDynamicVector<int> vrow0(row0, 5);
	TDynamicVector<int> vrow1(row1, 5);
	TDynamicVector<int> vrow2(row2, 5);
	TDynamicVector<int> vrow3(row3, 5);
	TDynamicVector<int> vrow4(row4, 5);

	delete[] row0; delete[] row1; delete[] row2; delete[] row3; delete[] row4;

	TDynamicMatrix<int> m(5);
	m[0] = vrow0; m[1] = vrow1; m[2] = vrow2; m[3] = vrow3; m[4] = vrow4;

	//-----------------------------------------------

	//------------Инициализация матрицы2------------
	int* row00 = new int[4] {0, 1, 2, 3};
	int* row10 = new int[4] {5, 6, 7, 8};
	int* row20 = new int[4] {10, 11, 12, 14};
	int* row30 = new int[4] {15, 16, 17, 18};

	TDynamicVector<int> vrow00(row00, 4);
	TDynamicVector<int> vrow10(row10, 4);
	TDynamicVector<int> vrow20(row20, 4);
	TDynamicVector<int> vrow30(row30, 4);

	delete[] row00; delete[] row10; delete[] row20; delete[] row30;

	TDynamicMatrix<int> m1(4);
	m1[0] = vrow00; m1[1] = vrow10; m1[2] = vrow20; m1[3] = vrow30;
	//-----------------------------------------------

	ASSERT_ANY_THROW(m * m1);
}