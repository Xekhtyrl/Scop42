#pragma once
#include <iostream>
#include <cmath>

//stand for Vectors and Matrices Library
namespace vml {
	template<typename T, size_t N >
	struct Vector {
		T data[N];

		//constructors
		constexpr Vector() : data{} {}
		constexpr Vector(std::initializer_list<T> vals) {
			size_t i = 0;
			for (auto &x : vals)
				data[i++] = x;
		}
		//operators
		constexpr T& operator[](int index) {return data[index];}
		constexpr const T& operator[](int index) const {return data[index];}
		Vector<T, N> operator+(const Vector<T, N>& vec) {
			Vector<T, N> res;
			for (size_t i = 0; i < N; i++)
				res[i] = data[i] + vec[i];
			return res;
		}
		Vector<T, N>& operator+=(const Vector<T, N>& vec) {
			for (size_t i = 0; i < N; i++)
				data[i] += vec[i];
			return *this;
		}
		Vector<T, N> operator-(const Vector<T, N>& vec) {
			Vector<T, N> res;
			for (size_t i = 0; i < N; i++)
				res[i] = data[i] - vec[i];
			return res;
		}
		Vector<T, N>& operator-=(const Vector<T, N>& vec) {
			for (size_t i = 0; i < N; i++)
				data[i] -= vec[i];
			return *this;
		}
		// Cross product (only for 3D)
		constexpr Vector<T, 3> cross(const Vector<T, 3>& v) const requires (N == 3) {
			return {
				data[1] * v.data[2] - data[2] * v.data[1],
				data[2] * v.data[0] - data[0] * v.data[2],
				data[0] * v.data[1] - data[1] * v.data[0]
			};
		}
		Vector<T, N> operator*(const T val) {
			Vector<T, N> res;
			for (size_t i = 0; i < N; i++)
				res[i] = data[i] * val;
			return res;
		}
		Vector<T, N>& operator*=(const T val) {
			for (T& x : data)
				x *= val;
			return *this;
		}
		// other operations
		T dot(Vector<T,N> vec) {
			T res = T{};
			for (size_t i = 0; i < N; i++)
				res += data[i] * vec[i];
			return res;
		}
		T norm() {return std::sqrt(dot(*this));}
		Vector<T, N> normalize() {
			T len = norm();
			Vector res;
			for (T x: data)
				res = x / len;
			return res;
		}
		// getter
		constexpr const size_t size() const {return N;}

		void print() {
			std::cout << "[";
			for (size_t i = 0; i < N; i++){
				std::cout << data[i];
				if (i < N - 1)
					std::cout << ", ";
			}
			std::cout << "]" << std::endl;
		}
	};
	using vec2 = Vector<float, 2>;
	using vec3 = Vector<float, 3>;
	template<typename T , size_t R, size_t C>
	struct Matrix {
		T data[R * C];

		//constructors
		constexpr Matrix() : data{} {}
		constexpr Matrix(std::initializer_list<T> vals) {
			size_t i = 0;
			for (auto &x : vals)
				data[i++] = x;
		}
		// operators

		constexpr T& operator()(int r, int c) {return data[r * C + c];}
		constexpr const T& operator()(int r, int c) const {return data[r * C + c];}
		constexpr T* operator[](int r) {return &data[r * C];}
		constexpr const T* operator[](int r) const {return &data[r * C];}
		Matrix<T, R, C> operator+(Matrix<T, R, C> mat) {
			Matrix res;
			for (size_t i = 0; i < R * C; i++)
				res = data[i] + mat[i];
			return res;
		}
		Matrix<T, R, C>& operator+=(Matrix<T, R, C> mat) {
			for (size_t i = 0; i < R * C; i++)
				data[i] += mat[i];
			return *this;
		}
		Matrix<T, R, C> operator-(Matrix<T, R, C> mat) {
			Matrix res;
			for (size_t i = 0; i < R * C; i++)
				res = data[i] - mat[i];
			return res;
		}
		Matrix<T, R, C>& operator-=(Matrix<T, R, C> mat) {
			for (size_t i = 0; i < R * C; i++)
				data[i] -= mat[i];
			return *this;
		}
		template<size_t C2>
		Matrix<T, R, C2> operator*(Matrix<T, C, C2> mat) {
			Matrix<T, R, C2> res{};
			for (size_t r = 0; r < R; r++){
				for (size_t c2 = 0; c2 < C2; c2++){
					for (size_t c = 0; c < C; c++){
						res[r][c2] += (*this)[r][c] * mat[c][c2];
					}
				}
			}
			return res;
		}
		template<size_t C2>
		Matrix<T, R, C2> operator*=(Matrix<T, C, C2> mat) {
			static_assert(R == C, "For *= operation Matrix need to be square.");
			*this = (*this) * mat;
			return *this;
		}
		template<size_t C2>
		Vector<T, R> operator*(Vector<T, C2> vec) {
			static_assert(C == C2, "Matrix and vector sizes incompatible.");
			Vector<T, R> res;
			for (size_t r = 0; r < R; r++)
				for (size_t c = 0; c < C2; c++)
					res[r] += vec[c] * (*this)[r][c];
			return res;
		}
		//getter
		void print() {
			std::cout << "[";
			for (size_t i = 0; i < R; i++) {
				std::cout << "[";
				for (size_t j = 0; j < C; j++) {
					std::cout << data[i * C + j];
					if (j < C - 1)
					std::cout << ", ";
				}
				std::cout << "]";
				if (i < R - 1)
				std::cout<< "\n";
			}
			std::cout << "]" << std::endl;
		}
	};
	using mat3 = Matrix<float, 3, 3>;
	using mat4 = Matrix<float, 4, 4>;
}