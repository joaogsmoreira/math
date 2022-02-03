#ifndef _MATH_H_
#define _MATH_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <math.h>
#include <vector>

#define EPSILON 1e-5

enum MatrixType{
  SINGLE_ROW,
  SINGLE_COLUMN
};

template <class T>
class Matrix {
public:
  Matrix(unsigned int rows, unsigned int cols, bool zero = false)
    : _rows(rows), _cols(cols) {
    data.reserve(_rows);
    for (unsigned int r = 0; r < _rows; r++) {
      data[r].reserve(_cols);
    }
    //Assign default values
    for(unsigned int r = 0; r < _rows; r++) {
      for(unsigned int c = 0; c < _cols; c++) {
        data[r][c] = 0;
      }
    }
  }

  //Its either single row or single column
  Matrix(const std::vector<unsigned char> &m, MatrixType type = SINGLE_ROW) {
    switch (type) {
      case SINGLE_ROW:
        _rows = 1;
        _cols = m.size();
        data.push_back(m);
        break;
      case SINGLE_COLUMN:
        _rows = m.size();
        _cols = 1;
        data.reserve(_rows);
        for (unsigned int i = 0; i < _rows; i++) {
          data[i].push_back(m[i]);
        }
        break;
    }
  }

  void Print(void);

  unsigned int _rows, _cols;
  std::vector<std::vector<unsigned char>> data;
};

template <class T>
void Matrix<T>::Print(void) {
  std::ofstream myfile;
  myfile.open("result.mine", std::ios_base::app);
  for (unsigned int r = 0; r < _rows; r++) {
    for (unsigned int c = 0; c < _cols; c++) {
      myfile.precision(6);
      myfile << std::fixed << "    " << (float) data[r][c];
    }
    myfile << std::endl;
  }
  myfile << std::endl;
  myfile.close();
}

template <class T>
Matrix<T> MatrixMultiplier(const Matrix<T> &a, const Matrix<T> &b) {
  if (a._cols != b._rows) {
    throw std::runtime_error("Math Error: Invalid size in matrix multiplication");
  }
  // The product of an m*n matrix and an n*k matrix is an m*k matrix
  Matrix<T> result(a._rows, b._cols, true);

  // Multiplying first and second matrices and storing it in result
  for (unsigned int row = 0; row < a._rows; row++) {
    for (unsigned int col = 0; col < b._cols; col++) {
      for (unsigned int k = 0; k < a._cols; k++) {
        result.data[row][col] += a.data[row][k] * b.data[k][col];
      }
    }
  }
  return result;
}

// Returns true if numbers are equal
bool compareFloatNumbers(float a, float b);

// Returns true if matrixes are equal
bool compareFloatMatrixes(Matrix<float> a, Matrix<float> b);

#endif