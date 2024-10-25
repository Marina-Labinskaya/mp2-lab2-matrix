// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>
#include <vector>//для реализации CRS
using namespace std;

//объявление класса CRS заранее, чтобы сделать его дружественным, это понадобится для конструктора с параметром 
template<typename T>
class TDynamicMatrixCRS;

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
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE) throw out_of_range("Too much importance");
    pMem = new T[sz]();// {}; // У типа T д.б. конструктор по умолчанию
    if (pMem == nullptr) throw domain_error("domain_error");
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    if (pMem == nullptr) throw domain_error("domain_error");
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz=v.sz;
      pMem=new T[sz];
      if (pMem == nullptr) throw domain_error("domain_error");
      copy(v.pMem, v.pMem+v.sz,pMem);
      //for (size_t i = 0; i<sz; ++i) pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = 0;
      pMem = nullptr;
      swap(*this,v);
  }
  ~TDynamicVector()
  {
      delete [] pMem;
      pMem = nullptr;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (v != *this){
          if (sz!=v.sz){
              delete [] pMem;
              sz=v.sz;
              pMem = new T[sz];
              if (pMem==nullptr) throw bad_alloc();
          }
          //copy(v.pMem, v.pMem + v.sz, pMem);
          for (size_t i = 0; i < sz; ++i) pMem[i]=v.pMem[i];
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      sz = 0;
      delete[] pMem;
      pMem = nullptr;
      swap(*this,v);
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
      if (ind<0 || ind>=sz) throw range_error("range error");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind<0 || ind>=sz) throw range_error("range error");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz!=v.sz) return false;
        for (size_t i=0;i<sz;++i) if (pMem[i]!=v.pMem[i]) return false;
        return true;
    }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return (!(*this == v));
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector Result(*this);
      for (size_t i = 0; i<sz;i++) Result.pMem[i]+=val;
      return Result;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector Result(*this);
      for (size_t i = 0; i<sz;i++) Result.pMem[i]-=val;
      return Result;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector Result(*this);
      for (size_t i = 0; i<sz;i++) Result.pMem[i]*=val;
      return Result;
  }
    
  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz!=v.sz) throw length_error("length error");
      TDynamicVector Result(*this);
      for (size_t i=0;i<sz;++i) Result[i] = Result[i] + v.pMem[i];
      return Result;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz!=v.sz) throw length_error("length error");
      TDynamicVector Result(*this);
      for (size_t i=0;i<sz;++i) Result[i] = Result[i] - v.pMem[i];
      return Result;
  }
  T operator*(const TDynamicVector& v) 
  {
      if (sz!=v.sz) throw length_error("length error");
      T sum = T(); //конструктор по умолчанию
      for (size_t i=0;i<sz;++i) sum = sum + (pMem[i]*v.pMem[i]);
      return sum;
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
  //friend class TDynamicMatrixCRS<T>;
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T> > //матрица хранится по строкам
{
  using TDynamicVector<TDynamicVector<T> >::pMem;
  using TDynamicVector<TDynamicVector<T> >::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T> >(s)
  {
      if (sz > MAX_MATRIX_SIZE) throw out_of_range("Too much importance");
      if (sz == 0) throw out_of_range("Greater than zero");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz); 
  }

  using TDynamicVector<TDynamicVector<T> >::operator[];
  using TDynamicVector<TDynamicVector<T> >::at;
  size_t size() const noexcept { return sz; }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return 0; 
      else for (size_t i = 0; i < sz; ++i) if (pMem[i] != m.pMem[i]) return 0;
      return 1;
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !(*this==m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix Res(sz);
      for (size_t i = 0; i < sz; ++i) Res.pMem[i] = pMem[i] * val;
      return Res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (size() != v.size()) throw range_error("range_error");
        TDynamicVector<T> Res(sz);
        for (size_t i = 0; i < sz; ++i) {
            Res[i] = pMem[i]*v;
        }
        return Res;
    }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw range_error("range_error");
      TDynamicMatrix<T> Res(sz);
      for (size_t i = 0; i < sz; ++i) {
          Res.pMem[i] = pMem[i] + m.pMem[i];
      }
      return Res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw range_error("range_error");
      TDynamicMatrix<T> Res(sz);
      for (size_t i = 0; i < sz; ++i) {
          Res.pMem[i] = pMem[i] - m.pMem[i];
      }
      return Res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw range_error("range_error");
      TDynamicMatrix Res(sz);
      for (size_t i = 0; i < sz; ++i) {
          for (size_t k = 0; k < sz; ++k) {
              for (size_t j = 0; j < sz; ++j) {
                  Res.pMem[i][j] = Res.pMem[i][j] + (pMem[i][k] * m.pMem[k][j]);
              }
          }
      }
      return Res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
      for (size_t row = 0; row < m.sz; ++row) {
          istr >> m.pMem[row];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
  {
      for (size_t row = 0; row < m.sz; ++row) ostr << m.pMem[row] << endl;
      return ostr;
  }
  //для реализации CRS
  //friend class TDynamicMatrixCRS<T>;
};



//Разрежанная матрица в формате CRS
template<typename T>
class TDynamicMatrixCRS
{
    vector<T> value;//вектор значений
    vector<size_t> rowPtr;//вектор индексов строк
    vector<size_t>  col;//вектор индексов столбцов
    size_t sz;
public:
    TDynamicMatrixCRS():sz(0){}
    
    TDynamicMatrixCRS(const TDynamicMatrixCRS& m) {
        value = m.value;
        col = m.col;
        rowPtr = m.rowPtr;
        sz=m.sz;
    }
    TDynamicMatrixCRS(vector<T> _value, vector<size_t> _rowPtr, vector<size_t> _col):value(_value), rowPtr(_rowPtr), col(_col),sz(rowPtr.size() - 1) {}
    
    TDynamicMatrixCRS(const TDynamicMatrix<T>& m) {
        size_t temp = 0;
        for (size_t row = 0; row < m.size(); ++row) {
            rowPtr.push_back(temp);
            for (size_t column = 0; column < m.size(); ++column) {
                if (m[row][column] != T()) {
                    value.push_back(m[row][column]);
                    col.push_back(column);
                    temp++;
                }
            }
        }
        rowPtr.push_back(temp);
        sz=m.size();
    }
    
    
    TDynamicMatrixCRS operator*(const T& val)
    {
        TDynamicMatrixCRS Res(*this);
        for (size_t i = 0; i < value.size(); ++i) Res.value[i] = Res.value[i] * val;
        return Res;
    }
    
    
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
        TDynamicVector<T> Res(sz);
        if (v.size() != (sz)) throw logic_error("different length");
        for (size_t i = 0; i < sz; ++i) {
            for (size_t j = rowPtr[i]; j < rowPtr[i + 1]; ++j) Res[i] = Res[i] + (value[j] * v[col[j]]);
        }
        return Res;
    }
    
    //алгоритм взят с http://www.hpcc.unn.ru/file.php?id=486
    TDynamicMatrixCRS<T> transposition() const{
        TDynamicMatrixCRS<T> Res;
        size_t Col,RIndex,IIndex;
        T V;
        for(size_t i = 0; i<value.size();++i){
            Res.value.push_back(T());
            Res.col.push_back(T());
        }
        for(size_t i = 0; i<rowPtr.size();++i){
            Res.rowPtr.push_back(T());
        }
        for (size_t i = 0; i < col.size(); i++)
            Res.rowPtr[col[i] + 1]++;
        size_t S = 0;
        size_t tmp;
        for (size_t i = 1; i <= sz; i++)
        {
            tmp = Res.rowPtr[i];
            Res.rowPtr[i] = S;
            S = S + tmp;
        }
        
        for (size_t i = 0; i < sz; i++)
        {
            Col = i;
            for (size_t j = rowPtr[i]; j < rowPtr[i+1]; j++)
            {
                V = value[j];
                RIndex = col[j];
                IIndex = Res.rowPtr[RIndex + 1];
                Res.value[IIndex] = V;
                Res.col[IIndex] = Col;
                Res.rowPtr[RIndex + 1]++;
            }
        }
        Res.sz=sz;
        return Res;
    }
    
    TDynamicMatrixCRS<T> operator*(const TDynamicMatrixCRS<T>& m){
        TDynamicMatrixCRS<T> Res;
        TDynamicVector<T> temp1(sz);
        TDynamicVector<T> temp2(sz);
        size_t temp3 = 0;
        TDynamicMatrixCRS<T> m_T = m.transposition();
        
        for(size_t k = 0; k<sz;++k){
            Res.rowPtr.push_back(temp3);
            temp1=TDynamicVector<T>(sz);
            temp2=TDynamicVector<T>(sz);
            //взятие k-ой строки левой матрицы в вектор temp1
            for(size_t i = rowPtr[k];i<rowPtr[k+1];++i){
                temp1[col[i]]=value[i];
            }
            for (size_t u = 0; u<sz;++u){
                //взятие u-ой строки правой транспонированной матрицы(= u-ого столбца правой матрицы) в вектор temp2
                for(size_t p = m_T.rowPtr[u];p<m_T.rowPtr[u+1];++p){
                    temp2[m_T.col[p]]=m_T.value[p];
                }
                //Res[k][u]=(temp1*temp2);
                //формирование CRS матрицы умножением строки(temp1) левой матрицы на столбец(temp2) правой матрицы
                if ((temp1*temp2) != T()) {
                    Res.value.push_back((temp1*temp2));
                    Res.col.push_back(u);
                    temp3++;
                }
            }
        }
        Res.rowPtr.push_back(temp3);
        Res.sz=m.size();
        return Res;
    }

    /*TDynamicMatrix<T> operator*(const TDynamicMatrix<T>& m) {
        TDynamicMatrix<T> Res(sz);
        if (m.size() != (sz)) throw logic_error("different length");
        for (size_t i = 0; i < sz; ++i) {
            for (size_t j = rowPtr[i]; j < rowPtr[i + 1]; ++j) {
                for (size_t k = 0; k < sz; ++k) {
                    Res[i][k] = Res[i][k] + (value[j] * m[col[j]][k]);
                }
            }
        }
        return Res;
    }*/
        
    //преобразование типа
    operator TDynamicMatrix<T>() {
        TDynamicMatrix<T> Res(sz);
        for (size_t i = 0; i < sz; ++i) {
            for (size_t j = rowPtr[i]; j < rowPtr[i + 1]; ++j) {
                Res[i][col[j]] = value[j];
            }
        }
        return Res;
    }

    bool operator==(const TDynamicMatrixCRS& m) const{
        if (value != m.value || rowPtr != m.rowPtr || col!=m.col) return 0;
        return 1;
    }
    bool operator!=(const TDynamicMatrixCRS& m) const {
        return !(*this==m);
    }

    TDynamicMatrixCRS& operator=(const TDynamicMatrixCRS& m) {
        if (*this != m) {
            value.clear();
            rowPtr.clear();
            col.clear();
            value = m.value;
            rowPtr = m.rowPtr;
            col = m.col;
            sz=m.sz();
        }
        return *this;
    }

    TDynamicMatrixCRS& operator=(const TDynamicMatrix<T>& m) {
        *this = TDynamicMatrixCRS<T>(m);
        return *this;
    }
    
    size_t size() const { return sz; }
    
    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrixCRS<T>& m)
    {
        TDynamicMatrix<T> temp;
        istr >> temp;
        m = TDynamicMatrixCRS<T>(temp);
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrixCRS<T>& m)
    {
        ostr << "value: ";
        for (size_t i = 0; i < m.value.size(); ++i) ostr<<m.value[i]<<" ";
        ostr << endl<<"row pointer: ";
        for (size_t i = 0; i < m.rowPtr.size(); ++i) ostr << m.rowPtr[i]<<" ";
        ostr << endl<<"columns: ";
        for (size_t i = 0; i < m.col.size(); ++i) ostr << m.col[i]<<" ";
        ostr << endl;
        return ostr;
    }
    
};
#endif
