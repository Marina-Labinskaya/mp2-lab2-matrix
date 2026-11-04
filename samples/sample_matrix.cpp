// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void printMenu()
{
  cout << "\n========== Меню ==========\n"
    << "1. Ввести матрицу A\n"
    << "2. Ввести матрицу B\n"
    << "3. Показать матрицы\n"
    << "4. A + B\n"
    << "5. A - B\n"
    << "6. A * B\n"
    << "7. Сравнить A и B\n"
    << "8. Умножить A на скаляр\n"
    << "0. Выход\n"
    << "Выберите пункт: ";
}

void inputMatrix(TDynamicMatrix<int>& m)
{
  size_t n;
  cout << "Введите размер матрицы: ";
  cin >> n;
  m = TDynamicMatrix<int>(n);
  cout << "Введите элементы матрицы (" << n << "x" << n << "):\n";
  cin >> m;
}

int main()
{
  setlocale(LC_ALL, "Russian");

  TDynamicMatrix<int> a(1), b(1), c(1);
  int choice = -1;
  int scalar = 0;

  cout << "Приложение для работы с матрицами\n";

  while (choice != 0)
  {
    printMenu();
    cin >> choice;

    try
    {
      switch (choice)
      {
      case 1:
        inputMatrix(a);
        break;
      case 2:
        inputMatrix(b);
        break;
      case 3:
        cout << "Матрица A:\n" << a << endl;
        cout << "Матрица B:\n" << b << endl;
        break;
      case 4:
        c = a + b;
        cout << "A + B =\n" << c << endl;
        break;
      case 5:
        c = a - b;
        cout << "A - B =\n" << c << endl;
        break;
      case 6:
        c = a * b;
        cout << "A * B =\n" << c << endl;
        break;
      case 7:
        if (a == b)
          cout << "Матрицы A и B равны\n";
        else
          cout << "Матрицы A и B не равны\n";
        break;
      case 8:
        cout << "Введите скаляр: ";
        cin >> scalar;
        c = a * scalar;
        cout << "A * " << scalar << " =\n" << c << endl;
        break;
      case 0:
        cout << "Выход\n";
        break;
      default:
        cout << "Неверный пункт меню\n";
        break;
      }
    }
    catch (const exception& e)
    {
      cout << "Ошибка: " << e.what() << endl;
    }
  }

  return 0;
}
//---------------------------------------------------------------------------
