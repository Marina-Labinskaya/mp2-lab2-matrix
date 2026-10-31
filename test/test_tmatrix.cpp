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
    TDynamicMatrix<int> m(3);
    ASSERT_NO_THROW(TDynamicMatrix<int> copy(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 7;
    m[1][1] = 9;
    TDynamicMatrix<int> copy(m);
    EXPECT_TRUE(copy == m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 7;
    TDynamicMatrix<int> copy(m);
    copy[0][0] = 10;
    EXPECT_EQ(7, m[0][0]);
    EXPECT_EQ(10, copy[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(4);
    EXPECT_EQ(4u, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(2);
    m[1][0] = 15;
    EXPECT_EQ(15, m[1][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(2);
    EXPECT_ANY_THROW(m[-1][0] = 5);
    EXPECT_ANY_THROW(m[0][-1] = 5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(2);
    EXPECT_ANY_THROW(m[2][0] = 5);
    EXPECT_ANY_THROW(m[0][2] = 5);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(2);
    m[0][1] = 8;
    m = m;
    EXPECT_EQ(8, m[0][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> a(2), b(2);
    b[1][1] = 12;
    a = b;
    EXPECT_TRUE(a == b);
    b[1][1] = 3;
    EXPECT_EQ(12, a[1][1]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> a(2), b(3);
    b[2][2] = 11;
    a = b;
    EXPECT_EQ(3u, a.size());
    EXPECT_EQ(11, a[2][2]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> a(3), b(2);
    b[1][0] = 6;
    ASSERT_NO_THROW(a = b);
    EXPECT_EQ(2u, a.size());
    EXPECT_EQ(6, a[1][0]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> a(2), b(2);
    a[0][0] = 5;
    b[0][0] = 5;
    EXPECT_TRUE(a == b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> a(2);
    a[1][1] = 4;
    EXPECT_TRUE(a == a);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> a(2), b(3);
    EXPECT_FALSE(a == b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> a(2), b(2);
    a[0][0] = 2; a[0][1] = 3;
    b[0][0] = 4; b[0][1] = 5;
    TDynamicMatrix<int> result = a + b;
    EXPECT_EQ(6, result[0][0]);
    EXPECT_EQ(8, result[0][1]);
    EXPECT_EQ(0, result[1][0]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> a(2), b(3);
    EXPECT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> a(2), b(2);
    a[0][0] = 9; a[1][1] = 6;
    b[0][0] = 4; b[1][1] = 2;
    TDynamicMatrix<int> result = a - b;
    EXPECT_EQ(5, result[0][0]);
    EXPECT_EQ(4, result[1][1]);
    EXPECT_EQ(0, result[0][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> a(2), b(3);
    EXPECT_ANY_THROW(a - b);
}
