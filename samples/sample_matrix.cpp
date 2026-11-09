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

	int n;
	cout << "Введите размерность матриц: ";
	cin >> n;

	TDynamicMatrix<int> a(n), b(n), c(n);

	cout << "Введите матрицу A (" << n << "x" << n << "):" << endl;
	cin >> a;

	cout << "Введите матрицу B (" << n << "x" << n << "):" << endl;
	cin >> b;

	cout << "\nMatrix A = \n" << a;
	cout << "\nMatrix B = \n" << b;

	c = a + b;
	cout << "\nMatrix C = A + B = \n" << c;

	c = a - b;
	cout << "\nMatrix C = A - B = \n" << c;

	c = a * b;
	cout << "\nMatrix C = A * B = \n" << c;

	return 0;
}
//---------------------------------------------------------------------------