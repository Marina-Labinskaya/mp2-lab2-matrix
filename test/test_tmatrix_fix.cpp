#include "tmatrix.h"

#include <gtest.h>

template <typename T>
class TestTMatrix : public ::testing::Test
{
protected:
    void SetUp()
    {
        m1 = new TDynamicMatrix<T>(5);
        m2 = new TDynamicMatrix<T>(5);
    }
    void TearDown()
    {
        delete m1;
        delete m2;
    }
    TDynamicMatrix<T>* m1;
    TDynamicMatrix<T>* m2;
    using param = T;
};
TYPED_TEST_CASE_P(TestTMatrix);



TYPED_TEST_P(TestTMatrix, compare_equal_matrix_return_true)
{
    EXPECT_TRUE((*m1) == (*m2));
}


TYPED_TEST_P(TestTMatrix, can_create_copied_matrix)
{
    ASSERT_NO_THROW(TDynamicMatrix<param> (((*m1))));
}

TYPED_TEST_P(TestTMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<param> m2((*m1));
    EXPECT_EQ((*m1), m2);
}

TYPED_TEST_P(TestTMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<param> v1(5), v2(v1);
    TDynamicMatrix<param>* pv1 = &v1;
    TDynamicMatrix<param>* pv2 = &v2;
    EXPECT_NE(pv1, pv2);
}
//
TYPED_TEST_P(TestTMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<param> v1(5);
    TDynamicMatrix<param> v2(6);
    EXPECT_NE(v1, v2);
}

TYPED_TEST_P(TestTMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<param> v_Res(5);
    v_Res[1][1] = (*m1)[1][1] = 6;
    v_Res[1][1] += (*m2)[1][1] = 10;
    v_Res[4][0] = (*m1)[4][0] = 50;
    v_Res[2][3] = (*m2)[2][3] = 18;


    EXPECT_EQ(v_Res, ((*m1) + (*m2)));
}

TYPED_TEST_P(TestTMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<param> v1(5);
    TDynamicMatrix<param> v2(6);
    ASSERT_ANY_THROW(v1 + v2);
}

TYPED_TEST_P(TestTMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<param> v_Res(5);
    v_Res[1][1] += (*m1)[1][1] = 6;
    v_Res[1][1] -= (*m2)[1][1] = 10;
    v_Res[4][0] += (*m1)[4][0] = 50;
    v_Res[2][3] -= (*m2)[2][3] = 18;
    EXPECT_EQ(v_Res, ((*m1) - (*m2)));
}

TYPED_TEST_P(TestTMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<param> v1(5);
    TDynamicMatrix<param> v2(6);
    ASSERT_ANY_THROW(v1 - v2);
}

TYPED_TEST_P(TestTMatrix, res_mult_matrix)
{
    TDynamicMatrix<param> v3(5);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ((*m1))[i][j] = ((*m2))[i][j] = i * 3 + (j + 1);
        }
    }
    v3[0][0] = 30;
    v3[0][1] = 36;
    v3[0][2] = 42;
    v3[1][0] = 66;
    v3[1][1] = 81;
    v3[1][2] = 96;
    v3[2][0] = 102;
    v3[2][1] = 126;
    v3[2][2] = 150;
    EXPECT_EQ(((*m1) * (*m2)), v3);
}






REGISTER_TYPED_TEST_CASE_P(TestTMatrix, compare_equal_matrix_return_true, can_create_copied_matrix, 
    copied_matrix_is_equal_to_source_one, copied_matrix_has_its_own_memory,
    res_mult_matrix, cant_subtract_matrixes_with_not_equal_size, can_subtract_matrices_with_equal_size,
    cant_add_matrices_with_not_equal_size, matrices_with_different_size_are_not_equal, can_add_matrices_with_equal_size);

typedef ::testing::Types<int, float, double, long long> MatrixTypes;
INSTANTIATE_TYPED_TEST_CASE_P(MatrixTypesInstantiation, TestTMatrix, MatrixTypes);





/*


TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> v(5);
  EXPECT_EQ(v.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> v(5);
    TDynamicVector<int> temp(5);
    temp[1]=5;
    v[1]=temp;
    
  EXPECT_EQ(v[1],temp);
}


TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> v(5);
  ASSERT_ANY_THROW(v.at(-1).at(0) = 5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> v(5);
  ASSERT_ANY_THROW(v.at(MAX_MATRIX_SIZE).at(0) = 5);
}


TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> v1(5);
    TDynamicMatrix<int> v2(5);
    v1[0][4]=v2[0][4]=6;
    v1[2][1]=v2[2][1]=16;
    v1=v1;
    EXPECT_EQ(v1,v2);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> v1(5);
  TDynamicMatrix<int> v2(5);
    v1[2][2]=10;
    v1[4][0]=24;
    v1=v2;
    EXPECT_EQ(v1, v2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> v1(5);
  TDynamicMatrix<int> v2(6);
  v1 = v2;
    EXPECT_EQ(v1.size(), v2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> v1(5);
    TDynamicMatrix<int> v2(7);
    v1[2][2]=10;
    v1[4][0]=24;
    v1=v2;
    EXPECT_EQ(v1, v2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> v1(5);
  TDynamicMatrix<int> v2(5);
  EXPECT_EQ(v1, v2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> v(5);
  EXPECT_EQ(v, v);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> v1(5);
  TDynamicMatrix<int> v2(6);
  EXPECT_NE(v1, v2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> v1(5);
  TDynamicMatrix<int> v2(5);
    TDynamicMatrix<int> v_Res(5);
    v_Res[1][1]=v1[1][1]=6;
    v_Res[1][1]+=v2[1][1]=10;
    v_Res[4][0]=v1[4][0]=50;
    v_Res[2][3]=v2[2][3]=18;
    
    
  EXPECT_EQ(v_Res,(v1+v2));
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> v1(5);
  TDynamicMatrix<int> v2(6);
  ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> v1(5);
    TDynamicMatrix<int> v2(5);
    TDynamicMatrix<int> v_Res(5);
    v_Res[1][1]+=v1[1][1]=6;
    v_Res[1][1]-=v2[1][1]=10;
    v_Res[4][0]+=v1[4][0]=50;
    v_Res[2][3]-=v2[2][3]=18;
    EXPECT_EQ(v_Res,(v1-v2));
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> v1(5);
  TDynamicMatrix<int> v2(6);
  ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicMatrix, res_mult_matrix)
{
  TDynamicMatrix<int> v1(3);
  TDynamicMatrix<int> v2(3);
  TDynamicMatrix<int> v3(3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      v1[i][j] = v2[i][j] = i * 3 + (j+1);
    }
  }
  // две матрицы
  // 1 2 3
  // 4 5 6
  // 7 8 9
  v3[0][0] = 30;
  v3[0][1] = 36;
  v3[0][2] = 42;
  v3[1][0] = 66;
  v3[1][1] = 81;
  v3[1][2] = 96;
  v3[2][0] = 102;
  v3[2][1] = 126;
  v3[2][2] = 150;
  EXPECT_EQ((v1*v2),v3);
}











//тесты для CRS

TEST(TDynamicMatrixCRS, can_create_copied_matrix)
{
  TDynamicMatrixCRS<int> m(5); //используется конструктор для TDynamicMatrix, проверка работы преобразования типа
  ASSERT_NO_THROW(TDynamicMatrixCRS<int> m1(m));
}

TEST(TDynamicMatrixCRS, is_equal_copied_matrix_CRS)
{
  TDynamicMatrixCRS<int> v1(5);
  TDynamicMatrixCRS<int> v2=v1;
  EXPECT_EQ(v1,v2);
}

TEST(TDynamicMatrixCRS, copied_matrix_has_its_own_memory)
{
  TDynamicMatrixCRS<int> v1(5), v2(v1);
  TDynamicMatrixCRS<int>* pv1 = &v1;
  TDynamicMatrixCRS<int>* pv2 = &v2;
  EXPECT_NE(pv1, pv2);
}

TEST(TDynamicMatrixCRS, can_get_size)
{
  TDynamicMatrixCRS<int> v(5);
  EXPECT_EQ(v.size(), 5);
}


TEST(TDynamicMatrixCRS, res_mult_matrix3)
{
    TDynamicMatrix<int> v1(3);
    TDynamicMatrix<int> v2(3);
    TDynamicMatrix<int> v3(3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            v1[i][j] = v2[i][j] = i * 3 + (j + 1);
        }
    }
    v3[0][0] = 30;
    v3[0][1] = 36;
    v3[0][2] = 42;
    v3[1][0] = 66;
    v3[1][1] = 81;
    v3[1][2] = 96;
    v3[2][0] = 102;
    v3[2][1] = 126;
    v3[2][2] = 150;
    TDynamicMatrixCRS<int> v1_CRS=v1;
    TDynamicMatrixCRS<int> v2_CRS=v2;
    EXPECT_EQ((TDynamicMatrix<int>)(v1_CRS * v2_CRS), (v1*v2));
}
    
 */   

