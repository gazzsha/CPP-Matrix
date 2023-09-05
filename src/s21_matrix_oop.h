#ifndef CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H_

#include <exception>
#include <iostream>


class S21Matrix { 
    private:
     int rows_,cols_;
     double **matrix_ = nullptr;
    public:
        S21Matrix();
        ~S21Matrix();
        S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix& other);

        S21Matrix operator+(const S21Matrix& other) const;
        S21Matrix operator-(const S21Matrix& other) const;
        bool operator==(const S21Matrix& other) const;
        S21Matrix& operator=(const S21Matrix& other);
        S21Matrix& operator+=(const S21Matrix& other);
        S21Matrix& operator-=(const S21Matrix& other);
        double& operator()(const int i,const int j);




        bool EqMatrix(const S21Matrix& other) const noexcept;
        void SumMatrix(const S21Matrix& other); 
        void SubMatrix(const S21Matrix& other); 
        void MulNumber(const double num) noexcept;
       // void MulMatrix(const S21Matrix& other);
        // helper function
        void init_matrix() noexcept; 
        void print_matrix(); 


};

#endif  // CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H_