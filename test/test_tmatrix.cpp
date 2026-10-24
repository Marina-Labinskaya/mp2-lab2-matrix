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

    TDynamicMatrix<int> copy(m);
    EXPECT_EQ(m, copy);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            EXPECT_EQ(m[i][j], copy[i][j]);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 10; m[1][1] = 30;

    TDynamicMatrix<int> copy(m);
    EXPECT_NE(&m[0][0], &copy[0][0]);
    EXPECT_NE(&m[1][0], &copy[1][0]);

    copy[0][0] = 20; copy[1][1] = 40;
    EXPECT_EQ(10, m[0][0]);
    EXPECT_EQ(30, m[1][1]);
    EXPECT_EQ(20, copy[0][0]);
    EXPECT_EQ(40, copy[1][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(4);
    EXPECT_EQ(static_cast<size_t>(4), m[0].size());
    for (size_t i = 0; i < 4; ++i)
        EXPECT_EQ(static_cast<size_t>(4), m[i].size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(2, m[0][1]);
    EXPECT_EQ(3, m[1][0]);
    EXPECT_EQ(4, m[1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(3);
    ASSERT_ANY_THROW(m[0].at(static_cast<size_t>(-1)) = 10);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(3);
    ASSERT_ANY_THROW(m[0].at(3) = 10);
    ASSERT_ANY_THROW(m[0].at(100) = 10);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    ASSERT_NO_THROW(m = m);
    ASSERT_EQ(static_cast<size_t>(2), m[0].size());
    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(2, m[0][1]);
    EXPECT_EQ(3, m[1][0]);
    EXPECT_EQ(4, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    ASSERT_NO_THROW(m2 = m1);
    EXPECT_EQ(m1, m2);
    EXPECT_EQ(1, m2[0][0]);
    EXPECT_EQ(2, m2[0][1]);
    EXPECT_EQ(3, m2[1][0]);
    EXPECT_EQ(4, m2[1][1]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(4), m2(2);
    ASSERT_NO_THROW(m2 = m1);
    ASSERT_EQ(static_cast<size_t>(4), m2[0].size());
    for (size_t i = 0; i < 4; ++i)
        EXPECT_EQ(static_cast<size_t>(4), m2[i].size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(3), m2(2);
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            m1[i][j] = static_cast<int>(i * 3 + j + 1);

    ASSERT_NO_THROW(m2 = m1);
    ASSERT_EQ(static_cast<size_t>(3), m2[0].size());
    EXPECT_EQ(m1, m2);
    for (size_t i = 0; i < 3; ++i)
    {
        ASSERT_EQ(static_cast<size_t>(3), m2[i].size());
        for (size_t j = 0; j < 3; ++j)
            EXPECT_EQ(m1[i][j], m2[i][j]);
    }
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 1; m1[0][1] = 2; m1[1][0] = 3; m1[1][1] = 4;
    m2[0][0] = 1; m2[0][1] = 2; m2[1][0] = 3; m2[1][1] = 4;
    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m2 == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(2), m2(3);
    EXPECT_FALSE(m1 == m2);
    EXPECT_FALSE(m2 == m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 1;  m1[0][1] = 2;  m1[1][0] = 3;  m1[1][1] = 4;
    m2[0][0] = 10; m2[0][1] = 20; m2[1][0] = 30; m2[1][1] = 40;

    TDynamicMatrix<int> result = m1 + m2;
    ASSERT_EQ(static_cast<size_t>(2), result[0].size());
    EXPECT_EQ(11, result[0][0]);
    EXPECT_EQ(22, result[0][1]);
    EXPECT_EQ(33, result[1][0]);
    EXPECT_EQ(44, result[1][1]);
    EXPECT_EQ(1, m1[0][0]);
    EXPECT_EQ(10, m2[0][0]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(3);
    ASSERT_ANY_THROW((void)(m1 + m2));
    ASSERT_ANY_THROW((void)(m2 + m1));
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 10; m1[0][1] = 20; m1[1][0] = 30; m1[1][1] = 40;
    m2[0][0] = 1;  m2[0][1] = 2;  m2[1][0] = 3;  m2[1][1] = 4;

    TDynamicMatrix<int> result = m1 - m2;
    ASSERT_EQ(static_cast<size_t>(2), result[0].size());
    EXPECT_EQ(9, result[0][0]);
    EXPECT_EQ(18, result[0][1]);
    EXPECT_EQ(27, result[1][0]);
    EXPECT_EQ(36, result[1][1]);
    EXPECT_EQ(10, m1[0][0]);
    EXPECT_EQ(1, m2[0][0]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(3);
    ASSERT_ANY_THROW((void)(m1 - m2));
    ASSERT_ANY_THROW((void)(m2 - m1));
}
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
