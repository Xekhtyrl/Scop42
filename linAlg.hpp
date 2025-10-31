#pragma once

template<typename T>
class linAlg {
	public:
		static T 				dot(std::vector<T> v1, std::vector<T> v2);
		static std::vector<T>	add(std::vector<T> v1, std::vector<T> v2);
		static std::vector<T>	sub(std::vector<T> v1, std::vector<T> v2);
		static std::vector<T>	mul(std::vector<T> v1, T val);
		static std::vector<T>	div(std::vector<T> v1, T val);
		static std::vector<T>	cross(std::vector<T> v1, std::vector<T> v2);
};

template<typename T>
using LA = linAlg<T>;

#include "linAlg.tpp"