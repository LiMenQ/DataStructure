#include "stack.h"
using namespace lmq;

void test1() {
	stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);

	while (!st.empty()) {
		cout << st.top() << endl;
		st.pop();
	}
}

void test2() {
	stack<int, std::vector<int>> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);

	while (!st.empty()) {
		cout << st.top() << endl;
		st.pop();
	}
}

void test3() {
	stack<int, std::list<int>> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);

	while (!st.empty()) {
		cout << st.top() << endl;
		st.pop();
	}
}

int main() {

	// test1();
	// test2();
	test3();

	return 0;
}