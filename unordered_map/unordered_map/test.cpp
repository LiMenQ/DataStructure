#include "unordered_map.h"
using namespace lmq;

int main() {

	unordered_map<int, int> m;
	for (int i = 20; i < 50; i++) {
		m.insert({i, i});
	}
	
	m.insert({1, 1});
	m[2] = 10;
	m[3] = 10;
	m[4] = 10;
	m[5] = 10;
	m.erase(5);
	m.erase(1);

	auto it = m.begin();
	while (it != m.end()) {
		cout << it->first << " " << it->second << endl;
		++it;
	}

	cout << m[1] << endl;

	return 0;
}