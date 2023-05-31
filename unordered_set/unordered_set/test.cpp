#include "unordered_set.h"
using namespace lmq;

int main() {
	
	unordered_set<int> s;

	for (int i = 0; i < 100; i++) {
		s.insert(i + 10);
	}
	
	unordered_set<int> s2;
	s2.insert(55);
	s2 = s;
	auto x = s2.begin();
	while (x != s.end()) {
		cout << *x << endl;
		++x;
	}

	return 0;
}