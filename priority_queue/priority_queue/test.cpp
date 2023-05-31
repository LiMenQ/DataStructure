#include "priority_queue.h"
using namespace lmq;

void test1() {
	priority_queue<int> heap;
	heap.push(1);
	heap.push(3);
	heap.push(3);
	heap.push(6);
	heap.push(9);
	heap.push(8);

	while (!heap.empty()) {
		cout << heap.top() << endl;
		heap.pop();
	}

}

void test2() {
	priority_queue<int, std::vector<int>, greater<int>> heap;
	heap.push(1);
	heap.push(3);
	heap.push(3);
	heap.push(6);
	heap.push(9);
	heap.push(8);

	while (!heap.empty()) {
		cout << heap.top() << endl;
		heap.pop();
	}
}

class Stu {
public:
	Stu(int num = 0) :_num(num) {}
	int _num;
};

struct Compare_Stu_Less {
	bool operator()(const Stu& a, const Stu& b) {
		return a._num < b._num;
	}
};

void test3() {
	priority_queue<Stu, std::vector<Stu>, Compare_Stu_Less> pq;
	Stu s1(10);
	Stu s2(20);
	Stu s3(30);
	Stu s4(40);
	Stu s5(28);
	pq.push(s1);
	pq.push(s2);
	pq.push(s3);
	pq.push(s4);
	pq.push(s5);

	while (!pq.empty()) {
		cout << pq.top()._num << endl;
		pq.pop();
	}
	
}

int main() {

	// test1();
	// test2();
	test3();

	return 0;
}