#ifndef _LOAD_H_
#define _LOAD_H_

#include <string>
#include <fstream>
#include <stdexcept>
#include "matrix.h"

template<class T>
Matrix<T> loadMatrixFromFile(std::string file_name) {
    std::ifstream file(file_name.c_str());
    if (!file.good()) {
        throw std::runtime_error("Bad file!");
    }
    int rows = 0, cols = 0;
    file >> rows;
    file >> cols;
    if( rows < 0 || rows > 1000){
        throw std::runtime_error("Invalid rows size!");
    }
    if (cols < 0 || cols > 1000){
        throw std::runtime_error("Invalid cols size!");
    }
    Matrix<float> m(rows, cols, true);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            float value = 0;
            file >> value;
            m._data[r][c] = value;
        }
    }
    return m;
}
#endif