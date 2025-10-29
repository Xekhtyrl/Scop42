#include <iostream>
#include <vector>
#include <string>
#include "linAlg.hpp"
#include "Matrix.hpp"

using namespace std;

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

	cout << add(2, 5) << endl;
	vector<int> v1 = {1,2,3};
	vector<int> v2 = {4,5,6};
	cout << linAlg<int>::dot(v1,v2) <<std::endl;
	vector<float> v3 = {1.,2.,3.};
	vector<float> v4 = {4.5,5.,6.};
	cout << linAlg<float>::dot(v3,v4) <<std::endl;
	Matrix<float> m1(std::vector<std::vector<float>>({{13.,2.,3.},{1.,1.,1.},{0.,0.,0.}}));
	// Matrix<float> m2(std::vector<std::vector<float>>({{13.,2.,3.},{1.,1.,1.},{0.,0.,0.}}));
	vector<float> m2({1.,1.,1.});
	// Matrix<float> m1(3,4,2.);
	// cout<< m1.rows() << m1.cols()<<endl;
	cout << m1 * m2 << endl;
	LA<float>::dot(v3,v4);
}