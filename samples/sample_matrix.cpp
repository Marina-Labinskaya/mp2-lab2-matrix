#include <iostream>
#include <clocale>
#include "tmatrix.h"

using namespace std;

void inputMatrix(TDynamicMatrix<int>& matrix, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = i; j < size; ++j)
        {
            cout << "Element [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
}

int main()
{
    setlocale(LC_ALL, "");
    int size;
    cout << "Lab 2. Matrix operations\n";
    cout << "Enter matrix size (1-10): ";
    if (!(cin >> size) || size < 1 || size > 10)
    {
        cout << "Invalid size!\n";
        return 1;
    }

    TDynamicMatrix<int> a(size), b(size);
    cout << "\nEnter matrix A:\n";
    inputMatrix(a, size);
    cout << "\nEnter matrix B:\n";
    inputMatrix(b, size);
    if (!cin)
    {
        cout << "Input error!\n";
        return 1;
    }

    int choice;
    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Show matrices\n";
        cout << "2. Add matrices\n";
        cout << "3. Subtract matrices\n";
        cout << "4. Compare matrices\n";
        cout << "5. Copy matrix A\n";
        cout << "6. Enter matrices again\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        if (!(cin >> choice))
        {
            cout << "Invalid input!\n";
            return 1;
        }
        switch (choice)
        {
        case 1:
            cout << "\nMatrix A:\n" << a << endl;
            cout << "Matrix B:\n" << b << endl;
            break;
        case 2:
        {
            TDynamicMatrix<int> result = a + b;
            cout << "\nA + B:\n" << result << endl;
            break;
        }
        case 3:
        {
            TDynamicMatrix<int> result = a - b;
            cout << "\nA - B:\n" << result << endl;
            break;
        }
        case 4:
            cout << (a == b ? "Matrices are equal.\n" : "Matrices are not equal.\n");
            break;
        case 5:
        {
            TDynamicMatrix<int> copy(a);
            cout << "\nCopy of A:\n" << copy << endl;
            break;
        }
        case 6:
            cout << "\nEnter matrix A:\n";
            inputMatrix(a, size);
            cout << "\nEnter matrix B:\n";
            inputMatrix(b, size);
            if (!cin) return 1;
            break;
        case 0:
            cout << "Program finished.\n";
            break;
        default:
            cout << "Unknown operation!\n";
        }
    } while (choice != 0);

    return 0;
}
