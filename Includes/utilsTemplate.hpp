#pragma once
#include "header.h"

template<typename T>
T radToDegree(T rad) {
	return rad * (180 / M_PI);
}

template<typename T>
T degreeToRad(T angle) {
	return angle * (M_PI / 180);
}

template<typename Container>
Container normalize(Container vec) {
	using T = typename Container::value_type;
	T norm = 0;
	size_t len = vec.size();
	for (size_t i = 0; i < len; i++) {
		norm += vec[i] * vec[i];
	}
	norm = sqrt(norm);
	if (norm == T(0)) 
		throw std::runtime_error("Cannot normalize a zero-length vector");
	for(T &x: vec) {
		x /= norm;
	}
	return vec;
}