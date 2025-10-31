#include "Matrix.hpp"

//---------------------------Constructors && Destructor---------------------------//

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
// Copy constructor
Matrix<T>::Matrix(const Matrix<T> &other) {
	_container = std::vector<std::vector<T>>(other._container);
	_rows = other._rows;
	_cols = other._cols;
	return;
}

template <typename T>
// Copy assignment overload
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &rhs) {
	_container = std::vector<std::vector<T>>(rhs._container);
	_rows = rhs._rows;
	_cols = rhs._cols;
	return *this;
}

template <typename T>
// Default destructor
Matrix<T>::~Matrix() { return; }

//--------------------------Static Constructors--------------------------//

template <typename T>
Matrix<T> Matrix<T>::translation(std::vector<T> vals) {
	if (vals.size() != 3)
		throw std::runtime_error("Vector must be of size 3.");
	Matrix<T> res(4,4, true);
	for (int i = 0; i < 3; i++){
		res[i][3] = vals[i];
	}
	return res;
}

template <typename T>
Matrix<T> Matrix<T>::rot(T rad, std::vector<T> axis) {
	if (axis.size() != 3)
		throw std::runtime_error("Error: axis vector should be of size 3");
	// Normalize axis just in case
	T len = std::sqrt(axis[0]*axis[0] + axis[1]*axis[1] + axis[2]*axis[2]);
	T x = axis[0] / len;
	T y = axis[1] / len;
	T z = axis[2] / len;

	T c = std::cos(rad);
	T s = std::sin(rad);
	T ic = 1.0 - c;

	Matrix<T> res({
		{ c + x*x*ic,		x*y*ic - z*s,	x*z*ic + y*s,	0. },
		{ y*x*ic + z*s,		c + y*y*ic,		y*z*ic - x*s,	0. },
		{ z*x*ic - y*s,		z*y*ic + x*s,	c + z*z*ic,		0. },
		{ 0., 				0., 			0., 			1. }
	});
	return res;
}

template <typename T>
Matrix<T> Matrix<T>::ortho(T left, T right, T bottom, T top, T near, T far) {
	Matrix <T> res({
		{2 / (right - left),	0,					0,					-(right + left) / (right - left)},
		{0,						2 / (top - bottom),	0,					-(top + bottom) / (top - bottom)},
		{0,						0,					-2 / (far - near),	-(far + near) / (far - near)	},
		{0,						0,					0,					1								}
	});
	return res;
}

template <typename T>
Matrix<T> Matrix<T>::perspective(T rad, T aspect, T near, T far) {
	T tR = tan(rad / 2);
	Matrix <T> res({
		{1 / (aspect * tR),	0,			0,								0								},
		{0,					1 / tR,		0,								0								},
		{0,					0,			-(far + near) / (far - near),	-2 * far * near / (far - near)	},
		{0,					0,			-1,								0								}
	});
	return res;
}

template <typename T>
Matrix<T> Matrix<T>::lookAt(std::vector<T> eye,std::vector<T> center,std::vector<T> rawUp) {
	std::vector<T> direction = normalize(LA<T>::sub(center, eye));
	std::vector<T> right = normalize(LA<T>::cross(direction, rawUp));
	std::vector<T> up = LA<T>::cross(right, direction);
	std::vector<T> perception = {-LA<T>::dot(right, eye), -LA<T>::dot(up, eye), LA<T>::dot(direction, eye)};

	Matrix<T> res({
		{right[0],		right[1],		right[2],		perception[0]	},
		{up[0],			up[1],			up[2],			perception[1]	},
		{direction[0],	direction[1],	direction[2],	perception[2]	},
		{0,				0,				0,				1				}
	});
	return res;
}

//--------------------------operations Overload Operators--------------------------//

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
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& oth) {
	if (_rows != oth._rows || _cols != oth._cols)
		throw std::runtime_error("Matrices of different Size");

	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			_container[i][j] = _container[i][j] - oth[i][j];
		}
	}
	return *this;
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
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& oth){
	if (_rows != oth._rows || _cols != oth._cols)
		throw std::runtime_error("Matrices of different Size");
	
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			_container[i][j] = _container[i][j] + oth[i][j];
		}
	}
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& oth) const{
	if (_cols != oth.rows())
		throw std::runtime_error("1Incompatible Matrices Sizes(" + std::to_string(_cols) +
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
Matrix<T> &Matrix<T>::operator*=(const Matrix<T>& oth){
	if (_cols != oth.rows())
		throw std::runtime_error("2Incompatible Matrices Sizes(" + std::to_string(_cols) +
			" (col) vs " + std::to_string(oth._rows) + " (rows))");
	
	unsigned int newRows = _rows;
	unsigned int newCols = oth.cols();
	std::vector<std::vector<T>> res(newRows, std::vector<T>(newCols, T{}));

	for (unsigned int i = 0; i < _rows; i++) {
		for (unsigned int j = 0; j < oth.cols(); j++) {
			for (unsigned int k = 0; k < _cols; k++){
				res[i][j] += _container[i][k] * oth[k][j];
			}
		}
	}
	_container = std::move(res);
	_rows = newRows;
	_cols = newCols;
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(std::vector<T> oth) const {
	if (_cols == oth.size() + 1){
		oth.push_back(1);
	}
	if (_cols != oth.size())
		throw std::runtime_error("3Incompatible Matrices Sizes(" + std::to_string(_cols)
			+ " (col) vs " + std::to_string(oth.size()) + " (rows))");

	Matrix<T> res(_rows, 1);

	for (int i = 0; i < _rows; i++)
		res[i][0] = linAlg<T>::dot(_container[i], oth);
	return res;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(std::vector<T> oth) {
	if (_cols == oth.size() + 1){
		oth.push_back(1);
	}
	if (_cols != oth.size())
		throw std::runtime_error("4Incompatible Matrices Sizes(" + std::to_string(_cols)
			+ " (col) vs " + std::to_string(oth.size()) + " (rows))");

	unsigned int newRows = _rows;
	unsigned int newCols = 1;
	std::vector<std::vector<T>> res(newRows, std::vector<T>(newCols, T{}));

	for (int i = 0; i < _rows; i++)
		res[i][0] = linAlg<T>::dot(_container[i], oth);

	_container = std::move(res);
	_rows = newRows;
	_cols = newCols;
	return *this;
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

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const T oth) {
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			_container[i][j] = _container[i][j] * oth;
		}
	}
	return *this;
}

template <typename T>
std::vector<T>& Matrix<T>::operator[](int row) {
	if (row >= _rows || row < 0)
		throw std::runtime_error("Index out of Range");
	return _container[row];
}

template <typename T>
const std::vector<T>& Matrix<T>::operator[](int row) const {
	if (row >= _rows || row < 0)
		throw std::runtime_error("Index out of Range");
	return _container[row];
}

//---------------------------Getters---------------------------//

template <typename T>
unsigned int Matrix<T>::rows() const {
	return _rows;
}

template <typename T>
unsigned int Matrix<T>::cols() const {
	return _cols;
}

template <typename T>
const float* Matrix<T>::toGLArray(bool columnMajor) const {
	if (_cols != 4 || _rows != 4)
		throw std::runtime_error("Must be a 4x4 Matrix.");
	static float flat[16];
	int idx = 0;

	if (columnMajor) {
		for (int c = 0; c < 4; ++c)
			for (int r = 0; r < 4; ++r)
				flat[c * 4 + r] = _container[r][c];
	} else {
		for (int r = 0; r < 4; ++r)
			for (int c = 0; c < 4; ++c)
				flat[r * 4 + c] = _container[r][c];
	}

	return flat;
}

//---------------------------Other---------------------------//
template <typename T>
Matrix<T>& Matrix<T>::scale(std::vector<T> val) {
	Matrix<T> m(4, 4, true); // start as identity
	for (int i = 0; i < val.size(); i++) {
		m[i][i] = val[i];
	}
	*this *= m;
	return *this;
}

//---------------------------Stream Operator Overload---------------------------//

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