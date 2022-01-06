#ifndef _MATH_H_
#define _MATH_H_

#include <stdio.h>

template <class T>
class Matrix {
public:
    Matrix(unsigned int rows, unsigned int cols) {
        setRows(rows);
        setCols(cols);
        _data = new T*[rows];

        for (unsigned int r = 0; r < _rows; r++) {
            _data[r] = new T[cols];
        }
        for(unsigned int r = 0; r < _rows; r++) {
            for(unsigned int c = 0; c < cols; c++) {
                _data[r][c] = (T) r * c;
            }
        }
    }

    void print(void);
    
    void setRows(unsigned int r) {
        _rows = r;
    }
    void setCols(unsigned int c) {
        _cols = c;
    }

private:
    unsigned int _rows, _cols;
    T **_data;
};

template <class T>
void Matrix<T>::print(void) {
    for (unsigned int r = 0; r < _rows; r++) {
        for(unsigned int c = 0; c < _cols; c++) {
            printf("%.1f    ",(float) _data[r][c]);
        }
        printf("\n");
    }
}

#endif