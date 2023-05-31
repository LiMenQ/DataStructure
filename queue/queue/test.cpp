#include "queue.h"
using namespace lmq;

void test1() {
	queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	while (!q.empty()) {
		cout << q.front() << endl;
		q.pop();
	}
}

void test2() {
	queue<int, std::list<int>> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	while (!q.empty()) {
		cout << q.front() << endl;
		q.pop();
	}
}

int main() {

	// test1();
	test2();

	return 0;
}
