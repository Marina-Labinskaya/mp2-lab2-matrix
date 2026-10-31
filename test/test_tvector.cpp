#include "tmatrix.h"
#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
    TDynamicVector<int> v(3);
    ASSERT_NO_THROW(TDynamicVector<int> copy(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    TDynamicVector<int> v(3);
    v[0] = 4;
    v[1] = 5;
    v[2] = 6;
    TDynamicVector<int> copy(v);
    EXPECT_TRUE(copy == v);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(2);
    v[0] = 7;
    TDynamicVector<int> copy(v);
    copy[0] = 10;
    EXPECT_EQ(7, v[0]);
    EXPECT_EQ(10, copy[0]);
}

TEST(TDynamicVector, can_get_size)
{
    TDynamicVector<int> v(4);
    EXPECT_EQ(4u, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
    TDynamicVector<int> v(4);
    v[0] = 9;
    EXPECT_EQ(9, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(3);
    EXPECT_ANY_THROW(v[-1] = 8);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(3);
    EXPECT_ANY_THROW(v[3] = 8);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(2);
    v[0] = 3;
    v = v;
    EXPECT_EQ(3, v[0]);
    EXPECT_EQ(2u, v.size());
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> a(2), b(2);
    b[0] = 11;
    a = b;
    EXPECT_TRUE(a == b);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> a(2), b(4);
    a = b;
    EXPECT_EQ(4u, a.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> a(2), b(3);
    b[2] = 15;
    a = b;
    EXPECT_EQ(15, a[2]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> a(2), b(2);
    a[0] = b[0] = 5;
    EXPECT_TRUE(a == b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> a(2);
    EXPECT_TRUE(a == a);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> a(2), b(3);
    EXPECT_TRUE(a != b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> a(2);
    a[0] = 2;
    a[1] = 3;
    TDynamicVector<int> result = a + 5;
    EXPECT_EQ(7, result[0]);
    EXPECT_EQ(8, result[1]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> a(2);
    a[0] = 8;
    a[1] = 5;
    TDynamicVector<int> result = a - 3;
    EXPECT_EQ(5, result[0]);
    EXPECT_EQ(2, result[1]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> a(2);
    a[0] = 3;
    a[1] = 4;
    TDynamicVector<int> result = a * 2;
    EXPECT_EQ(6, result[0]);
    EXPECT_EQ(8, result[1]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> a(2), b(2);
    a[0] = 1; a[1] = 2;
    b[0] = 3; b[1] = 4;
    TDynamicVector<int> result = a + b;
    EXPECT_EQ(4, result[0]);
    EXPECT_EQ(6, result[1]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> a(2), b(3);
    EXPECT_ANY_THROW(a + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> a(2), b(2);
    a[0] = 7; a[1] = 9;
    b[0] = 2; b[1] = 4;
    TDynamicVector<int> result = a - b;
    EXPECT_EQ(5, result[0]);
    EXPECT_EQ(5, result[1]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> a(2), b(3);
    EXPECT_ANY_THROW(a - b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> a(2), b(2);
    a[0] = 2; a[1] = 3;
    b[0] = 4; b[1] = 5;
    EXPECT_EQ(23, a * b);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> a(2), b(3);
    EXPECT_ANY_THROW(a * b);
}
