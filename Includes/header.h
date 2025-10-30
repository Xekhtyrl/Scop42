#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <GL/glext.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "../CreateShader.hpp"
#include "../Shader.hpp"
#include "../Texture.hpp"
#include "../Matrix.hpp"
#include "../linAlg.hpp"

std::string floatToStr(float value);
void strTrim(std::string& str, std::string arr);
std::string fileToStr(std::string filePath);

template<typename T>
T radToDegree(T rad) {
	return rad * (180 / M_PI);
};

template<typename T>
T degreeToRad(T angle) {
	return angle * (M_PI / 180);
};