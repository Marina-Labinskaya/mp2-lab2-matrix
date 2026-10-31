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
    TDynamicMatrix<int> m(3);
    m.GenerateRandom();
    TDynamicMatrix<int> c(m);
    EXPECT_TRUE(c == m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(10);
    m.GenerateRandom();
    TDynamicMatrix<int> n(m);
    m.GenerateRandom();
    ASSERT_NE(m,n);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(4);

    EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(3);
    m[2][0] = 7;
    EXPECT_EQ(7, m[2][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(3);
    EXPECT_ANY_THROW(m[-2][0] = 7);
    EXPECT_ANY_THROW(m[2][-1] = 7);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(3);
    EXPECT_ANY_THROW(m[3][0] = 7);
    EXPECT_ANY_THROW(m[2][3] = 7);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(3);
    m[2][0] = 7;
    m = m;
    EXPECT_EQ(m[2][0], 7);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m(3), n(3);
    m[2][0] = 7;
    n = m;
    EXPECT_TRUE(n == m);
    n[2][0] = 10;
    EXPECT_EQ(m[2][0], 7);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m(2), n(3), k(4);
    m = n;
    EXPECT_EQ(3, m.size());
    k = m;
    EXPECT_EQ(3, k.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m(3), n(4);
    m[2][0] = 7;
    n = m;
    EXPECT_TRUE(n == m);
    n[2][0] = 10;
    EXPECT_EQ(m[2][0], 7);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m(3), n(3);
    EXPECT_TRUE(m == n); EXPECT_FALSE(m != n);
    n[0][0] = 1;
    EXPECT_TRUE(m != n); EXPECT_FALSE(m == n);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(3);
    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m(3), n(4);
    EXPECT_TRUE(m != n); EXPECT_FALSE(m == n);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(10), n(10), k(10);
    m.GenerateRandom();
    n.GenerateRandom();
    k = m + n;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) EXPECT_EQ(m[i][j] + n[i][j], k[i][j]);
    }
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(3), n(4);
    EXPECT_ANY_THROW(m + n);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(10), n(10), k(10);
    m.GenerateRandom();
    n.GenerateRandom();
    k = m - n;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) EXPECT_EQ(m[i][j] - n[i][j], k[i][j]);
    }
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m(3), n(4);
    EXPECT_ANY_THROW(m - n);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(2), n(2), k(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    n[0][0] = 5; n[0][1] = 6;
    n[1][0] = 7; n[1][1] = 8;
    k = m * n;
    EXPECT_EQ(k[0][0], 19); EXPECT_EQ(k[0][1], 22);
    EXPECT_EQ(k[1][0], 43); EXPECT_EQ(k[1][1], 50);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(3), m1(4);
    EXPECT_ANY_THROW(m * m1);
}

TEST(TDynamicMatrix, default_and_zero_size) {
    TDynamicMatrix<int> m;
    ASSERT_EQ(1, m.size());
    EXPECT_EQ(0, m[0][0]);
    EXPECT_ANY_THROW(TDynamicMatrix<int> z(0));
}

TEST(TDynamicMatrix, scalar_operations_do_not_change_source) {
    TDynamicMatrix<int> a(2);
    a[0][0] = 1; a[0][1] = -2;
    a[1][0] = 3; a[1][1] = 4;
    const TDynamicMatrix<int> saved(a);
    auto plus = a + 2, minus = a - 2, product = a * -3;
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j) {
            EXPECT_EQ(saved[i][j] + 2, plus[i][j]);
            EXPECT_EQ(saved[i][j] - 2, minus[i][j]);
            EXPECT_EQ(saved[i][j] * -3, product[i][j]);
        }
    EXPECT_EQ(a, saved);
}

TEST(TDynamicMatrix, multiplication_by_vector) {
    TDynamicMatrix<int> a(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;
    int data[] = { 5, 6 };
    TDynamicVector<int> v(data, 2);
    const TDynamicMatrix<int> saved(a);
    auto result = a * v;
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(17, result[0]); EXPECT_EQ(39, result[1]);
    EXPECT_TRUE(a == saved);
    EXPECT_EQ(5, v[0]); EXPECT_EQ(6, v[1]);
}

TEST(TDynamicMatrix, cant_multiply_by_vector_with_different_size) {
    TDynamicMatrix<int> a(2);
    TDynamicVector<int> wrong(3);
    EXPECT_ANY_THROW(a * wrong);
}

TEST(TDynamicMatrix, input_and_output) {
    TDynamicMatrix<int> m(2);
    std::istringstream in("1 2 3 4");
    EXPECT_EQ(&in, &(in >> m));
    EXPECT_FALSE(in.fail());
    EXPECT_EQ(1, m[0][0]); EXPECT_EQ(2, m[0][1]);
    EXPECT_EQ(3, m[1][0]); EXPECT_EQ(4, m[1][1]);
    std::ostringstream out;
    EXPECT_EQ(&out, &(out << m));
    EXPECT_EQ("( 1 2 )\n( 3 4 )\n", out.str());
    std::istringstream bad("1 2 wrong 4");
    bad >> m;
    EXPECT_TRUE(bad.fail());
}
TEST(TDynamicMatrix, randomizer) {
    TDynamicVector<int> v(100);
    EXPECT_NO_THROW(v.GenerateRandom());
}