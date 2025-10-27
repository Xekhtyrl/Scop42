#ifndef CREATESHADER_HPP_
#define CREATESHADER_HPP_
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <string>
#include "./Includes/header.h"

// Class declaration
class CreateShader {
 public:
  CreateShader();
  CreateShader(int vecSize);
  CreateShader(const CreateShader &other);
  CreateShader(std::vector<float> colors);
  CreateShader &operator=(const CreateShader &rhs);
  std::string getContent();
  ~CreateShader();

 private:
  void VertexColShader(int vecSize);
  void VertexShader(int vecSize);
  void FragmentShader(std::vector<float> colors);
  std::vector<std::string> _content;
};

#endif // CREATESHADER_HPP_
