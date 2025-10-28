
#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <vector>
#include <iostream>
#include "linAlg.hpp"
#include <cmath>

// should I maTe a K var for diversity (i.e K T operation and not only T T)
template <typename T>

// Class declaration
class Matrix {
	public:
		/// @brief Constructs an empty or identity matrix.
		/// @param rows Number of rows.
		/// @param cols Number of columns.
		/// @param identity If true create an identity matrix.
		Matrix(int rows, int cols, bool identity = false);

		/// @brief Constructs a matrix filled with a value.
		/// @param rows Number of rows.
		/// @param cols Number of columns.
		/// @param fillVal Value used to fill every element.
		Matrix(int rows, int cols, T fillVal);

		/// @brief Constructs a matrix from a nested vector.
		/// @param val 2D vector containing matrix values (row-major).
		Matrix(std::vector<std::vector<T>> val);

		/// @brief Create an identity matrix with a translation vector (3 elements).
		/// @param vec A size-3 vector containing translation components.
		Matrix(std::vector<T> vec);

		/// @brief Rotation matrix of 'rad' radians around the axis 'axis'.
		/// @param rad Angle in radians.
		/// @param axis A size-3 axis vector (should be normalized).
		Matrix(double rad, std::vector<double> axis);

		Matrix(const Matrix<T> &other);
		Matrix<T> &operator=(const Matrix<T> &rhs);
		~Matrix();
		Matrix<T> operator-(const Matrix<T>& oth) const;
		Matrix<T> operator+(const Matrix<T>& oth) const;
		Matrix<T> operator*(const Matrix<T>& oth) const;
		Matrix<T> operator*(const std::vector<T>& oth) const;
		Matrix<T> operator*(const T oth) const;
		// Matrix<T> &operator/(const Matrix<T>& oth);
		// Matrix<T> &operator/(const std::vector<T>& oth);
		// == and != too?
		std::vector<T>& operator[](int row);
		const std::vector<T>& operator[](int row) const;

		unsigned int rows() const;
		unsigned int cols() const;

	private:
		std::vector<std::vector<T>> _container;
		unsigned int _rows, _cols;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& Class);

#include "Matrix.tpp"

#endif // MATRIX_HPP_