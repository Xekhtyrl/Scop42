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

template<typename T>
std::vector<T> normalize(std::vector<T> vec) {
	T norm = 0;
	size_t len = vec.size();
	for (size_t i = 0; i < len; i++) {
		norm += vec[i] * vec[i];
	}
	norm = sqrt(norm);
	if (norm == 0.0) 
		throw std::runtime_error("Cannot normalize a zero-length vector");
	for(T &x: vec) {
		x /= norm;
	}
	return vec;
};