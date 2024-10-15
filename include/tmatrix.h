// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz <= 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size should be less than MAX_VECTOR_SIZE");
    pMem = new T[sz]();// {}; // У типа T д.б. конструктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
     pMem = new T[v.sz];
     if (pMem == nullptr) throw std::bad_alloc();
     else
     {
         sz = v.sz;
         std::copy(v.pMem, v.pMem + v.sz, pMem);
     }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[] pMem;
      pMem = nullptr;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (&v == this) return *this;
      if (sz != v.sz){
          T* p = new T[v.sz];
          delete[] pMem;
          pMem = p;
          sz = v.sz;
      }
      std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(*this, v);
      return (*this);
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind<0 || ind>sz - 1) throw std::out_of_range("Out of range");
      else return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind<0 || ind>sz - 1) throw std::out_of_range("Out of range");
      else return pMem[ind]
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      for (size_t i = 0; i < sz; i++) if (pMem[i] != v.pMem[i]) return 0;
      return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !((*this) == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      for (size_t i = 0; i < sz; i++) pMem[i] += val;
      return *this;
  }
  TDynamicVector operator-(T val)
  {
      for (size_t i = 0; i < sz; i++) pMem[i] -= val;
      return *this;
  }
  TDynamicVector operator*(T val)
  {
      for (size_t i = 0; i < sz; i++) pMem[i] *= val;
      return *this;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw logic_error("Wrong dimensions"); else {
          TDynamicVector<T> result(sz);
          for (size_t i = 0; i < sz; i++) result.pMem[i] = this->pMem[i] + v.pMem[i];
          return result;
      }
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw logic_error("Wrong dimensions"); else {
          TDynamicVector<T> result(sz);
          for (size_t i = 0; i < sz; i++) result.pMem[i] = this->pMem[i] - v.pMem[i];
          return result;
      }
  }
  T operator*(const TDynamicVector& v) 
  {
      if (sz != v.sz) throw logic_error("Wrong dimensions"); else {
          T result = (T)0;
          for (size_t i = 0; i < sz; i++) result += (*this)[i] * v[i];
          return result;
      }
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
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
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s > MAX_MATRIX_SIZE)
          throw out_of_range("Vector size should be less than MAX_MATRIX_SIZE");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  using TDynamicVector<TDynamicVector<T>>::at;

  using TDynamicVector<TDynamicVector<T>>::size;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator!=(m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; i++) result.pMem[i] = pMem[i] * val;
      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (pMem[0].sz != v.sz) throw logic_error("Wrong dimensions"); else {
          TDynamicVector<T> result(sz);
          for (size_t i = 0; i < sz; i++) result.pMem[i] += pMem[i] * v;
          return result;
      }
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (pMem[0].size() != m.pMem[0].size() || sz != m.sz) throw logic_error("Wrong dimensions"); else {
          TDynamicMatrix result(sz);
          for (size_t i = 0; i < sz; i++) result.pMem[i] = pMem[i] + m.pMem[i];
          return result;
      }
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (pMem[0].size() != m.pMem[0].size() || sz != m.sz) throw logic_error("Wrong dimensions"); else {
          TDynamicMatrix result(sz);
          for (size_t i = 0; i < sz; i++) result.pMem[i] = pMem[i] - m.pMem[i];
          return result;
      }
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (pMem[0].size() != m.pMem[0].size() || sz != m.sz) throw logic_error("Wrong dimensions"); else {
          TDynamicMatrix result(sz);
          TDynamicVector<T> tmp(pMem[0].sz);
          for (size_t i = 0; i < sz; i++) {
              for (size_t k = 0; k < pMem[0].sz; k++)
                  tmp[k] = m[k][i];
              for (size_t j = 0; j < pMem[0].sz; j++)
                  result[i][j] += pMem[i] * tmp;
          }
      }
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      size_t row, col;
      istr >> row >> col;
      if (v.sz != row && v.pMem[0].size() != col) throw logic_error("Wrong dimensions");
      for (size_t i = 0; i < row; i++)
          for (size_t j = 0; j < col; j++)
              isrt >> v.pMem[i][j];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      ostr << endl;
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << endl;
      return ostr;
  }
};

#endif
