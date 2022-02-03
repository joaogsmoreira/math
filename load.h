#ifndef _LOAD_H_
#define _LOAD_H_

#include "matrix.h"
#include <vector>

namespace load {

template<class T>
Matrix<T> MatrixFromFile(std::string file_name) {
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
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      float value = 0;
      file >> value;
      m.data[row][col] = value;
    }
  }
  return m;
}

class IdxLoader {
public:
  bool Label(std::string filename);
  bool Image(std::string filename);
  bool Plot(unsigned int a);
  std::vector<unsigned char> Labels;
  std::vector<std::vector<unsigned char>> Images;
  unsigned int image_height;
  unsigned int image_width;
};

}

#endif