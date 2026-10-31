// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const size_t MAX_VECTOR_SIZE = 100000000;
const size_t MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
  
  static size_t check_sz_valid(size_t s) {
    if (s == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (s > MAX_VECTOR_SIZE)
      throw out_of_range("Too much vector size");
    return s;
  }
  
  void validate_matching_vectors(const TDynamicVector& other) const {
    if (other.sz != sz) throw invalid_argument("Vector dimension mismatch");
  }

public:
  TDynamicVector(size_t size = 1) : sz(check_sz_valid(size)), pMem(new T[sz]()) {}
  
  TDynamicVector(T* arr, size_t s) : sz(check_sz_valid(s)) {
    if (arr == nullptr)
      throw invalid_argument("TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    try {
      std::copy(arr, arr + sz, pMem);
    }
    catch (...) {
      delete[] pMem;
      throw;
    }
  }
  
  TDynamicVector(const TDynamicVector& other): sz(other.sz), pMem(new T[sz]) {
    try {
      for (size_t idx = 0; idx < sz; idx++)
        pMem[idx] = other.pMem[idx];
    }
    catch (...) {
      delete[] pMem;
      throw;
    }
  }
  
  TDynamicVector(TDynamicVector&& other) noexcept: sz(other.sz), pMem(other.pMem) {
    other.sz = 0;
    other.pMem = nullptr;
  }
  
  ~TDynamicVector() {
    delete[] pMem;
    pMem = nullptr;
    sz = 0;
  }
  
  TDynamicVector& operator=(const TDynamicVector& other) {
    if (this != &other) {
      TDynamicVector temp(other);
      swap(*this, temp);
    }
    return *this;
  }
  
  TDynamicVector& operator=(TDynamicVector&& other) noexcept {
    if (this == &other)
        return *this;
    delete[] pMem;
    pMem = nullptr; sz = 0;
    swap(*this, other);
    return *this;
  }

  size_t size() const noexcept { return sz; }

  T& operator[](size_t ind) {
    return at(ind);
  }
  const T& operator[](size_t ind) const {
    return at(ind);
  }
  
  T& at(size_t ind) {
    if (ind >= sz) throw out_of_range("Vector index out of range");
    return pMem[ind];
  }
  const T& at(size_t ind) const {
    if (ind >= sz) throw out_of_range("Vector index out of range");
    return pMem[ind];
  }

  bool operator==(const TDynamicVector& other) const noexcept {
    if (sz != other.sz) return false;
    for (size_t i = 0; i < sz; i++)
      if (pMem[i] != other.pMem[i]) return false;
    return true;
  }
  bool operator!=(const TDynamicVector& other) const noexcept {
    return !(*this == other);
  }

  TDynamicVector operator+(const T val) const {
    TDynamicVector res(*this);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] + val;
    return res;
  }
  
  TDynamicVector operator-(const T val) const {
    TDynamicVector res(*this);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] - val;
    return res;
  }
  
  TDynamicVector operator*(const T val) const {
    TDynamicVector res(*this);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] * val;
    return res;
  }

  TDynamicVector operator+(const TDynamicVector& other) const {
    validate_matching_vectors(other);
    TDynamicVector res(*this);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] + other.pMem[i];
    }
    return res;
  }
  
  TDynamicVector operator-(const TDynamicVector& other) const {
    validate_matching_vectors(other);
    TDynamicVector res(*this);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] - other.pMem[i];
    }
    return res;
  }
  
  T operator*(const TDynamicVector& other) const {
    validate_matching_vectors(other);
    T sum = T();
    for (size_t i = 0; i < sz; i++)
      sum = sum + (pMem[i] * other.pMem[i]);
    return sum;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  friend istream& operator>>(istream& istr, TDynamicVector& v) {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i];
    return istr;
  }
  
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) {
    ostr << "( ";
    for (size_t i = 0; i < v.sz; i++) {
      ostr << v.pMem[i] << " ";
    }
    ostr << ")";
    return ostr;
  }
};

template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
  
  static size_t check_matrix_sz(size_t s) {
    if (s == 0)
      throw out_of_range("Matrix size should be greater than zero");
    if (s > MAX_MATRIX_SIZE)
      throw out_of_range("Too much vector size");
    return s;
  }
  
  void validate_square_matrix() const {
    for (size_t i = 0; i < sz; i++)
      if (pMem[i].size() != sz) throw invalid_argument("Matrix size doesn't match");
  }
  
  void validate_matching_matrices(const TDynamicMatrix& other) const {
    validate_square_matrix(); 
    other.validate_square_matrix();
    if (sz != other.sz) throw invalid_argument("Matrices sizes differ");
  }

public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(check_matrix_sz(s)) {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;

  bool operator==(const TDynamicMatrix& other) const noexcept {
    return static_cast<const TDynamicVector<TDynamicVector<T>>&>(*this) == static_cast<const TDynamicVector<TDynamicVector<T>>&>(other);
  }
  bool operator!=(const TDynamicMatrix& other) const noexcept {
    return !(*this == other);
  }

  TDynamicMatrix operator+(const T& val) {
    validate_square_matrix();
    TDynamicMatrix resMatrix(*this);
    for (size_t i = 0; i < sz; i++)
      resMatrix.pMem[i] = pMem[i] + val;
    return resMatrix;
  }
  TDynamicMatrix operator-(const T& val) {
    validate_square_matrix();
    TDynamicMatrix resMatrix(*this);
    for (size_t i = 0; i < sz; i++)
      resMatrix.pMem[i] = pMem[i] - val;
    return resMatrix;
  }
  TDynamicMatrix operator*(const T& val) {
    validate_square_matrix();
    TDynamicMatrix resMatrix(*this);
    for (size_t i = 0; i < sz; i++)
      resMatrix.pMem[i] = pMem[i] * val;
    return resMatrix;
  }

  TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
    validate_square_matrix();
    if (sz == v.size()){
        TDynamicVector<T> resVector(sz);
        for (size_t i = 0; i < sz; i++) {
          resVector[i] = pMem[i] * v;
        }
        return resVector;
    }
    throw invalid_argument("Matrix and vector sizes differ");
  }

  TDynamicMatrix operator+(const TDynamicMatrix& other) {
    validate_matching_matrices(other);
    if (sz == other.sz){
        TDynamicMatrix resMatrix(sz);
        for (size_t i = 0; i < sz; i++) {
            resMatrix.pMem[i] = pMem[i] + other.pMem[i];
        }
        return resMatrix;
    }
    throw invalid_argument("Sizes of matrices differ");
  }
  
  TDynamicMatrix operator-(const TDynamicMatrix& other) {
    validate_matching_matrices(other);
    if (sz == other.sz){
        TDynamicMatrix resMatrix(sz);
        for (size_t i = 0; i < sz; i++) {
            resMatrix.pMem[i] = pMem[i] - other.pMem[i];
        }
        return resMatrix;
    }
    throw invalid_argument("Sizes of matrices differ");
  }

  TDynamicMatrix operator*(const TDynamicMatrix& other) {
    validate_matching_matrices(other);
    TDynamicMatrix resMatrix(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        T value = T();
        for (size_t k = 0; k < sz; k++) {
          value = value + (pMem[i][k] * other.pMem[k][j]);
        }
        resMatrix[i][j] = value;
      }
    }
    return resMatrix;
  }

  friend istream& operator>>(istream& istr, TDynamicMatrix& m) {
    for (size_t i = 0; i < m.sz; i++) {
      istr >> m.pMem[i];
    }
    return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m) {
    for (size_t i = 0; i < m.sz; i++) {
      ostr << m.pMem[i] << "\n";
    }
    return ostr;
  }
};

#endif