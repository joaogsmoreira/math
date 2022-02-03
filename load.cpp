#include "load.h"
#include "functions.h"
/*
bool load::IdxLoader::Plot(unsigned int id) {
    std::string file_name = "_id" + std::to_string(id) + "-" + std::to_string(Labels[id]) + ".png";
    unsigned error = lodepng::encode(file_name.c_str(), Images[id], image_width,
                                     image_height, LCT_GREY, 8U);
    if (error) {
        std::cout << "encoder error " << error << ": "
                  << lodepng_error_text(error) << std::endl;
        return false;
    }
    return true;
}
*/

bool load::IdxLoader::Label(std::string filename) {
  std::ifstream Input;
  Input.open(filename, std::fstream::binary);
  if (!Input.good()) {
    std::cout << "Cant open file: " << filename << std::endl;
    return false;
  }
  unsigned char data_type;
  unsigned char number_of_dimensions;

  // Get 3rd byte
  for (unsigned int i = 0; i < 3; i++) {
    data_type = Input.get();
  }
  // Check if it's 8 bit data type
  if (data_type != sizeof(uint8_t) * 8) {
    std::cout << "Not an unsigned byte type file: " << filename << std::endl;
    return false;
  }
  // Get 4th byte & checking if it's 1 dimension
  if ((number_of_dimensions = Input.get()) != 1) {
    std::cout << "File does not seem to be label file: " << filename << std::endl;
    return false;
  }
  unsigned int number_of_labels;
  Input.read(reinterpret_cast<char *>(&number_of_labels),
              sizeof(number_of_labels));
  number_of_labels = functions::Msb2Lsb(number_of_labels);

  std::cout << "Number of labels: " << number_of_labels << std::endl;
  Labels.resize(number_of_labels);

  // Getting labels
  for (size_t i = 0; i < number_of_labels; i++) {
    Labels[i] = Input.get();
  }

  Input.close();
  return true;
}

bool load::IdxLoader::Image(std::string filename) {
  std::ifstream Input;
  Input.open(filename, std::ifstream::binary);
  if (!Input.good()) {
    std::cout << "Cant open file: " << filename << std::endl;
    return false;
  }
  unsigned char data_type;
  unsigned char number_of_dimensions;
  // Get 3rd byte
  for (unsigned int i = 0; i < 3; i++) {
    data_type = Input.get();
  }
  // Check if it's 8 bit data type
  if (data_type != sizeof(uint8_t) * 8) {
    std::cout << "Not an unsigned byte type file: " << filename << std::endl;
    return false;
  }
  // Get 4th byte & checking if it's 3 dimension
  if ((number_of_dimensions = Input.get()) != 3) {
    std::cout << "File does not seem to be label file: " << filename << std::endl;
    return false;
  }
  // Size in dimension 0
  unsigned int number_of_images;
  Input.read(reinterpret_cast<char *>(&number_of_images),
              sizeof(number_of_images));
  number_of_images = functions::Msb2Lsb(number_of_images);
  // Size in dimension 1
  Input.read(reinterpret_cast<char *>(&image_height), sizeof(image_height));
  image_height = functions::Msb2Lsb(image_height);
  // Size in dimension 2
  Input.read(reinterpret_cast<char *>(&image_width), sizeof(image_width));
  image_width = functions::Msb2Lsb(image_width);

  std::cout << "Number of images: " << number_of_images << " H: " << image_height << " W: " << image_width
              << std::endl;

  Images.resize(number_of_images);
  std::vector<unsigned char> temp(image_height * image_width);

  for (size_t i = 0; i < number_of_images; i++) {
    Input.read((char *)&temp[0], image_height * image_width);
    Images[i] = temp;
  }

  Input.close();
  return true;
}