#include "s21_matrix_oop.h"



// function - try block 
S21Matrix::S21Matrix() : rows_(3),cols_(3) { 
    try {
        matrix_ = new double*[rows_]; 
    } catch (...) { 
        delete[] matrix_;
        throw;
    }
    for (int i = 0; i < rows_; ++i) { 
        try {
         matrix_[i] = new double[cols_];
        } catch (...) { 
            for (int j = 0; j < i; j++) { 
                delete[] matrix_[j];
            }
            delete[] matrix_;
            throw;
        }
    }
        init_matrix();  
}


S21Matrix::~S21Matrix() { 
    if (matrix_) {
    for (int i = 0; i < rows_; ++i) { 
        delete[] matrix_[i];
    }
    delete[] matrix_;
    }
}

S21Matrix::S21Matrix(const S21Matrix& other): S21Matrix::S21Matrix(other.rows_,other.cols_) {
    for (int i = 0; i < rows_; i++) { 
        for (int j = 0; j < cols_; j++) { 
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) { 
        if (rows < 1 || cols < 1) { 
            throw std::invalid_argument("Invalid argument");
        }
        try {
            matrix_ = new double*[rows_]; 
        } catch (...) { 
            delete[] matrix_;
            throw;
        }
        for ( int i = 0; i < rows; ++i) { 
            try {
            matrix_[i] = new double[cols_];
            } catch (...) { 
                for (int j = 0; j < i; j++) { 
                    delete[] matrix_[j];
                }
                delete[] matrix_;
                throw;
            }
        }
        init_matrix(); 
    } 

void S21Matrix::init_matrix() noexcept { 
    for (int i = 0; i < rows_; i++) { 
        for (int j = 0; j < cols_; j++) { 
            matrix_[i][j] = rand() % (50 - -50 + 1) + (-50);
        }
    }
}

void S21Matrix::init_matrix(const int&x) noexcept { 
        for (int i = 0; i < rows_; i++) { 
        for (int j = 0; j < cols_; j++) { 
            matrix_[i][j] = x;
        }
    }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept { 
    if (cols_ != other.cols_ || rows_ != other.rows_) return false; 
    for (int i = 0; i < rows_; i++) { 
        for (int j = 0; j < cols_; j++) { 
            if (matrix_[i][j] != other.matrix_[i][j]) return false;
        }
    }
    return true; 
}

void S21Matrix::SumMatrix(const S21Matrix& other) { 
    if (rows_ != other.rows_ || cols_ != other.cols_) { 
        throw std::logic_error("Invalid size of Matrix");
    }
    for (int i = 0; i < rows_; i++) { 
        for (int j = 0; j < cols_; j++) { 
            matrix_[i][j]+=other.matrix_[i][j];
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other) { 
        if (rows_ != other.rows_ || cols_ != other.cols_) { 
        throw std::logic_error("Invalid size of Matrix");
    }
    for (int i = 0; i < rows_; i++) { 
        for (int j = 0; j < cols_; j++) { 
            matrix_[i][j]-=other.matrix_[i][j];
        }
    }
}

 void S21Matrix::MulNumber(const double num) noexcept { 
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
             matrix_[i][j]*=num;
        }
    }
 }


void S21Matrix::MulMatrix(const S21Matrix& other) { 
    if (cols_ != other.rows_)
        throw std::logic_error("The number of columns of the first matrix is not equal to the number of rows of the second matrix");
    S21Matrix temp(*this);
    set_cols(other.cols_);
    init_matrix(0);
    for (int i = 0; i < temp.rows_; i++) {
      for (int k = 0; k < other.cols_; k++) {
        for (int j = 0; j < temp.cols_; j++) {
          matrix_[i][k] += temp.matrix_[i][j] * other.matrix_[j][k];
        }
      }
    }
}

  S21Matrix S21Matrix::Transpose() { 
    S21Matrix result(cols_,rows_);
    for (int i = 0; i < rows_; i++) { 
        for (int j = 0; j < cols_; j++) { 
            result.matrix_[j][i] = matrix_[i][j];
        }
    }
    return result; 
  }

S21Matrix S21Matrix::CalcComplements() const { 
    if (rows_ != cols_) 
         throw std::logic_error("The matrix is not square");
    if (rows_ == 1) 
        throw std::logic_error("Invalid size of matrix");
    double sign = 1;
    S21Matrix result(rows_,cols_);
    for (int i = 0; i < rows_; i++) { 
        for (int j = 0; j < cols_; j++) { 
            S21Matrix intermediate_matrix = get_new_matrix(i,j,rows_ - 1);
             if (((i + j) % 2) == 0)
            sign = 1.0f;
            else
            sign = (-1.0f);
            double matrix_determinant_value = matrix_determinant(intermediate_matrix);
            result.matrix_[i][j]  = (matrix_determinant_value == 0.0f ? 1 : sign) * matrix_determinant_value;
        }
    }
    return result;
}

double S21Matrix::matrix_determinant(S21Matrix& result) const { 
    double return_value = 0;
    int sign = 1;
    int matrix_order = result.rows_;
    if (matrix_order == 1) {
        return result.matrix_[0][0];
    } else if (matrix_order == 2) { 
        return result.matrix_[0][0] * result.matrix_[1][1] - result.matrix_[0][1] * result.matrix_[1][0];
    } else { 
        for (int i = 0; i < result.cols_; i++) { 
            S21Matrix new_matrix = result.get_new_matrix(0,i,matrix_order - 1);
            return_value += sign * result.matrix_[0][i] * matrix_determinant(new_matrix);
            sign = -sign;
        }
    }
    return return_value;
}

double S21Matrix::Determinant() const { 
     if (rows_ != cols_) 
         throw std::logic_error("The matrix is not square");
         S21Matrix temp(*this);
    return matrix_determinant(temp);
}

S21Matrix S21Matrix::InverseMatrix() const { 
    if (rows_ == 1 && cols_ == 1) { 
        if (matrix_[0][0] == 0.0f) 
            throw std::logic_error("Div by zero");
        else { 
            S21Matrix result(rows_,cols_);
            result.matrix_[0][0] = 1.0f / matrix_[0][0];
        }
    }
    double determinant = 0;
    determinant = Determinant();
    if (fabs(determinant) < 1e-6) 
        throw std::logic_error("Div by zero");
    S21Matrix algebraic_additions = CalcComplements();
    S21Matrix algebraic_additions_transpoce = algebraic_additions.Transpose();
    algebraic_additions_transpoce.MulNumber(1.0f / determinant);
    return algebraic_additions_transpoce;
}

 S21Matrix S21Matrix::get_new_matrix(int n,int m, int new_size) const { 
    S21Matrix result(new_size,new_size);
    int h = 0, k = 0; // индексы новой матрицы
    for (int i = 0; i < rows_; i++) { 
        for (int j = 0; j < cols_; j++) { 
            if ( i!= n && j != m) { 
                result.matrix_[h][k++] = matrix_[i][j];
                if ( k == (cols_ - 1)) { 
                    h++;
                    k = 0;
                }
            }
        }
    }
    return result;
 }

 void S21Matrix::print_matrix() { 
    for (int i = 0; i < rows_; i++) { 
        for (int j = 0; j < cols_; j++) { 
            std::cout << matrix_[i][j] << " ";
        }
        std::cout << "\n";
    }
 }

 S21Matrix S21Matrix::operator+(const S21Matrix& other) const { 
    if (other.rows_ != rows_ || other.cols_ != cols_) { 
        throw std::logic_error("Invalid size");
    }
    S21Matrix result(*this);
    result.SumMatrix(other);
    return result;
 }

  S21Matrix S21Matrix::operator-(const S21Matrix& other) const { 
    if (other.rows_ != rows_ || other.cols_ != cols_) { 
        throw std::logic_error("Invalid size");
    }
    S21Matrix result(*this);
    result.SubMatrix(other);
    return result;
 }

bool S21Matrix::operator==(const S21Matrix& other) const { 
    return this->EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) { 
    try {
    for (int i = 0; i < rows_; i++) { 
            delete[] matrix_[i];
    }
    delete[] matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) { 
        matrix_[i] = new double[cols_];
    }

    for (int i = 0; i < rows_; i++) { 
        for (int j = 0; j < cols_; j++) { 
            matrix_[i][j] = other.matrix_[i][j];
        }
    } 
    } catch (const std::exception&ex) { 
        std::cout << ex.what();
    }
    return *this; 
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) { 
    this->SumMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) { 
    this->SubMatrix(other);
    return *this;
}

double& S21Matrix::operator()(const int i,const int j) { 
    if (i >= rows_ || j >= cols_ || i < 0 || j < 0) 
        throw std::out_of_range("Invalid input, index exceeds valid range");
    return matrix_[i][j];
}

void S21Matrix::set_cols(int cols) { 
    if (cols < 0 ) 
        throw std::logic_error("Invalid size");
    if (cols == cols_) return; 

    for (int i = 0; i < rows_; i++) { 
        delete[] matrix_[i];
    }

    for (int i = 0; i < rows_; i++) { 
        matrix_[i] = new double[cols];
    }

    cols_ = cols;
}


S21Matrix S21Matrix::operator*(const S21Matrix& other) const { 
    S21Matrix result(*this);
    result.MulMatrix(other);
    return result;
}

S21Matrix operator*(const double& num,const S21Matrix& other) { 
    S21Matrix result(other);
    result.MulNumber(num);
    return result;
}

S21Matrix operator*(const S21Matrix& other,const double& num) { 
    S21Matrix result(other);
    result.MulNumber(num);
    return result;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) noexcept { 
    this->MulMatrix(other);
    return *this;
}

 S21Matrix& S21Matrix::operator*=(const double& num) noexcept { 
    this->MulNumber(num);
    return *this;
 }

   int S21Matrix::get_rows() const noexcept{ 
    return rows_;
   }

    int S21Matrix::get_cols() const noexcept{ 
    return cols_;
   }

    void init_zero_matrix(double** matrix, const int& rows, const int& cols) { 
    for (int i = 0; i < rows; i ++) { 
        for ( int j = 0; j < cols; j++) { 
            matrix[i][j] = 0;
        }
    } 
   }

   void S21Matrix::setter_rows(const int& rows) {
        if (rows < 0) 
            throw std::invalid_argument("Invalid argument");
        if (rows == rows_) return; 
        double **tmp = new double*[rows];
        for (int i = 0; i < rows; i++) { 
            tmp[i] = new double[cols_];
        }
        init_zero_matrix(tmp,rows,cols_);
        for (int i = 0; i < std::min(rows,rows_); i++) { 
            for (int j = 0; j < cols_; j++) { 
                tmp[i][j] = matrix_[i][j];
            }
        }
        for (int i = 0; i < rows_; i++) { 
            delete[] matrix_[i];
         }
        delete[] matrix_;
        matrix_ = tmp;
        rows_ = rows;
   }

   void S21Matrix::setter_cols(const int& cols) {
        if (cols < 0) 
            throw std::invalid_argument("Invalid argument");
        if (cols == cols_) return;
        double **tmp = new double*[rows_];
        for (int i = 0; i < rows_; i++) { 
            tmp[i] = new double[cols];
        }
        init_zero_matrix(tmp,rows_,cols);
        for (int i = 0; i < rows_; i++) { 
            for (int j = 0; j < std::min(cols,cols_); j++) { 
                tmp[i][j] = matrix_[i][j];
            }
        }
        for (int i = 0; i < rows_; i++) { 
            delete[] matrix_[i];
         }
        delete[] matrix_;
        matrix_ = tmp;
        cols_ = cols;
   }
