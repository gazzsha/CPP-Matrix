#include "s21_matrix_oop.h" 

int main() { 
    S21Matrix a(3,3);
    S21Matrix b(a);
     b = a;
    b.print_matrix();
    //c = a+b;
    b(0,0) = 1;
    try {
    b(-1,1) = 3;
    } catch (std::exception&ex) { 
        std::cout << ex.what();
    }
    b(2,2) = 9;
  //  b.print_matrix();


   // c.print_matrix();
}