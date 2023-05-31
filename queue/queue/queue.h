#pragma once
#include <iostream>
#include <deque>
#include <list>

using std::cout;
using std::endl;

namespace lmq {
	template<class T, class Container = std::deque<T>> class queue {
	public:
		bool empty() {
			return _con.empty();
		}

		size_t size() {
			return _con.size();
		}
		
		T& front() {
			return _con.front();
		}

		T& back() {
			return _con.back();
		}

		void push(const T& x) {
			_con.push_back(x);
		}

		void pop() {
			_con.pop_front();
		}

	private:
		Container _con;
	};
}
