// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

int main() {
  try {
    long long n;
    std::cout << "Matrix size (1.." << MAX_MATRIX_SIZE << "): ";
    if (!(std::cin >> n) || n <= 0 || n > MAX_MATRIX_SIZE) {
      std::cerr << "Invalid size\n"; return 1;
    }
    TDynamicMatrix<double> a((size_t)n), b((size_t)n), c((size_t)n);
    std::cout << "Enter A row by row (" << n*n << " numbers):\n";
    if (!(std::cin >> a)) { std::cerr << "Invalid A\n"; return 1; }
    std::cout << "Enter B row by row:\n";
    if (!(std::cin >> b)) { std::cerr << "Invalid B\n"; return 1; }

    for (;;) {
        std::cout << "1: A+B, 2: A-B, 3: A*B, 4: A*scalar, 5: A*vector, "
                     "6: compare, 7: copy A to B, 8: show, 0: exit\n";
        int op;
        if (!(std::cin >> op)) { std::cerr << "Invalid command\n"; return 1; }
        if (op==0) break;
        switch(op) {
          case 1: std::cout << a+b << endl; break;
          case 2: std::cout << a-b << endl; break;
          case 3: std::cout << a*b << endl; break;
          case 4: {
            double value; std::cout << "Scalar: ";
            if (!(std::cin>>value)) return 1;
            std::cout << a*value << endl; break;
          }
          case 5: {
            TDynamicVector<double> v(a.size()); std::cout << "Vector: ";
            if (!(std::cin>>v)) return 1;
            std::cout << a*v << '\n' << endl; break;
          }
          case 6: std::cout << (a==b ? "Equal\n" : "Different\n") << endl; break;
          case 7: b=a; std::cout << "Copied\n" << endl; break;
          case 8: std::cout << "A:\n" << a << "B:\n" << b << endl; break;
          default: std::cout << "Unknown command\n";
        }
      }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n'; return 1;
  }
  return 0;
}
//---------------------------------------------------------------------------
