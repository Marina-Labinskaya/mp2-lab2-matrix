#include "tmatrix.h"

#include <gtest.h>

template <typename T>
class TestTMatrix : public ::testing::Test
{
protected:
    void SetUp()
    {
        m1_ptr = new TDynamicMatrix<T>(5);
        m2_ptr = new TDynamicMatrix<T>(5);
        m1 = (*m1_ptr);
        m2 = (*m2_ptr);
    }
    void TearDown()
    {
        delete m1_ptr;
        delete m2_ptr;
    }
    TDynamicMatrix<T>* m1_ptr;
    TDynamicMatrix<T>* m2_ptr;
    TDynamicMatrix<T> m1;
    TDynamicMatrix<T> m2;
    using param = T;
};
TYPED_TEST_CASE_P(TestTMatrix);



TYPED_TEST_P(TestTMatrix, compare_equal_matrix_return_true)
{
    using param = typename TestTMatrix::param;
    EXPECT_TRUE((this->m1) == (this->m2));
}


TYPED_TEST_P(TestTMatrix, can_create_copied_matrix)
{
    using param = typename TestTMatrix::param;
    ASSERT_NO_THROW(TDynamicMatrix<param> (((this->m1))));
}

TYPED_TEST_P(TestTMatrix, copied_matrix_is_equal_to_source_one)
{
    using param = typename TestTMatrix::param;
    TDynamicMatrix<param> m2((this->m1));
    EXPECT_EQ((this->m1), m2);
}

TYPED_TEST_P(TestTMatrix, copied_matrix_has_its_own_memory)
{
    using param = typename TestTMatrix::param;
    TDynamicMatrix<param> v1(5), v2(v1);
    TDynamicMatrix<param>* pv1 = &v1;
    TDynamicMatrix<param>* pv2 = &v2;
    EXPECT_NE(pv1, pv2);
}
//
TYPED_TEST_P(TestTMatrix, matrices_with_different_size_are_not_equal)
{
    using param = typename TestTMatrix::param;
    TDynamicMatrix<param> v1(5);
    TDynamicMatrix<param> v2(6);
    EXPECT_NE(v1, v2);
}

TYPED_TEST_P(TestTMatrix, can_add_matrices_with_equal_size)
{
    using param = typename TestTMatrix::param;
    TDynamicMatrix<param> v_Res(5);
    v_Res[1][1] = (this->m1)[1][1] = 6;
    v_Res[1][1] += (this->m2)[1][1] = 10;
    v_Res[4][0] = (this->m1)[4][0] = 50;
    v_Res[2][3] = (this->m2)[2][3] = 18;


    EXPECT_EQ(v_Res, ((this->m1) + (this->m2)));
}

TYPED_TEST_P(TestTMatrix, cant_add_matrices_with_not_equal_size)
{
    using param = typename TestTMatrix::param;
    TDynamicMatrix<param> v1(5);
    TDynamicMatrix<param> v2(6);
    ASSERT_ANY_THROW(v1 + v2);
}

TYPED_TEST_P(TestTMatrix, can_subtract_matrices_with_equal_size)
{
    using param = typename TestTMatrix::param;
    TDynamicMatrix<param> v_Res(5);
    v_Res[1][1] += (this->m1)[1][1] = 6;
    v_Res[1][1] -= (this->m2)[1][1] = 10;
    v_Res[4][0] += (this->m1)[4][0] = 50;
    v_Res[2][3] -= (this->m2)[2][3] = 18;
    EXPECT_EQ(v_Res, ((this->m1) - (this->m2)));
}

TYPED_TEST_P(TestTMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    using param = typename TestTMatrix::param;
    TDynamicMatrix<param> v1(5);
    TDynamicMatrix<param> v2(6);
    ASSERT_ANY_THROW(v1 - v2);
}

TYPED_TEST_P(TestTMatrix, res_mult_matrix)
{
    using param = typename TestTMatrix::param;
    TDynamicMatrix<param> v3(5);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ((this->m1))[i][j] = ((this->m2))[i][j] = i * 3 + (j + 1);
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
    EXPECT_EQ(((this->m1) * (this->m2)), v3);
}






REGISTER_TYPED_TEST_CASE_P(TestTMatrix, compare_equal_matrix_return_true, can_create_copied_matrix, copied_matrix_is_equal_to_source_one, copied_matrix_has_its_own_memory, matrices_with_different_size_are_not_equal, can_add_matrices_with_equal_size, cant_add_matrices_with_not_equal_size, can_subtract_matrices_with_equal_size, cant_subtract_matrixes_with_not_equal_size, res_mult_matrix);

typedef ::testing::Types<int, float, double, long long> MatrixTypes;
INSTANTIATE_TYPED_TEST_CASE_P(MatrixTypesInstantiation, TestTMatrix, MatrixTypes);




