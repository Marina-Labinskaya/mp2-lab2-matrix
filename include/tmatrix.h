// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

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
    if (sz == 0 || sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. конструктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
      : sz(v.sz)
  {
      
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = 0;
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[] pMem;
      pMem = nullptr;
      sz = 0;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v)
      {
          TDynamicVector tmp(v);
          swap(*this, tmp);
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
     
      swap(*this, v);
      return *this; // заглушка
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
      if (ind >= sz)
          throw std::out_of_range("fefefe");
      return pMem[ind];
     
  }
  const T& at(size_t ind) const
  {
      if ( ind >= sz)
          throw std::out_of_range("fefefe");
      return pMem[ind];
     
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz)
          return false;
      for (size_t i = 0; i < sz; ++i)
      {
          if (pMem[i] != v.pMem[i])
              return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector result(*this);
      for (size_t i = 0; i < sz; ++i)
          result.pMem[i] += val;
      return result;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector result(*this);
      for (size_t i = 0; i < sz; ++i)
          result.pMem[i] -= val;
      return result;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector result(*this);
      for (size_t i = 0; i < sz; i++)
          result.pMem[i] *= val;
      return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz == v.sz) {
          TDynamicVector result(*this);
          for (size_t i = 0; i < sz; ++i)
          result.pMem[i] += v.pMem[i];
          return result;
      }
      else throw std::out_of_range("fefefe");
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz == v.sz) {
          TDynamicVector result(*this);
          for (size_t i = 0; i < sz; ++i)
          result.pMem[i] -= v.pMem[i];
          return result;
      }
      else throw std::out_of_range("fefefe");
  }
  T operator*(const TDynamicVector& v) noexcept(false)
  {
      if (sz != v.sz) {
          throw std::invalid_argument("not same sizes");
      }
      T result = T{};
      for (size_t i = 0; i < sz; ++i) {
          result += pMem[i] * v.pMem[i];
      }
          return result;
   
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
      if (s > MAX_MATRIX_SIZE || s == 0) throw std::out_of_range("size nonono");

    for (size_t i = 0; i < s; ++i)
      pMem[i] = TDynamicVector<T>(s);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz)
          return false;
      for (size_t i = 0; i < sz; ++i)
      {
          if (pMem[i] != m.pMem[i])
              return false;
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; ++i)
      {
          result.pMem[i] = pMem[i] * val;
      }
      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (v.sz == sz) {
          TDynamicVector<T> result(sz);
          for (size_t i = 0; i < sz; ++i)
              result.pMem[i] = pMem[i] * v;
          return result;
      }
      else throw std::out_of_range("size nonono");
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw std::out_of_range("sizes different beee");
      }
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; ++i) {
          result.pMem[i] = pMem[i] + m.pMem[i];
      }

       return result;
      
      
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw std::out_of_range("sizes different beee");
      }
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; ++i)
      {
          result.pMem[i] = pMem[i] - m.pMem[i];
      }
      return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw std::out_of_range("sizes different beee");

      TDynamicMatrix result(sz);
      TDynamicVector<T> temp(sz);
      for (size_t i = 0; i < sz; ++i) {
          for (size_t j = 0; j < sz; ++j)
              temp[j] = m.pMem[j][i];
          for (size_t j = 0; j < sz; ++j)
              result.pMem[j][i] = pMem[j] * temp;
         
      }
      return result;

  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; ++i) {
          istr >> v.pMem[i];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; ++i) {
          ostr << v.pMem[i] << '\n';
      }
      return ostr;
  } 
 
};

#endif