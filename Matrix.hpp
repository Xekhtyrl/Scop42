
#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <vector>
#include <iostream>

// should I make a K var for diversity (i.e K T operation and not only T T)
template <typename T>

// Class declaration
class Matrix {
	public:
		Matrix();
		Matrix(const Matrix<T> &other);
		Matrix<T> &operator=(const Matrix<T> &rhs);
		~Matrix();
		template <typename K>
		Matrix<decltype(T{} - K {})> &operator-(const Matrix<K>& oth) const;
		template <typename K>
		Matrix<decltype(T{} + K {})> &operator+(const Matrix<K>& oth) const;
		template <typename K>
		Matrix<decltype(T{} * K {})> &operator*(const Matrix<K>& oth) const;
		template <typename K>
		Matrix<decltype(T{} * K {})> &operator*(const std::vector<K>& oth) const;
		template <typename K>
		Matrix<decltype(T{} * K {})> &operator*(const K oth) const;
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

#endif // MATRIX_HPP_
