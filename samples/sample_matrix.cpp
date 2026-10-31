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
  TDynamicMatrix<int> a(5), b(5), c(5);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами"
    << endl;
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      b[i][j] = (i * 10 + j) * 100;
    }
  c = a + b;
  cout << "Matrix a =\n" << a << endl;
  cout << "Matrix b =\n" << b << endl;
  cout << "Matrix c = a + b =\n" << c << endl;

  c = a - b;
  cout << "Matrix c = a - b =\n" << c << endl;

  TDynamicMatrix<int> d = a * 2;
  cout << "Matrix d = a * 2 =\n" << d << endl;

  TDynamicMatrix<int> e = a * b;
  cout << "Matrix e = a * b =\n" << e << endl;

  cout << "a == b ? " << (a == b ? "true" : "false") << endl;
  cout << "a == a ? " << (a == a ? "true" : "false") << endl;
  return 0;
 
  TDynamicMatrix<int> A(1), B(1);
  bool hasA = false, hasB = false;
  int choice;

  while (true)
  {
      cout << "\n=== TDynamicMatrix demo ===\n"
          << "1. Enter matrix A\n"
          << "2. Enter matrix B\n"
          << "3. Show A\n"
          << "4. Show B\n"
          << "5. A + B\n"
          << "6. A - B\n"
          << "7. A * B\n"
          << "8. A * scalar\n"
          << "9. Compare A and B\n"
          << "0. Exit\n"
          << "> ";
      cin >> choice;

      if (choice == 0) break;

      try
      {
          switch (choice)
          {
          case 1:
          case 2:
          {
              size_t n;
              cout << "Size: ";
              cin >> n;
              TDynamicMatrix<int> M(n);
              cout << "Enter " << n * n << " elements:\n";
              cin >> M;
              if (choice == 1) { A = M; hasA = true; }
              else { B = M; hasB = true; }
              break;
          }
          case 3:
              if (!hasA) { cout << "A is empty\n"; break; }
              cout << "A =\n" << A;
              break;
          case 4:
              if (!hasB) { cout << "B is empty\n"; break; }
              cout << "B =\n" << B;
              break;
          case 5:
              cout << "A + B =\n" << (A + B);
              break;
          case 6:
              cout << "A - B =\n" << (A - B);
              break;
          case 7:
              cout << "A * B =\n" << (A * B);
              break;
          case 8:
          {
              int s;
              cout << "Scalar: ";
              cin >> s;
              cout << "A * " << s << " =\n" << (A * s);
              break;
          }
          case 9:
              cout << (A == B ? "A == B\n" : "A != B\n");
              break;
          default:
              cout << "Unknown option\n";
          }
      }
      catch (const std::exception& e)
      {
          cout << "Error: " << e.what() << "\n";
      }
  }
  return 0;

}