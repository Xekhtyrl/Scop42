#include <iostream>
#include <vector>
#include <string>
// #include "linAlg.hpp"
// #include "Matrix.hpp"
#include "Includes/vml.hpp"
#include "my_glm.h"

using namespace std;
using namespace vml;

void strTrim(string& str, string arr = " ") {
	size_t start = str.find_first_not_of(arr);
	if (start > str.length()) {
		str = "";
		return;
	}
	size_t end = str.find_last_not_of(arr);
	str = str.substr(start, end - start + 1);	
}

template <typename T>
T add(T a, T b) {
	return a + b;
}

int main() {
	vec3 v1;
	mat4 rot = rotation(radians(50.), vec3({1.,1.,0.}));
	rot.print();
}