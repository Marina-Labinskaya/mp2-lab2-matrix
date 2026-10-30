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
  TDynamicVector<int> v(10);
  v[5] = 25;
  TDynamicVector<int> v1(v);
  ASSERT_EQ(true, v==v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(10);
  v[0] = 10;
  ASSERT_EQ(10, v[0]);
  TDynamicVector<int> v1(v);
  v1[0] = 11;
  ASSERT_EQ(11, v1[0]); ASSERT_EQ(10, v[0]);
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
  ASSERT_ANY_THROW(v[-3] = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(4);
  ASSERT_ANY_THROW(v[4] = 4);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(4);
  v[1]=7;
  v = v;
  EXPECT_EQ(7,v[1]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> a(3), b(3);
  b[1]=9;
  a = b;
  EXPECT_TRUE(a==b);
  b[1]=0;
  EXPECT_EQ(9,a[1]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> a(3), b(5);
  a = b;
  EXPECT_EQ(5,a.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> a(3), b(5);
  b[1]=9;
  a=b;
  EXPECT_TRUE(a==b);
  b[1]=0;
  EXPECT_EQ(9,a[1]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> a(3), b(3);
  a[1] = 9; b[1] = 9;
  EXPECT_TRUE(a==b);
  b[0]=1;
  EXPECT_TRUE(a!=b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> a(3);
  a[1] = 9;
  EXPECT_TRUE(a==a);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> a(3), b(4);
  EXPECT_FALSE(a==b);
  EXPECT_TRUE(a!=b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> a(3), b(3);
  a[0] = 9; a[2] = 24;
  b = a+1;
  EXPECT_EQ(9, a[0]); EXPECT_EQ(0, a[1]); EXPECT_EQ(24, a[2]);
  EXPECT_EQ(10, b[0]); EXPECT_EQ(1, b[1]); EXPECT_EQ(25, b[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> a(3), b(3);
  a[0] = 9; a[2] = 24;
  b = a-1;
  EXPECT_EQ(9, a[0]); EXPECT_EQ(0, a[1]); EXPECT_EQ(24, a[2]);
  EXPECT_EQ(8, b[0]); EXPECT_EQ(-1, b[1]); EXPECT_EQ(23, b[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> a(3), b(3);
  a[0] = 10; a[2] = 20;
  b = a*2;
  EXPECT_EQ(10, a[0]); EXPECT_EQ(0, a[1]); EXPECT_EQ(20, a[2]);
  EXPECT_EQ(20, b[0]); EXPECT_EQ(0, b[1]); EXPECT_EQ(40, b[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> a(3), b(3), p(3);
  a[0] = 10; a[2] = 20;
  b[1] = 5; b[2] = 10;
  p = a+b;
  EXPECT_EQ(10, a[0]); EXPECT_EQ(0, a[1]); EXPECT_EQ(20, a[2]);
  EXPECT_EQ(0, b[0]); EXPECT_EQ(5, b[1]); EXPECT_EQ(10, b[2]);
  EXPECT_EQ(10, p[0]); EXPECT_EQ(5, p[1]); EXPECT_EQ(30, p[2]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(3), b(4);
  EXPECT_ANY_THROW(a+b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> a(3), b(3), p(3);
  a[0] = 10; a[2] = 20;
  b[1] = 5; b[2] = 10;
  p = a-b;
  EXPECT_EQ(10, a[0]); EXPECT_EQ(0, a[1]); EXPECT_EQ(20, a[2]);
  EXPECT_EQ(0, b[0]); EXPECT_EQ(5, b[1]); EXPECT_EQ(10, b[2]);
  EXPECT_EQ(10, p[0]); EXPECT_EQ(-5, p[1]); EXPECT_EQ(10, p[2]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(3), b(4);
  EXPECT_ANY_THROW(a-b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> a(3), b(3);
  a[0] = 10; a[2] = 20;
  b[0] = 1; b[1] = 5; b[2] = 10;
  int p = a*b;
  EXPECT_EQ(10, a[0]); EXPECT_EQ(0, a[1]); EXPECT_EQ(20, a[2]);
  EXPECT_EQ(1, b[0]); EXPECT_EQ(5, b[1]); EXPECT_EQ(10, b[2]);
  EXPECT_EQ(210, p);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(3), b(4);
  EXPECT_ANY_THROW(a*b);
}

TEST(TDynamicVector, default_and_zero_size) {
  TDynamicVector<int> v;
  ASSERT_EQ(1, v.size());
  EXPECT_EQ(0, v[0]);
  EXPECT_ANY_THROW(TDynamicVector<int> z(0));
}

TEST(TDynamicVector, array_constructor_copies_data) {
  int data[] = {1, 2, 3};
  TDynamicVector<int> v(data, 3);
  data[0] = 25;
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
  v[1] = 45;
  EXPECT_EQ(2, data[1]);
}

TEST(TDynamicVector, array_constructor_rejects_invalid_arguments) {
  int data[] = {1};
  EXPECT_ANY_THROW(TDynamicVector<int>(nullptr, 1));
  EXPECT_ANY_THROW(TDynamicVector<int>(data, 0));
  EXPECT_ANY_THROW(TDynamicVector<int>(data, MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, move_constructor_transfers_storage) {
  TDynamicVector<int> v(2);
  v[0] = 7; v[1] = 9;
  int* old = &v[0];
  TDynamicVector<int> v1(std::move(v));
  ASSERT_EQ(2, v1.size());
  EXPECT_EQ(old, &v1[0]);
  EXPECT_EQ(7, v1[0]); EXPECT_EQ(9, v1[1]);
  EXPECT_EQ(0, v.size());
  v = TDynamicVector<int>(1);
  v[0] = 5;
  EXPECT_EQ(5, v[0]);
}

TEST(TDynamicVector, move_assignment_and_self_move) {
  TDynamicVector<int> v1(2), v2(4);
  v2[0] = 12;
  v1[0] = 7; v1[1] = 9;
  int* old = &v1[0];
  EXPECT_EQ(&v2, &(v2 = std::move(v1)));
  ASSERT_EQ(2, v2.size());
  EXPECT_EQ(old, &v2[0]);
  EXPECT_EQ(9, v2[1]);
  EXPECT_EQ(0, v1.size());
  v2 = std::move(v2);
  EXPECT_EQ(7, v2[0]); EXPECT_EQ(9, v2[1]);
}

TEST(TDynamicVector, at_and_const_at) {
  TDynamicVector<int> v(2);
  v.at(1) = 8;
  const TDynamicVector<int>& cv = v;
  EXPECT_EQ(8, cv.at(1)); EXPECT_EQ(8, cv[1]);
  EXPECT_ANY_THROW(v.at(2));
  EXPECT_ANY_THROW(cv.at(2));
  EXPECT_ANY_THROW(cv[2]);
}

TEST(TDynamicVector, scalar_compound_assignments) {
  int data[] = {1, -2, 3};
  TDynamicVector<int> v(data, 3);
  EXPECT_EQ(&v, &(v += 2));
  EXPECT_EQ(3, v[0]); EXPECT_EQ(0, v[1]); EXPECT_EQ(5, v[2]);
  EXPECT_EQ(&v, &(v -= 1));
  EXPECT_EQ(2, v[0]); EXPECT_EQ(-1, v[1]); EXPECT_EQ(4, v[2]);
  EXPECT_EQ(&v, &(v *= -2));
  EXPECT_EQ(-4, v[0]); EXPECT_EQ(2, v[1]); EXPECT_EQ(-8, v[2]);
}

TEST(TDynamicVector, vector_compound_assignments) {
  int x[] = {1, 2}, y[] = {3, 4};
  TDynamicVector<int> a(x, 2), b(y, 2);
  EXPECT_EQ(&a, &(a += b));
  EXPECT_EQ(4, a[0]); EXPECT_EQ(6, a[1]);
  EXPECT_EQ(3, b[0]); EXPECT_EQ(4, b[1]);
  EXPECT_EQ(&a, &(a -= b));
  EXPECT_EQ(1, a[0]); EXPECT_EQ(2, a[1]);
  EXPECT_EQ(3, b[0]); EXPECT_EQ(4, b[1]);
  a += a;
  EXPECT_EQ(2, a[0]); EXPECT_EQ(4, a[1]);
  a -= a;
  EXPECT_EQ(0, a[0]); EXPECT_EQ(0, a[1]);
}

TEST(TDynamicVector, compound_assignment_rejects_different_sizes) {
  TDynamicVector<int> a(2), b(3);
  a[0] = 7;
  const TDynamicVector<int> saved(a);
  EXPECT_ANY_THROW(a += b);
  EXPECT_EQ(a, saved);
  EXPECT_ANY_THROW(a -= b);
  EXPECT_EQ(a, saved);
}

TEST(TDynamicVector, swap_exchanges_sizes_and_storage) {
  TDynamicVector<int> a(2), b(3);
  a[0] = 7; b[0] = 9;
  int* sa = &a[0]; int* sb = &b[0];
  swap(a, b);
  ASSERT_EQ(3, a.size()); ASSERT_EQ(2, b.size());
  EXPECT_EQ(sb, &a[0]); EXPECT_EQ(sa, &b[0]);
  EXPECT_EQ(9, a[0]); EXPECT_EQ(7, b[0]);
}

TEST(TDynamicVector, input_and_output) {
  TDynamicVector<int> v(3);
  std::istringstream in("1 -2 3");
  EXPECT_EQ(&in, &(in >> v));
  EXPECT_FALSE(in.fail());
  EXPECT_EQ(1, v[0]); EXPECT_EQ(-2, v[1]); EXPECT_EQ(3, v[2]);
  std::ostringstream out;
  EXPECT_EQ(&out, &(out << v));
  EXPECT_EQ("( 1 -2 3 )", out.str());
  std::istringstream bad("1 wrong 3");
  bad >> v;
  EXPECT_TRUE(bad.fail());
}