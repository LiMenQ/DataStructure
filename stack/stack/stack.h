#pragma once
#include <iostream>
#include <deque>
#include <vector>
#include <list>

using std::cout;
using std::endl;

namespace lmq {
	template<class T, class Container = std::deque<T>> class stack {
	public:
		bool empty() {
			return _con.empty();
		}

		size_t size() {
			return _con.size();
		}

		T& top() {
			return _con.back();
		}

		void push(const T& x) {
			_con.push_back(x);
		}
		
		void pop() {
			_con.pop_back();
		}

	private:
		Container _con;
	};
}