#include "tmatrix.h"

#include <gtest.h>

const int sz = 4;

template <typename T> // можно использовать Typle, чтобы сделать 2 параметра, для сравнения в функции mult_matrix(abs(m1 - m2), < 1e-6), так как результат в Floating point классах может быть ошибочен
class TestTMatrix : public ::testing::Test
{
protected:
    void SetUp()
    {
        m1_ptr = new TDynamicMatrix<T>(sz);
        m2_ptr = new TDynamicMatrix<T>(sz);
        m1 = (*m1_ptr);
        m2 = (*m2_ptr);
        m_Res_ptr = new TDynamicMatrix<T>(sz);
        m_Res = *m_Res_ptr;
    }
    void TearDown() // деструктор вызывается неявно (вызываюстя деструкторы для матриц, а m1, m2 и m_Res указывают на тоже самое место в памяти)
    {
        delete m1_ptr;
        delete m2_ptr;
        delete m_Res_ptr;
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
    using par = T;
};
TYPED_TEST_CASE_P(TestTMatrix);


TYPED_TEST_P(TestTMatrix, compare_equal_matrix)
{
    EXPECT_TRUE((this->m1) == (this->m2));
}

TYPED_TEST_P(TestTMatrix, can_create_copied_matrix)
{
    ASSERT_NO_THROW(this->CreateMatrix(this->m1));
}

TYPED_TEST_P(TestTMatrix, can_add_matrices_with_equal_size)
{
    this->m1[1][1] = 61;
    this->m2[1][1] = 77;
    this->m1[3][0] = 5;
    this->m2[2][3] = 13;
    
    this->m_Res[3][0] = 5;
    this->m_Res[2][3] = 13;
    this->m_Res[1][1] = 138;

    EXPECT_EQ(this->m_Res, ((this->m1) + (this->m2)));
}

TYPED_TEST_P(TestTMatrix, can_subtract_matrices_with_equal_size)
{
    this->m1[1][1] = 5;
    this->m1[1][2] = -45;
    this->m1[2][1] = 63;
    this->m2[1][0] = 757;
    this->m1[1][0] = 123;
    this->m2[3][1] = 137;
    
    this->m_Res[1][1] = 5;
    this->m_Res[1][2] = -45;
    this->m_Res[2][1] = 63;
    this->m_Res[1][0] = -634;
    this->m_Res[3][1] = -137;
   
    EXPECT_EQ(this->m_Res, ((this->m1) - (this->m2)));
}

TYPED_TEST_P(TestTMatrix, mult_matrix)
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            this->m1[i][j] = 17 * 3 + (j - 56);
            this->m2[i][j] = 17 * 3 + (j - 56);
        }
    }
    this->m1[3][2] = -46;
    
    for (size_t i = 0; i < sz; i++)
        this->m_Res[i][3] = 0;
    for (size_t i = 0; i < sz - 1; i++) {
        this->m_Res[i][0] = 60;
        this->m_Res[i][1] = 48;
        this->m_Res[i][2] = 36;
    }
    this->m_Res[3][0] = 230;
    this->m_Res[3][1] = 184;
    this->m_Res[3][2] = 138;
    
    EXPECT_EQ(((this->m1) * (this->m2)), this->m_Res);
    //this->TearDown();
}



REGISTER_TYPED_TEST_CASE_P(TestTMatrix, compare_equal_matrix, can_create_copied_matrix, can_add_matrices_with_equal_size, can_subtract_matrices_with_equal_size, mult_matrix);

typedef ::testing::Types<int, long long, float, double> MatrixTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MatrixTypesInstantiation, TestTMatrix, MatrixTypes);


