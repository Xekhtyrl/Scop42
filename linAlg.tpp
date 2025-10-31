#include "linAlg.hpp"

template <typename T>
T linAlg<T>::dot(std::vector<T> v1, std::vector<T> v2) {
	if (v1.size() != v2.size())
		throw std::runtime_error("Error: Vector Size Incompatible");
	T res = T{};
	for (int i = 0; i < v1.size(); i++) {
		res += (v1[i] * v2[i]);
	}
	return res;
}

template <typename T>
std::vector<T> linAlg<T>::add(std::vector<T> v1, std::vector<T> v2) {
	if (v1.size() != v2.size())
		throw std::runtime_error("Error: Vector Size Incompatible");
	size_t len = v1.size();
	std::vector<T> res(len);
	for (size_t i = 0; i < len; i++)
		res[i] = v1[i] + v2[i];
	return res;
}

template <typename T>
std::vector<T>  linAlg<T>::sub(std::vector<T> v1, std::vector<T> v2) {
	if (v1.size() != v2.size())
		throw std::runtime_error("Error: Vector Size Incompatible");
	size_t len = v1.size();
	std::vector<T> res(len);
	for (size_t i = 0; i < len; i++)
		res[i] = v1[i] - v2[i];
	return res;
}

template <typename T>
std::vector<T>  linAlg<T>::mul(std::vector<T> v1, T val) {
	for (size_t i = 0; i <v1.size(); i++)
		v1[i] *= val;
	return val;
}

template <typename T>
std::vector<T>  linAlg<T>::div(std::vector<T> v1, T val) {
	if (val == 0)
		throw std::runtime_error("Error: Can not divide by 0.");
	for (size_t i = 0; i <v1.size(); i++)
		v1[i] /= val;
	return val;
}

template <typename T>
std::vector<T> linAlg<T>::cross(std::vector<T> v1, std::vector<T> v2) {
	if (v1.size() != v2.size() || v1.size() != 3)
		throw std::runtime_error("Error: Vector Size Incompatible");

	size_t len = v1.size();
	std::vector<T> res(len);
	res[0] = v1[1] * v2[2] - v1[2] * v2[1];
	res[1] = v1[2] * v2[0] - v1[0] * v2[2];
	res[2] = v1[0] * v2[1] - v1[1] * v2[0];
	return res;
}