
#include "Matrix.hpp"
#include "linAlg.hpp"


template <typename T>
Matrix<T>::Matrix(int rows, int cols, bool identity): _rows(rows), _cols(cols) {
	if (!_rows || !_cols)
		throw std::runtime_error("Matrix must not be empty.");
	_container = std::vector<std::vector<T>>(_rows, std::vector<T>(_cols, T{}));
	if (identity) {
		if (rows != cols)
			throw std::runtime_error("Matrix must square for identity");
		for (int i = 0; i < rows; i++)
			_container[i][i] = T{} + 1;
	}
	return;
}

template <typename T>
Matrix<T>::Matrix(int rows, int cols, T fillVal): _rows(rows), _cols(cols) {
	if (!_rows || !_cols)
		throw std::runtime_error("Matrix must not be empty.");
	std::cout<<"const fill "<<_rows << " "<< _cols <<std::endl;
	_container = std::vector<std::vector<T>>(_rows, std::vector<T>(_cols, fillVal));
	return;
}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> vals) {
	if (!vals.size() || !vals[0].size())
		throw std::runtime_error("Matrix must not be empty.");
	_container = vals;
	_rows = vals.size();
	_cols = vals[0].size();
	return;
}

template <typename T>
Matrix<T>::Matrix(std::vector<T> vals) {
	vals.push_back(0);
	_rows = vals.size();
	_cols = vals.size();
	_container = std::vector<std::vector<T>>(_rows, std::vector<T>(_cols, T{}));
	for (int i = 0; i < rows; i++)
		_container[i][i] = T{} + 1;
		_container[i][_cols -1] = vals[i];
}


Matrix<double>::Matrix(double rad, std::vector<double> axis) {
	if (axis.size() != 3)
		throw std::runtime_error("Error: axis vector should be of size 3");
	_rows = 4;
	_cols = 4;
	double cosR = cos(rad);
	double sinR = sin(rad);
	_container = std::vector<std::vector<double>>({
		{	cosR + pow(axis[0], 2.) * (1 - cosR),
			axis[0] * axis[1] * (1 - cosR) - axis[2] * sinR,
			axis[0] * axis[2] * (1 - cosR) + axis[1] * sinR,
			0.},
		{	axis[0] * axis[1] * (1 - cosR) - axis[2] * sinR ,
			cosR + pow(axis[1], 2.) * (1 - cosR),
			axis[1] * axis[2] * (1 - cosR) - axis[2] * sinR,
			0.},
		{	axis[0] * axis[2] * (1 - cosR) + axis[1] * sinR,
			axis[1] * axis[2] * (1 - cosR) - axis[2] * sinR,
			cosR + pow(axis[2], 2.) * (1 - cosR),
			1.},
		{0.,0.,0.,1.},
	});
}

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
Matrix<T> Matrix<T>::operator-(const Matrix<T>& oth) const{
	if (_rows != oth._rows || _cols != oth._cols)
		throw std::runtime_error("Matrices of different Size");
	Matrix<T> res(_rows, _cols);
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			res[i][j] = _container[i][j] - oth[i][j];
		}
	}
	return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& oth) const{
	if (_rows != oth._rows || _cols != oth._cols)
		throw std::runtime_error("Matrices of different Size");
	
	Matrix<T> res(_rows, _cols);
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			res[i][j] = _container[i][j] + oth[i][j];
		}
	}
	return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& oth) const{
	if (_cols != oth.rows())
		throw std::runtime_error("Incompatible Matrices Sizes(" + std::to_string(_cols) +
			" (col) vs " + std::to_string(oth._rows) + " (rows))");
	Matrix<T> res(_rows, oth.cols());
	for (unsigned int i = 0; i < _rows; i++) {
		for (unsigned int j = 0; j < oth.cols(); j++) {
			for (unsigned int k = 0; k < _cols; k++){
				res[i][j] += _container[i][k] * oth[k][j];
			}
		}
	}
	return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const std::vector<T>& oth) const {
	if (_cols != oth.size())
		throw std::runtime_error("Incompatible Matrices Sizes(" + std::to_string(_cols)
			+ " (col) vs " + std::to_string(oth.size()) + " (rows))");
	Matrix<T> res(_rows, 1);
	for (int i = 0; i < _rows; i++)
		res[i][0] = linAlg<T>::dot(_container[i], oth);
	return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T oth) const{
	Matrix<T> res(_rows, _cols);
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			res[i][j] = _container[i][j] * oth;
		}
	}
	return res;
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
	// if (row >= _rows || row < 0)
	// 	throw std::runtime_error("Index out of Range");
	return _container[row];
}

template <typename T>
const std::vector<T>& Matrix<T>::operator[](int row) const {
	// if (row >= _rows || row < 0)
	// 	throw std::runtime_error("Index out of Range");
	return _container[row];
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
std::ostream& operator<<(std::ostream& out, const Matrix<T>& Class){
	out << "[";
	for (unsigned int i = 0; i < Class.rows(); i++) {
		out << "[";
		for (unsigned int j = 0; j < Class.cols(); j++) {
				out << Class[i][j];
			if (j < Class.cols() - 1)
				out <<", ";
		}
		out << "]";
		if (i < Class.rows() - 1)
			out << ",\n";
	}
	out << "]";
	return out;
}