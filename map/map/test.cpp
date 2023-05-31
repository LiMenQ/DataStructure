#include "map.h"
using namespace lmq;

void test1() {
	map<int, int> mp;
	mp.insert({1, 1});
	mp.insert({5, 5});
	mp.insert({8, 8});
	mp.insert({4, 4});
	mp.insert({0, 0});
	
	for (auto x : mp) {
		cout << x.first << " " << x.second << endl;
	}
	
}

void test2() {
	map<int, int> mp;
	mp[0] = 1;
	mp[1] = 2;
	mp[5] = 10;
	mp[10] = 20;
	mp[0] = 15;

	for (auto x : mp) {
		cout << x.first << '-' << x.second << endl;
	}
}

int main() {

	// test1();
	test2();

	return 0;
}