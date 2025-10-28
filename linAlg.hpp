#pragma once

template<typename T>
class linAlg {
	public:
		static T dot(std::vector<T> v1, std::vector<T> v2);
};

// template<typename T>
// using LA = linAlg<T>;

#include "linAlg.tpp"