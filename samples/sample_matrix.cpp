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
    setlocale(LC_ALL, "Russian");
    cout << "Тестирование класса работы с матрицами" << endl;

    try {
        size_t size;
        cout << "Введите размер квадратных матриц: ";
        cin >> size;

        TDynamicMatrix<int> a(size), b(size), c(size);

        cout << "\nВведите элементы первой матрицы (построчно):" << endl;
        cin >> a;

        cout << "\nВведите элементы второй матрицы (построчно):" << endl;
        cin >> b;

        cout << "\nМатрица A:" << endl << a;
        cout << "\nМатрица B:" << endl << b;

        c = a + b;
        cout << "\nСложение (A + B):" << endl << c;

        c = a - b;
        cout << "\nВычитание (A - B):" << endl << c;

        c = a * b;
        cout << "\nУмножение (A * B):" << endl << c;
    }
    catch (const exception& e) {
        cerr << "\nОшибка: " << e.what() << endl;
    }

    return 0;
}
//---------------------------------------------------------------------------