#ifndef _MATH_H_
#define _MATH_H_

#include <stdio.h>
#include <iostream>
#include <memory>

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

    unsigned int _rows, _cols;
    T **_data;
};

template <class T>
void Matrix<T>::print(void) {
    for (unsigned int r = 0; r < _rows; r++) {
        for(unsigned int c = 0; c < _cols; c++) {
            printf("%d    ",(int) _data[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

template <class T>
Matrix<T> matrix_multiplier(const Matrix<T> &a, const Matrix<T> &b) {

    if (a._cols != b._rows) {
        std::cout << "Math Error: Invalid size in matrix multiplication" << std::endl;
        exit(0);
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

#endif