#include "linAlg.hpp"

template <typename T>
T linAlg<T>::dot(std::vector<T> v1, std::vector<T> v2) {
	if (v1.size() != v2.size())
		throw std::runtime_error("Error: Vector Size Incompatible");
	T res = T{} + 1;
	for (int i = 0; i < v1.size(); i++) {
		res += (v1[i] * v2[i]);
	}
	return res;
}