#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <math.h>
#include <vector>

namespace functions {
    template <typename T>
    inline T ReLU(T x) {
        return x > 0 ? x : 0;
    }

    template <typename T>
    inline T Sigmoid(T x) {
    return 1 / 1 + exp(-x);
    }

    inline float MSE(std::vector<float> actual, std::vector<float> predicted) {
        float sumSquareError = 0.0;
        for (uint i = 0; i < actual.size(); i++) {
            sumSquareError += powf(actual[i] - predicted[i], 2);
        }
        return (1.0 / actual.size() * sumSquareError);
    }

    inline unsigned int Msb2Lsb(const unsigned int a) {
        unsigned char *c = (unsigned char *)&a;
        unsigned int r = 0;
        for (int i = 0; i < 4; ++i) {
            r = r * 256 + c[i];
        }
        return r;
    }
}

#endif