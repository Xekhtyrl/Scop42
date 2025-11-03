#pragma once
#include "Includes/header.h"

template <typename T>
class Vector {
	private:
		std::vector<T> _data;
		size_t _size;
	public:
		//-------------------------Constructors & Destructors-------------------------//
		Vector() {
			// _data = std::vector<T>();
			// _size = 0;
		};
		Vector(std::vector<T> vec) : _data(vec){
			_size = vec.size();
		};
		Vector(size_t size, T val = T{}) {
			_data = std::vector<T>(size, val);
			_size = size;
		};
		Vector(const Vector<T>& other): _data(other._data), _size(other._size) {}
		Vector<T> &operator=(const Vector<T> &rhs) {
			_data = rhs._data;
			_size = rhs._size;
			return *this;
		};

		~Vector(){};

		//----------------------------------Operators----------------------------------//
		Vector<T> operator-(const Vector<T>& oth) const {
			if (oth._size != _size)
				throw std::runtime_error("Error: Vectors of incompatible size.");
			Vector<T> res(_size);
			for (int i = 0; i < _size; i++)
				res[i] = _data[i] - oth[i];
			return res;
		};

		Vector<T>& operator-=(const Vector<T>& oth) {
			if (oth._size != _size)
				throw std::runtime_error("Error: Vectors of incompatible size.");

			for (int i = 0; i < _size; i++)
				_data[i] -= oth[i];
			return *this;
		};

		Vector<T> operator+(const Vector<T>& oth) const {
			if (oth._size != _size)
				throw std::runtime_error("Error: Vectors of incompatible size.");
			Vector<T> res(_size);
			for (int i = 0; i < _size; i++)
				res[i] = _data[i] + oth[i];
			return res;
		};

		Vector<T>& operator+=(const Vector<T>& oth) {
			if (oth._size != _size)
				throw std::runtime_error("Error: Vectors of incompatible size.");
			for (int i = 0; i < _size; i++)
				_data[i] += oth[i];
			return *this;
		};

		Vector<T> operator*(const Vector<T>& oth) const {
			if (oth._size != _size || _size != 3)
				throw std::runtime_error("Error: Vectors of incompatible size.");
			Vector<T> res(_size);
			res[0] = (*this)[1] * oth[2] - (*this)[2] * oth[1];
			res[1] = (*this)[2] * oth[0] - (*this)[0] * oth[2];
			res[2] = (*this)[0] * oth[1] - (*this)[1] * oth[0];
			return res;
		}; // cross product

		Vector<T>& operator*=(const Vector<T>& oth) {
			if (oth._size != _size || _size != 3)
				throw std::runtime_error("Error: Vectors of incompatible size.");
			    Vector<T> tmp(_size);
			tmp[0] = _data[1] * oth[2] - _data[2] * oth[1];
			tmp[1] = _data[2] * oth[0] - _data[0] * oth[2];
			tmp[2] = _data[0] * oth[1] - _data[1] * oth[0];

			*this = tmp;
			return *this;
		}; // cross product

		Vector<T> operator*(const T val) const {
			Vector<T> res(_size);
			for (int i = 0; i < _size; i++)
			res[i] = _data[i] * val;
			return res;
		};

		friend Vector<T> operator*(T scalar, const Vector<T>& vec) {
			return vec * scalar; // just reuse the member operator
		}
		
		Vector<T>& operator*=(const T val) {
			for (int i = 0; i < _size; i++)
				_data[i] *= val;
			return *this;
		};
		
		Vector<T> operator/(const T val) const {
			if (val == T{})
			throw std::runtime_error("Error: Can not Divide by 0");
			Vector<T> res(_size);
			for (int i = 0; i < _size; i++)
			res[i] = _data[i] / val;
			return res;
		};
		
		Vector<T>& operator/=(const T val) {
			for (int i = 0; i < _size; i++)
				_data[i] /= val;
			return *this;
		};
		
		//-------------------------Getters & Setters-------------------------//
		size_t size() const {
			return _size;
		}

		T& operator[](int index) {
			if (index < 0 && _size + index >= 0)
			return _data[_size + index];
			return _data[index];
		}

		const T operator[](int index) const {
			if (index < 0 && _size + index >= 0)
			return _data[_size + index];
			return _data[index];
		}

		void push_back(T& value) {
			_data.push_back(value);
			_size += 1;
		}

		void pop_back() {
			_data.pop_back();
			_size -= 1;
		}

		const std::vector<T> container() const{
			return _data;
		}

		//-------------------------Other Methods-------------------------//
		T dot(const Vector<T>& oth) const {
			if (oth._size != _size)
				throw std::runtime_error("Error: Vectors of incompatible size.");
			T res = T{};
			for (int i = 0; i < _size; i++)
				res += (*this)[i] * oth[i];
			return res;
		}; // dot product

		//-------------------------Iterators-------------------------//
		typedef typename std::vector<T>::iterator iterator;
		typedef typename std::vector<T>::const_iterator const_iterator;
		using value_type = T;

		iterator begin(){
			return this->_data.begin();
		};
		iterator end(){
			return this->_data.end();
		};

		const_iterator begin() const {
			return _data.begin();
		}

		const_iterator end() const {
			return _data.end();
		}
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& Class){
	size_t len = Class.size();
	out << "[";
	for (size_t i = 0; i < len; i++){
		out << Class[i];
		if (i < len - 1)
			out << ", ";
	}
	out << "]" << std::endl;
	return out;
};
