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

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
  static size_t checked_size(size_t s) {
    if (s == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (s > MAX_VECTOR_SIZE)
      throw out_of_range("Too much vector size");
    return s;
  }
  void same_size(const TDynamicVector& v) const {
    if (v.sz != sz) throw invalid_argument("Vector dimension mismatch");
  }
public:
  TDynamicVector(size_t size = 1) : sz(checked_size(size)), pMem(new T[sz]()) {}
  TDynamicVector(T* arr, size_t s) : sz(checked_size(s)) {
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
  TDynamicVector(const TDynamicVector& v): sz(v.sz), pMem(new T[sz]) {
    try {
      for (size_t i = 0; i < sz; ++i)
        pMem[i] = v.pMem[i];
    }
    catch (...) {
      delete[] pMem;
      throw;
    }
  }
  TDynamicVector(TDynamicVector&& v) noexcept: sz(v.sz), pMem(v.pMem) {
    v.sz = 0;
    v.pMem = nullptr;
  }
  ~TDynamicVector() {
    delete[] pMem;
    pMem = nullptr;
    sz = 0;
  }
  TDynamicVector& operator=(const TDynamicVector& v) {
    if (this != &v) {
      TDynamicVector temp(v);
      swap(*this, temp);
    }
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept {
    if (this == &v)
        return *this;
    delete[] pMem;
    pMem = nullptr; sz = 0;
    swap(*this, v);
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind) {
    return at(ind);
  }
  const T& operator[](size_t ind) const {
    return at(ind);
  }
  // индексация с контролем
  T& at(size_t ind) {
    if (ind >= sz) throw out_of_range("Vector index out of range");
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (ind >= sz) throw out_of_range("Vector index out of range");
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept {
    if (sz != v.sz) return false;
    for (size_t i = 0; i < sz; ++i)
      if (pMem[i] != v.pMem[i]) return false;
    return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept {
    return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(const T val) const {
    TDynamicVector result(*this);
    for (size_t i = 0; i < sz; ++i)
      result.pMem[i] = pMem[i] + val;
    return result;
  }
  TDynamicVector& operator+=(const T val) {
    for (size_t i = 0; i < sz; ++i)
      pMem[i] = pMem[i] + val;
    return *this;
  }
  TDynamicVector operator-(const T val) const {
    TDynamicVector result(*this);
    for (size_t i = 0; i < sz; ++i)
      result.pMem[i] -= val;
    return result;
  }
  TDynamicVector& operator-=(const T val) {
    for (size_t i = 0; i < sz; ++i)
      pMem[i] -= val;
    return *this;
  }
  TDynamicVector operator*(const T val) const {
    TDynamicVector result(*this);
    for (size_t i = 0; i < sz; ++i)
      result.pMem[i] *= val;
    return result;
  }
  TDynamicVector& operator*=(const T val) {
    for (size_t i = 0; i < sz; ++i)
      pMem[i] *= val;
    return *this;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) const {
    same_size(v);
    TDynamicVector result(*this);
    for (size_t i = 0; i < sz; ++i) {
      result.pMem[i] = pMem[i] + v.pMem[i];
    }
    return result;
  }
  TDynamicVector& operator+=(const TDynamicVector& v) {
    same_size(v);
    for (size_t i = 0; i < sz; ++i) {
      pMem[i] = pMem[i] + v.pMem[i];
    }
    return *this;
  }
  TDynamicVector operator-(const TDynamicVector& v) const {
    same_size(v);
    TDynamicVector result(*this);
    for (size_t i = 0; i < sz; ++i) {
      result.pMem[i] = pMem[i] - v.pMem[i];
    }
    return result;
  }
  TDynamicVector& operator-=(const TDynamicVector& v) {
    same_size(v);
    for (size_t i = 0; i < sz; ++i) {
      pMem[i] = pMem[i] - v.pMem[i];
    }
    return *this;
  }
  T operator*(const TDynamicVector& v) const {
    same_size(v);
    T result = T();
    for (size_t i = 0; i < sz; ++i)
      result += pMem[i] * v.pMem[i];
    return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v) {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) {
    ostr << "( ";
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << " "; // требуется оператор<< для типа T
    ostr << ")";
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
  static size_t checked_matrix_size(size_t s) {
    if (s == 0)
      throw out_of_range("Matrix size should be greater than zero");
    if (s > MAX_MATRIX_SIZE)
      throw out_of_range("Too much vector size");
    return s;
  }
  void require_square() const {
    for (size_t i = 0; i < sz; ++i)
      if (pMem[i].size() != sz) throw invalid_argument("Matrix size doesn't match");
  }
  void require_same_size(const TDynamicMatrix& m) const {
    require_square(); m.require_square();
    if (sz != m.sz) throw invalid_argument("Matrices sizes differ");
  }
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(checked_matrix_size(s)) {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept {
    return static_cast<const TDynamicVector<TDynamicVector<T>>&>(*this) == static_cast<const TDynamicVector<TDynamicVector<T>>&>(m);
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept {
    return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator+(const T& val) {
    require_square();
    TDynamicMatrix result(*this);
    for (size_t i = 0; i < sz; ++i)
      result.pMem[i] = pMem[i] + val;
    return result;
  }
  TDynamicMatrix operator-(const T& val) {
    require_square();
    TDynamicMatrix result(*this);
    for (size_t i = 0; i < sz; ++i)
      result.pMem[i] = pMem[i] - val;
    return result;
  }
  TDynamicMatrix operator*(const T& val) {
    require_square();
    TDynamicMatrix result(*this);
    for (size_t i = 0; i < sz; ++i)
      result.pMem[i] = pMem[i] * val;
    return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
    require_square();
    if (sz == v.size()){
        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] * v;
        }
        return result;
    }
    throw invalid_argument("Matrix and vector sizes differ");
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) {
    require_same_size(m);
    if (sz == m.sz){
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; i++) {
            result.pMem[i] = pMem[i] + m.pMem[i];
        }
        return result;
    }
    throw invalid_argument("Sizes of matrices differ");
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m) {
    require_same_size(m);
    if (sz == m.sz){
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; i++) {
            result.pMem[i] = pMem[i] - m.pMem[i];
        }
        return result;
    }
    throw invalid_argument("Sizes of matrices differ");
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m) {
    require_same_size(m);
    TDynamicMatrix result(sz);
    TDynamicVector<T> temp(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t k = 0; k < sz; ++k) {
        for (size_t j = 0; j < sz; j++) {
          temp[j] = m.pMem[j][k];
        }
        result.pMem[i][k] = pMem[i] * temp;
      }
    }
    return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
    m.require_square();
    for (size_t i = 0; i < m.sz; ++i)
      istr >> m.pMem[i];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
  {
    m.require_square();
    for (size_t i = 0; i < m.sz; ++i)
      ostr << m.pMem[i] << "\n";
    return ostr;
  }
};

#endif
