#ifndef _MATH_H_
#define _MATH_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <math.h>

#define EPSILON 1e-5

template <class T>
class Matrix {
public:
    Matrix(unsigned int rows, unsigned int cols, bool zero = false)
        : _rows(rows), _cols(cols), _data(new T*[rows]) {  

        for (unsigned int r = 0; r < _rows; r++) {
            _data[r] = new T[_cols];
        }
        for(unsigned int r = 0; r < _rows; r++) {
            for(unsigned int c = 0; c < _cols; c++) {
                _data[r][c] = zero ? (T)0 : (T)r * c;
            }
        }
    }

    void print(void);

    /* Only needed if further restrictions are aplied
    T* access_slot(const unsigned int row, const unsigned int col) {
        return _data[row][col];
    } */

    unsigned int _rows, _cols;
    T **_data;
};

template <class T>
void Matrix<T>::print(void) {
    std::ofstream myfile;
    myfile.open("result.mine", std::ios_base::app);
    for (unsigned int r = 0; r < _rows; r++) {
        for (unsigned int c = 0; c < _cols; c++) {
            myfile.precision(6);
            myfile << std::fixed << "    " << (float) _data[r][c];
        }
        myfile << std::endl;
    }
    myfile << std::endl;
    myfile.close();
}

template <class T>
Matrix<T> matrixMultiplier(const Matrix<T> &a, const Matrix<T> &b) {

    if (a._cols != b._rows) {
        throw std::runtime_error("Math Error: Invalid size in matrix multiplication");
    }

    // The product of an m*n matrix and an n*k matrix is an m*k matrix
    Matrix<T> result(a._rows, b._cols, true);

    // Multiplying first and second matrices and storing it in result
    for (unsigned int row = 0; row < a._rows; row++) {
        for (unsigned int col = 0; col < b._cols; col++) {
            for (unsigned int k = 0; k < a._cols; k++) {
                result._data[row][col] += a._data[row][k] * b._data[k][col];
            }
        }
    }

    return result;
}

// Returns true if numbers are equal
bool compareFloatNumbers(float a, float b) {
    return fabs(a - b) < EPSILON;
}

// Returns true if matrixes are equal
bool compareFloatMatrixes(Matrix<float> a, Matrix<float> b) {
    if (a._rows != b._rows || a._cols != b._cols) {
        return false;
    }
    for (uint r = 0; r < a._rows; r++) {
        for (uint c = 0; c < a._cols; c++) {
            if (!compareFloatNumbers(a._data[r][c], b._data[r][c])) {
                return false;
            }
        }
    }
    return true;
}

#endif