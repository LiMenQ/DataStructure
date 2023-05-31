#include "list.h"
using namespace lmq;

void printList(const list<int>& A) {
	list<int>::const_iterator it = A.begin();
	while (it != A.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

void test1() {
	list<int> A;
	A.push_back(1);
	A.push_back(2);
	A.push_back(3);
	A.push_back(4);
	A.push_back(5);
	list<int>::iterator it = A.begin();
	while (it != A.end()) {
		*it = *it + 1;
		cout << *it << " ";
		it++;
	}
	cout << endl;
	printList(A);
}

void test2() {
	list<int> A;
	A.push_front(3);
	A.push_front(2);
	A.push_front(1);
	A.push_back(5);
	A.push_back(6);
	A.push_back(7);
	A.pop_back();
	A.pop_front();
	for (auto x : A) cout << x << " ";
	cout << endl;
	A.clear();
	for (auto x : A) cout << x << " ";
	cout << endl;
	A.push_back(1);
	A.push_back(1);
	A.push_back(1);
	for (auto x : A) cout << x << " ";
	cout << endl;
}

void test3() {
	list<int> A;
	A.push_back(1);
	A.push_back(1);
	A.push_back(1);
	list<int> B(A);
	for (auto x : B) cout << x << endl;
	list<int> C;
	C.push_back(10);
	C.push_back(10);
	C.push_back(10);
	C.push_back(10);
	C.push_back(10);
	C.push_back(10);
	C = C;
	for (auto& x : A) cout << x << endl;
}	

void test5(const list<int> A) {
	list<int>::const_reverse_iterator rit = A.rbegin();
	while (rit != A.rend()) {
		cout << *rit << endl;
		rit++;
	}
}

void test4() {
	list<int> A;
	for (int i = 0; i < 5; i++) A.push_back(i + 1);
	list<int>::reverse_iterator rit = A.rbegin();
	while (rit != A.rend()) {
		(*rit)++;
		cout << *rit << endl;
		rit++;
	}
	test5(A);
}


int main() {

	// test1();
	// test2();
	// test3();
	test4();

	return 0;
}