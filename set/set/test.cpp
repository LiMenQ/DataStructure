#include "set.h"
using namespace lmq;

void test1() {
	set<int> s;
	s.insert(1);
	s.insert(6);
	s.insert(8);
	s.insert(2);
	s.insert(0);
	set<int>::iterator it = s.begin();
	++it;
	++it;
	++it;
	while (it != s.begin()) {
		cout << *it << endl;
		--it;
	}
	cout << endl;
	for (auto x : s) {
		cout << x << endl;
	}
}

void test2() {
	set<int> s;
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(4);
	s.insert(5);
	s.insert(6);

	set<int>::iterator it = s.find(3);
	cout << *it << endl;
	for (auto x : s) {
		cout << x << endl;
	}
	
	set<int> s2(s);
	for (auto x : s2) {
		cout << x << endl;
	}

	set<int> s3;
	s3 = s;
	for (auto x : s3) {
		cout << x << endl;
	}
	
	pair<set<int>::iterator, bool> p = s3.insert(100);
	cout << *(p.first) << endl;


}

int main() {

	// test1();
	test2();

	return 0;
}