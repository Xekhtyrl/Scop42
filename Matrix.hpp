
#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include "Includes/header.h"
#include "linAlg.hpp"

template<typename Container>
Container normalize(Container vec);
// Custom Matrix Object Allowing you instantiate it in different way, and purpose 
// (empty, identity, filled with 1 val, with a nested vector of T value, or even a translation or rotation matrix)
// and to make different orperation with it 
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
		static Matrix<T> translation(std::vector<T> vec);

		/// @brief Rotation matrix of 'rad' radians around the axis 'axis'.
		/// @param rad Angle in radians.
		/// @param axis A size-3 axis vector (should be normalized).
		static Matrix<T> rot(T rad, std::vector<T> axis);

		static Matrix<T> ortho(T left, T rigth, T bottom, T top, T near, T far);

		static Matrix<T> perspective(T rad, T aspect, T near, T far);

		static Matrix<T> lookAt(std::vector<T>,std::vector<T>,std::vector<T>);

		Matrix(const Matrix<T> &other);
		Matrix<T> &operator=(const Matrix<T> &rhs);
		~Matrix();
		Matrix<T> operator-(const Matrix<T>& oth) const;
		Matrix<T>& operator-=(const Matrix<T>& oth);
		Matrix<T> operator+(const Matrix<T>& oth) const;
		Matrix<T>& operator+=(const Matrix<T>& oth);
		Matrix<T> operator*(const Matrix<T>& oth) const;
		Matrix<T>& operator*=(const Matrix<T>& oth);
		Matrix<T> operator*(std::vector<T> oth) const;
		Matrix<T>& operator*=(std::vector<T> oth);
		Matrix<T> operator*(const T oth) const;
		Matrix<T>& operator*=(const T oth);
		// Matrix<T> &operator/(const Matrix<T>& oth);
		// Matrix<T> &operator/(const std::vector<T>& oth);
		// == and != too?
		std::vector<T>& operator[](int row);
		const std::vector<T>& operator[](int row) const;

		unsigned int rows() const;
		unsigned int cols() const;
		const float* toGLArray(bool columnMajor = true) const;

		Matrix<T>& scale(std::vector<T>);

	private:
		std::vector<std::vector<T>> _container;
		unsigned int _rows, _cols;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& Class);

#include "Matrix.tpp"

#endif // MATRIX_HPP_