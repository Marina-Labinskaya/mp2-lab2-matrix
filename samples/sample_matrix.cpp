// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

int main()
{
  TDynamicMatrix<int> a(5), b(5), c(5), d(5);

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами" << endl;
  a.GenerateRandom(-10,10);
  b.GenerateRandom(-10,10);
  cout << "Matrix a" << endl << a << endl;
  cout << "Matrix b" << endl << b << endl;
  
  c = a + b;
  cout << "Matrix c = a + b" << endl << c << endl;
  c = a - b;
  cout << "Matrix c = a - b" << endl << c << endl;
  c = a * b;
  cout << "Matrix c = a * b" << endl << c << endl;
  return 0;
}
//---------------------------------------------------------------------------
