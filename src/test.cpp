// #include "s21_matrix_oop.h"

// int main() {
//   // S21Matrix a(3,3);
//   // S21Matrix b(a);
//   //  b = a;
//   // b.print_matrix();
//   // //c = a+b;
//   // b(0,0) = 1;
//   // try {
//   // b(-1,1) = 3;
//   // } catch (std::exception&ex) {
//   //     std::cout << ex.what();
//   // }
//   // b(2,2) = 9;
//   //  b.print_matrix();
//   //   S21Matrix a(2,3);
//   //   a.init_matrix();
//   //   S21Matrix b(2,3);
//   //   b.print_matrix();
//   //   a.print_matrix();
//   //   a.MulMatrix(b);
//   //   a.print_matrix();
//   // S21Matrix a;
//   // a(0, 0) = 1;
//   // a(0, 1) = 2;
//   // a(0, 2) = 3;
//   // a(1, 0) = 0;
//   // a(1, 1) = 4;
//   // a(1, 2) = 2;
//   // a(2, 0) = 5;
//   // a(2, 1) = 2;
//   // a(2, 2) = 1;

//   // S21Matrix b = a.CalcComplements();
//   // a.print_matrix();
//   // b.print_matrix();
//   // std::cout << a.Determinant() << " " << b.Determinant() << "\n";
//   // S21Matrix c = b.InverseMatrix();
//   // std::cout << "=============\n";
//   // c.print_matrix();
//   // S21Matrix a_(1, 4);
//   // S21Matrix d = a * c;
//   // d.print_matrix();
//   // a.setter_rows(6);
//   // std::cout << "=============\n";
//   // a.print_matrix();
//   // std::cout << "=============\n";
//   // a.setter_cols(10);
//   // a.print_matrix();

//   S21Matrix a(2, 2);
//   S21Matrix b;
//   a(0, 0) = 4;
//   a(0, 1) = 12;
//   a(1, 0) = 1;
//   a(1, 1) = 90;
//   b = (std::move(a));
//   a.print_matrix();
//   std::cout << "=====\n";
//   b.print_matrix();
// }