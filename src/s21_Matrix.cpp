#include "s21_matrix_oop.h"



// function - try block 
S21Matrix::S21Matrix() : rows_(3),cols_(3) { 
    try {
        matrix_ = new double*[rows_]; 
        for (int i = 0; i < rows_; ++i) { 
            matrix_[i] = new double[cols_];
        }
        init_matrix();
    }   
    catch (const std::bad_alloc& e)
    {
        std::cout << "Allocation failed: " << e.what() << '\n';
    }
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
    try { 
        if (rows < 1 || cols < 1) { 
            throw std::invalid_argument("Invalid argument");
        }
        matrix_ = new double*[rows_]; 
        for ( int i = 0; i < rows; ++i) { 
            matrix_[i] = new double[cols_];
        }
        init_matrix(); 
    } catch (const std::invalid_argument& ex) { 
        std::cout << ex.what() << "\n";
    }  catch (const std::bad_alloc& e) { 
      std::cout << "Allocation failed: " << e.what() << '\n';
    }
}

void S21Matrix::init_matrix() noexcept { 
    for (int i = 0; i < rows_; i++) { 
        for (int j = 0; j < cols_; j++) { 
            matrix_[i][j] = 0;
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