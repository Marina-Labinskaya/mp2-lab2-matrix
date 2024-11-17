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
        m_Res_ptr = new TDynamicMatrix<T>(5);
        m_Res = *m_Res_ptr;
    }
    void TearDown()
    {
        delete m1_ptr;
        delete m2_ptr;
    }
    void CreateMatrix(size_t n) {
        new TDynamicMatrix<T>(n);
    }
    void CreateMatrix(TDynamicMatrix<T> m_) {
        new TDynamicMatrix<T>(m_);
    }
    TDynamicMatrix<T>* m1_ptr;
    TDynamicMatrix<T>* m2_ptr;
    TDynamicMatrix<T> m1;
    TDynamicMatrix<T> m2;
    TDynamicMatrix<T>* m_Res_ptr;
    TDynamicMatrix<T> m_Res;
    using param = T;
};
TYPED_TEST_CASE_P(TestTMatrix);



TYPED_TEST_P(TestTMatrix, compare_equal_matrix_return_true)
{
    EXPECT_TRUE((this->m1) == (this->m2));
}


TYPED_TEST_P(TestTMatrix, can_create_copied_matrix)
{
   
    ASSERT_NO_THROW(CreateMatrix(this->m1));
}



TYPED_TEST_P(TestTMatrix, can_add_matrices_with_equal_size)
{
    m_Res[1][1] = (this->m1)[1][1] = 6;
    m_Res[1][1] += (this->m2)[1][1] = 10;
    m_Res[4][0] = (this->m1)[4][0] = 50;
    m_Res[2][3] = (this->m2)[2][3] = 18;


    EXPECT_EQ(m_Res, ((this->m1) + (this->m2)));
}


TYPED_TEST_P(TestTMatrix, can_subtract_matrices_with_equal_size)
{
   
    m_Res[1][1] += (this->m1)[1][1] = 6;
    m_Res[1][1] -= (this->m2)[1][1] = 10;
    m_Res[4][0] += (this->m1)[4][0] = 50;
    m_Res[2][3] -= (this->m2)[2][3] = 18;
    EXPECT_EQ(m_Res, ((this->m1) - (this->m2)));
}


TYPED_TEST_P(TestTMatrix, res_mult_matrix)
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ((this->m1))[i][j] = ((this->m2))[i][j] = i * 3 + (j + 1);
        }
    }
    m_Res[0][0] = 30;
    m_Res[0][1] = 36;
    m_Res[0][2] = 42;
    m_Res[1][0] = 66;
    m_Res[1][1] = 81;
    m_Res[1][2] = 96;
    m_Res[2][0] = 102;
    m_Res[2][1] = 126;
    m_Res[2][2] = 150;
    EXPECT_EQ(((this->m1) * (this->m2)), m_Res);
}






REGISTER_TYPED_TEST_CASE_P(TestTMatrix, compare_equal_matrix_return_true, can_create_copied_matrix, can_add_matrices_with_equal_size, can_subtract_matrices_with_equal_size, res_mult_matrix);

typedef ::testing::Types<int, float, double, long long> MatrixTypes;
INSTANTIATE_TYPED_TEST_CASE_P(MatrixTypesInstantiation, TestTMatrix, MatrixTypes);




