#pragma once
#include <iostream>
#include <string>
#include<assert.h>

using std::cout;
using std::endl;
using std::string;

namespace lmq {
	template<class T> class vector {
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		vector() :_start(nullptr), _finish(nullptr), _endofstorage(nullptr) {}

		vector(size_t n) :_start(nullptr), _finish(nullptr), _endofstorage(nullptr)
		{
			assert(n >= 0);
			for (size_t i = 0; i < n; i++) {
				push_back(T());
			}
		}

		vector(int n, const int& val)
			:_start(nullptr), _finish(nullptr), _endofstorage(nullptr)
		{
			assert(n >= 0);
			for (int i = 0; i < n; i++) {
				push_back(val);
			}
		}

		vector(size_t n, const T& val) 
			:_start(nullptr), _finish(nullptr), _endofstorage(nullptr) 
		{
			assert(n >= 0);
			for (size_t i = 0; i < n; i++) {
				push_back(val);
			}
		}
		
		template<class InputIterator> vector(InputIterator first, InputIterator last)
			:_start(nullptr), _finish(nullptr), _endofstorage(nullptr)
		{
			while (first != last) {
				push_back(*first);
				++first;
			}
		}

		void Swap(vector<T>& v) {
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}
		
		vector(const vector<T>& v) :_start(nullptr), _finish(nullptr), _endofstorage(nullptr) {
			vector<T> tmp(v.begin(), v.end());
			Swap(tmp);
		}

		vector<T>& operator=(const vector<T>& v) {
			if (&v != this) {
				vector<T> tmp(v);
				Swap(tmp);
			}
			return *this;
		}

		~vector() {
			if (_start) {
				delete[] _start;
			}
			_start = _finish = _endofstorage = nullptr;
		}
		
		size_t capacity() {
			return _endofstorage - _start;
		}
		
		size_t size() {
			return _finish - _start;
		}

		void reserve(size_t n) {
			if (n > capacity()) {
				T* tmp = new T[n];
				if (_start) {
					int j = 0;
					for (iterator i = _start; i < _finish; i++) {
						tmp[j++] = *i;
					}
					delete[] _start;
				}
				size_t sz = size();
				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}

		void resize(size_t n, const T& val = T()) {
			if (n < 0) {
				return;
			}
			else if (n > capacity()) {
				reserve(n);
				while (_finish != _endofstorage) {
					*_finish = val;
					_finish++;
				}
			}
			else {
				_finish = _start + n;
			}
		}

		void push_back(T x) {
			if (_finish == _endofstorage) {
				size_t newCapacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(newCapacity);
			}
			*_finish = x;
			_finish++;
		}

		void pop_back() {
			assert(_finish > _start);
			--_finish;
		}

		iterator insert(iterator pos, const T& val) {
			assert(pos >= _start && pos <= _finish);
			if (_finish == _endofstorage) {
				size_t len = pos - _start;
				size_t newCapacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(newCapacity);
				pos = _start + len;
			}

			iterator end = _finish - 1;
			while (end >= pos) {
				*(end + 1) = *end;
				end--;
			}
			*pos = val;
			_finish++;
			return pos;
		}

		iterator erase(iterator pos) {
			assert(pos >= _start && pos < _finish);
			iterator begin = _start + 1;
			while (begin != _finish) {
				*(begin - 1) = *begin;
				begin++;
			}
			_finish--;
			return pos;
		}
		
		T& operator[](size_t i) {
			assert(i >= 0 && i < size());
			return *(_start + i);
		}

		iterator begin() {
			return _start;
		}

		iterator end() {
			return _finish;
		}

		const_iterator cbegin() const{
			return _start;
		}

		const_iterator cend() const {
			return _finish;
		}
		
		const_iterator begin() const {
			return _start;
		}
		
		const_iterator end() const {
			return _finish;
		}
		
	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};
}