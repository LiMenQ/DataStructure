#include "vector.h"
using namespace lmq;

void test1() {
	vector<int> C;
	C.push_back(1);
	C.push_back(2);
	C.push_back(3);
	C.push_back(4);
	C.push_back(4);
	C.push_back(5);
	for (int i = 0; i < C.size(); i++) cout << C[i] << " ";
	cout << endl;
	vector<int>::iterator begin = C.begin();
	while (begin != C.end()) {
		cout << *begin << endl;
		++begin;
	}
}

void test2() {

	vector<int> C;
	C.push_back(1);
	C.push_back(2);
	C.push_back(3);
	C.push_back(4);
	C.push_back(5);
	C.push_back(1);
	C.push_back(2);
	C.push_back(3);
	C.push_back(4);
	C.push_back(5);
	C.push_back(1);
	C.push_back(2);
	C.push_back(3);
	C.push_back(4);
	C.push_back(5);
	for (int i = 0; i < C.size(); i++) cout << C[i] << " ";
	cout << endl;
	cout << C.capacity() << endl;
	C.reserve(20);
	cout << C.capacity() << endl;
	C.resize(5);
	for (int i = 0; i < C.size(); i++) cout << C[i] << " ";
	cout << endl;
	cout << C.capacity() << endl;
	C.resize(30, 4);
	for (int i = 0; i < C.size(); i++) cout << C[i] << " ";
	cout << endl;
	cout << C.capacity() << endl;
}

void test3() {
	vector<int> A;
	A.push_back(1);
	A.push_back(2);
	A.push_back(3);
	A.push_back(4);
	A.push_back(5);
	vector<int> C(A);
	for (int i = 0; i < C.size(); i++) cout << C[i] << " ";
	cout << endl;
	vector<int> B;
	B.push_back(10);
	B.push_back(10);
	B.push_back(10);
	C = B;
	for (int i = 0; i < C.size(); i++) cout << C[i] << " ";
	cout << endl;
}

void test4() {
	vector<int> C;
	C.push_back(1);
	C.push_back(2);
	C.push_back(3);
	C.push_back(4);
	for (int i = 0; i < C.size(); i++) cout << C[i] << " ";
	cout << endl;
	C.pop_back();
	C.pop_back();
	for (int i = 0; i < C.size(); i++) cout << C[i] << " ";
	cout << endl;
	/*vector<int> A(10, 5);
	for (int i = 0; i < A.size(); i++) cout << A[i] << " ";*/
}

void test5() {
	vector<int> C;
	//C.push_back(1);
	vector<int>::iterator bg = C.begin();
	bg = C.insert(bg, 0);
	bg = C.insert(bg, 1);
	bg = C.insert(bg, 2);
	bg = C.insert(bg, 3);
	bg = C.insert(bg, 4);
	bg = C.insert(bg, 5);
	bg = C.insert(bg, 6);
	for (int i = 0; i < C.size(); i++) cout << C[i] << " ";
	cout << endl;
	vector<int>::iterator er = C.begin();
	er = C.erase(er);
	er = C.erase(er);
	for (int i = 0; i < C.size(); i++) cout << C[i] << " ";
	cout << endl;
	vector<int> A;
	for (int i = 0; i < 8; i++) A.push_back(i);
	vector<int>::const_iterator cit = A.cbegin();
	while (cit != A.cend()) {
		cout << *cit++ << ' ';
	}
	cout << endl;
	vector<int> B(5, 10);
	for (int i = 0; i < B.size(); i++) cout << B[i] << " ";

}

void test6() {
	vector<string> C;
	C.push_back("1111111111111");
	C.push_back("1111111111111");
	C.push_back("11111111111111");
	C.push_back("11111111111111");
	C.push_back("11111111111111");
	C.push_back("111111111111111");
	for (auto& x : C) cout << x << endl;
	vector<int> A(10, 5);
	for (auto x : A) cout << x << endl;
}

int main() {

	// test1();
	// test2();
	// test3();
	// test4();
	// test5();
	test6();

	return 0;
}