#include "matrix.h"

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
            if (!compareFloatNumbers(a.data[r][c], b.data[r][c])) {
                return false;
            }
        }
    }
    return true;
}