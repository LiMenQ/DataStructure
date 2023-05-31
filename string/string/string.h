#pragma once
#include<iostream>
#include<assert.h>

using std::cout;
using std::endl;
using std::cin;

namespace lmq{

	class string {
	public:
		typedef char* iterator;
		iterator begin() {
			return _str;
		}

		iterator end() {
			return _str + _size;
		}

		string(const char* str = ""){
			_size = strlen(str);
			_str = new char[_size + 1];
			_capacity = _size;
			copy(_str, str);
		}
		
		void swap(string& s) {
			std::swap(_str, s._str);
			std::swap(_capacity, s._capacity);
			std::swap(_size, s._size);
		}

		string(const string& str) :_str(nullptr), _capacity(0), _size(0) {
			string tmp(str._str);
			swap(tmp);
		}
		
		string& operator=(const string& str) {
			if (this != &str) {
				string tmp(str);
				swap(tmp);
			}
			return *this;
		}

		~string() {
			delete[] _str;
			_size = 0, _capacity = 0;
			_str = nullptr;
		}

		const char* c_str() const {
			return _str;
		}

		size_t size() const {
			return _size;
		}

		size_t capacity() const {
			return _capacity;
		}

		char& operator[](int n) {
			assert(n >= 0 && n < _size);
			return _str[n];
		}

		const char& operator[](int n) const {
			assert(n >= 0 && n < _size);
			return _str[n];
		}

		bool empty() const {
			return _size == 0;
		}

		void reserve(size_t n) {
			if (n > _capacity) {
				char* tmp = new char[n + 1];
				copy(tmp, _str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}

		void resize(size_t n, char c = '\0') {
			if (n > _size) {
				reserve(n);
				for (size_t i = _size; i < n; i++) {
					_str[i] = c;
				}
			}
			_str[n] = '\0';
			_size = n;
		}

		void clear() {
			string tmp("");
			swap(tmp);
		}

		void push_back(char c) {
			if (_size == _capacity) {
				size_t n = _capacity == 0 ? 10 : 2 * _capacity;
				reserve(n);
				_capacity = n;
			}
			*(_str + _size) = c;
			_size++;
		}

		void append(const char* str) {
			int len = strlen(str);
			if (_size + len > _capacity) {
				size_t n = _capacity + len + 20;
				reserve(n);
				_capacity = n;		
			}
			for (size_t i = _size; i < _size + len; i++) {
				_str[i] = str[i - _size];
			}
			_size += len;
		}

		string& operator+=(char c) {
			push_back(c);
			return *this;
		}

		string& operator+=(const char* str) {
			append(str);
			return *this;
		}

		bool operator<(const string& s) {
			size_t i = 0;
			for (i = 0; i < _size && i < s.size(); i++) {
				if (_str[i] < s[i]) return true;
				else if (_str[i] > s[i]) return false;
			}
			if (i < s.size()) return true;
			return false;
		}

		bool operator<=(const string& s) {
			return *this < s || *this == s;
		}

		bool operator>(const string& s) {
			return !(*this <= s);
		}

		bool operator>=(const string& s) {
			return !(*this < s);
		}

		bool operator==(const string& s) {
			if (_size != s.size()) return false;
			for (size_t i = 0; i < _size; i++) {
				if (_str[i] != s[i]) return false;
			}
			return true;
		}

		bool operator!=(const string& s) {
			return !(*this == s);
		}

		size_t find(char c, size_t pos = 0) const {
			for (size_t i = pos; i < _size; i++) {
				if (_str[i] == c) return i;
			}
			return npos;
		}

		// KMP
		size_t find(const char* s, size_t pos = 0) const{
			char* str = _str + pos;
			int len = strlen(str);
			int sublen = strlen(s);

			int* next = new int[sublen];
			get_next(next, s);

			int i = 0;
			int j = 0;

			while (i < len && j < sublen) {
				if (j == -1 || str[i] == s[j]) {
					++i;
					++j;
				}
				else {
					j = next[j];
				}
			}

			delete[] next;
			next = nullptr;

			if (j >= sublen)
				return i - j + pos;
			else
				return -1;
		}

		string& insert(size_t pos, char c) {
			size_t tmp = _size - 1;
			push_back(c);
			for (int i = tmp; i >= (int)pos; i--) {
				_str[i + 1] = _str[i];
			}
			_str[pos] = c;
			return *this;
		}

		string& insert(size_t pos, const char* str) {
			size_t tmp = _size - 1;
			int len = strlen(str);
			append(str);
			for (int i = tmp, j = (int)_size - 1; i >= (int)pos; i--, j--) {
				_str[j] = _str[i];
			}
			for (int i = pos, j = 0; i < pos + len; i++, j++) {
				_str[i] = str[j];
			}
			return *this;
		}

		string& erase(size_t pos, size_t len) {
			if (pos + len >= _size) {
				_str[pos] = '\0';
				_size = pos;
				return *this;
			}
			int begin = (int)(pos + len);
			for (int i = (int)pos, j = begin; j < _size; i++, j++) {
				_str[i] = _str[j];
			}
			_size -= len;
			_str[_size] = '\0';
			return *this;
		}

	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		const static size_t npos = -1;

		int strlen(const char* str) const{
			int i = 0;
			while (str[i] != '\0') i++;
			return i;
		}

		void copy(char* str1, const char* str2) {
			while (*str1++ = *str2++);
		}

		void get_next(int* next, const char* sub) const{
			int len = strlen(sub);
			next[0] = -1;
			next[1] = 0;
			int i = 2;
			int k = 0;
			while (i < len) {
				if (k == -1 || sub[i - 1] == sub[k]) {
					next[i] = ++k;
					++i;
				}
				else {
					k = next[k];
				}
			}
		}
	};

	std::ostream& operator<<(std::ostream& out, const string& s) {
		for (size_t i = 0; i < s.size(); i++) {
			out << s[i];
		}
		return out;
	}

	std::istream& operator>>(std::istream& in, string& s) {
		s.clear();
		char ch = in.get();
		while (ch == ' ' || ch == '\n') ch = in.get();
		while (ch != ' ' && ch != '\n') {
			s += ch; 
			ch = in.get();
		}
		return in;
	}

}