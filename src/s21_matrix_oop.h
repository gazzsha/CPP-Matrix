#ifndef CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H_

#include <stdlib.h>

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_ = nullptr;

 public:
  S21Matrix();
  ~S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double& num);
  S21Matrix operator*(const S21Matrix& other) const;
  friend S21Matrix operator*(const double& num, const S21Matrix& other);
  friend S21Matrix operator*(const S21Matrix& other, const double& num);

  double& operator()(const int i, const int j);

  int get_rows() const noexcept;
  int get_cols() const noexcept;
  void setter_rows(const int& rows);
  void setter_cols(const int& cols);

  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  S21Matrix CalcComplements() const;
  S21Matrix Transpose();
  void MulMatrix(const S21Matrix& other);
  // helper function
  // void init_matrix() noexcept;
  void init_matrix(const int&) noexcept;
  // void print_matrix();
  void set_cols(int cols);
  S21Matrix get_new_matrix(int n, int m, int new_size) const;
  double matrix_determinant(S21Matrix& result) const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;
  friend void init_zero_matrix(double** matrix, const int& rows,
                               const int& cols);
};

#endif  // CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H_