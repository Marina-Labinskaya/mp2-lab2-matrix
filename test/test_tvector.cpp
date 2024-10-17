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
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a,10);
	delete[] a;

	TDynamicVector<int> v1(v);

	EXPECT_EQ(v,v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	TDynamicVector<int> v1(v);
	TDynamicVector<int>* pv = &v;
	TDynamicVector<int>* pv1 = &v1;

	EXPECT_NE(pv, pv1);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(-1) = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(5) = 4);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	v = v;

	EXPECT_EQ(v, v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	int* b = new int[10] {1, 3, 4, 54, 98, 24, 342, 548, 45, 10};
	TDynamicVector<int> v1(b, 10);
	delete[] b;

	v = v1;

	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	int* b = new int[13] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0};
	TDynamicVector<int> v2(b,13);
	delete[] b;

	v = v2;
	EXPECT_EQ(v.size(),v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	int* b = new int[8] {4, 54, 98, 24, 342, 548, 45, 10};
	TDynamicVector<int> v1(b, 8);
	delete[] b;

	v1 = v;

	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	TDynamicVector<int> v1(a, 10);
	delete[] a;

	EXPECT_EQ(1, v==v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	EXPECT_EQ(1, v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	int* b = new int[8] {4, 54, 98, 24, 342, 548, 45, 10};
	TDynamicVector<int> v1(b, 8);
	delete[] b;

	EXPECT_EQ(0, v == v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	int* b = new int[10] {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	TDynamicVector<int> v1(b, 10);
	delete[] b;

	v = v + 1;

	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	int* b = new int[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	TDynamicVector<int> v1(b, 10);
	delete[] b;

	v = v - 1;

	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	int* b = new int[10] {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	TDynamicVector<int> v1(b, 10);
	delete[] b;

	v = v * 2;

	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	int* b = new int[10] {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	TDynamicVector<int> v1(b, 10);
	delete[] b;

	int* r = new int[10] {3, 6, 9, 12, 15, 18, 21, 24, 27, 30};
	TDynamicVector<int> vr(r, 10);
	delete[] r;

	TDynamicVector<int> v2(10);
	v2 = v + v1;

	EXPECT_EQ(vr, v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	int* b = new int[8] {6, 8, 10, 12, 14, 16, 18, 20};
	TDynamicVector<int> v1(b, 8);
	delete[] b;
	
	ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	int* b = new int[10] {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	TDynamicVector<int> v1(b, 10);
	delete[] b;

	int* r = new int[10] {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10};
	TDynamicVector<int> vr(r, 10);
	delete[] r;

	TDynamicVector<int> v2(10);
	v2 = v - v1;

	EXPECT_EQ(vr, v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	int* b = new int[8] {6, 8, 10, 12, 14, 16, 18, 20};
	TDynamicVector<int> v1(b, 8);
	delete[] b;

	ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int* a = new int[5] {1, 2, 3, 4, 5};
	TDynamicVector<int> v(a, 5);
	delete[] a;

	int* b = new int[5] {2, 4, 6, 8, 10};
	TDynamicVector<int> v1(b, 5);
	delete[] b;

	int res = 110;
	int res2 = v * v1;

	EXPECT_EQ(res, res2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;

	int* b = new int[8] {6, 8, 10, 12, 14, 16, 18, 20};
	TDynamicVector<int> v1(b, 8);
	delete[] b;

	ASSERT_ANY_THROW(v * v1);
}

