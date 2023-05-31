#pragma once
#include<iostream>
#include<vector>

using std::cout;
using std::endl;

namespace lmq {
	
	template<class T> struct less {
		bool operator()(const T& a, const T& b) {
			return a < b;
		}
	};

	template<class T> struct greater {
		bool operator()(const T& a, const T& b) {
			return a > b;
		}
	};
	
	template<class T, class Container = std::vector<T>, class Compare = less<T>>
	class priority_queue {
	public:
		priority_queue(){}

		template<class InputIterator> priority_queue(InputIterator first, InputIterator last)
			:_con(first, last)
		{
			for (int i = (_con.size() - 2) / 2; i >= 0; i--) {
				AdjustDown(i);
			}
		}
		
		void push(const T& x) {
			_con.push_back(x);
			AdjustUp(_con.size() - 1);
		}

		void pop() {
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			AdjustDown(0);
		}

		const T& top() {
			return _con[0];
		}

		size_t size() {
			return _con.size();
		}

		bool empty() {
			return _con.empty();
		}
		
	private:
		void AdjustDown(size_t parent) {
			Compare compare;
			size_t child = parent * 2 + 1;
			while (child < size()) {
				if (child + 1 < size() && compare(_con[child], _con[child + 1])) {
					child++;
				}
				if (compare(_con[parent], _con[child])) {
					std::swap(_con[parent], _con[child]);
					parent = child;
					child = child * 2 + 1;
				}
				else {
					break;
				}
			}
		}

		void AdjustUp(size_t child) {
			Compare compare;
			size_t parent = (child - 1) / 2;
			while (child > 0) {
				if (compare(_con[parent], _con[child])) {
					std::swap(_con[parent], _con[child]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else {
					break;
				}
			}
		}

		Container _con;
	};
}