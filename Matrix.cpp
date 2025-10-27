
#include "Matrix.hpp"

template <typename T>
// Default constructor
Matrix<T>::Matrix() { return; }

template <typename T>
// Copy constructor
Matrix<T>::Matrix(const Matrix<T> &other) {
  *this = other;
  return;
}

template <typename T>
// Copy assignment overload
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &rhs) {
  (void)rhs;
  return *this;
}

template <typename T>
// Default destructor
Matrix<T>::~Matrix() { return; }

template <typename T>
template <typename K>
Matrix<decltype(T{} - K {})> &Matrix<T>::operator-(const Matrix<K>& oth) const{
	if (_rows != oth._rows || _cols != oth._cols)
		throw std::runtime_error("Matrices of different Size");
	Matrix<decltype(T{} - K {})> res(_rows, _cols);
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			res[i][j] = _container[i][j] - oth[i][j];
		}
	}
	return res;
}

template <typename T>
template <typename K>
Matrix<decltype(T{} + K {})> &Matrix<T>::operator+(const Matrix<K>& oth) const{
	if (_rows != oth._rows || _cols != oth._cols)
		throw std::runtime_error("Matrices of different Size");
	
	Matrix<decltype(T{} + K {})> res(_rows, _cols);
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			res[i][j] = _container[i][j] + oth[i][j];
		}
	}
	return res;
}

template <typename T>
template <typename K>
Matrix<decltype(T{} * K {})> &Matrix<T>::operator*(const Matrix<K>& oth) const{
	if (_cols != oth.rows)
		throw std::runtime_error("Incompatible Matrices Sizes(" + std::to_string(_cols)
			+ " (col) vs ", + std::to_string(oth._rows) + " (rows))");
	Matrix<decltype(T{} * K {})> res(_rows, oth.cols);
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {

		}
	}
}

template <typename T>
template <typename K>
Matrix<decltype(T{} * K {})> &Matrix<T>::operator*(const std::vector<K>& oth) const {
	if (_cols != oth.size())
		throw std::runtime_error("Incompatible Matrices Sizes(" + std::to_string(_cols)
			+ " (col) vs ", + std::to_string(oth._size()) + " (rows))");
}

template <typename T>
template <typename K>
Matrix<decltype(T{} * K {})> &Matrix<T>::operator*(const K oth) const{
	Matrix<decltype(T{} * K {})> res(_rows, _cols);
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			res[i][j] = _container[i][j] * oth;
		}
	}
}

//useless?
// template <typename T>
// Matrix<T> &Matrix<T>::operator/(const Matrix<T>& oth) {

// }

// template <typename T>
// Matrix<T> &Matrix<T>::operator/(const std::vector<T>& oth) {

// }

template <typename T>
// == and != too?
std::vector<T>& Matrix<T>::operator[](int row) {
	if (row >= _rows || row < 0)
		throw std::runtime_error("Index out of Range")
}

template <typename T>
const std::vector<T>& Matrix<T>::operator[](int row) const {
	if (row >= _rows || row < 0)
		throw std::runtime_error("Index out of Range")
}

template <typename T>
unsigned int Matrix<T>::rows() const {
	return _rows;
}

template <typename T>
unsigned int Matrix<T>::cols() const {
	return _cols;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T> Class){
	out << "[";
	for (int i = 0; i < _rows; i++) {
		out << "[";
		for (int j = 0; j < _cols; j++) {
			out << Class[i][j];
			if (j != _cols - 1)
				out <<", ";
		}
		out << "]";
		if (i != _cols - 1)
			out << "\n";
	}
	out << "]";
}