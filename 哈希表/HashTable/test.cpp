#include "HashTable.h"

void test1() {
	CloseHash::HashTable<int, int> ht;
	
	for (int i = 0; i < 100; i++) {
		ht.HashTableInsert({i, i});
	}
	
	auto res = ht.HashTableFind(3);
	cout << res->_kv.first << endl;
	cout << ht.HashTableErase(3) << endl;
	auto res2 = ht.HashTableFind(3);
	cout << res2->_kv.first << endl;
}

void test2() {
	OpenHash::HashTable<int, int> t;
	t.HashTableInsert({1, 1});
	t.HashTableInsert({2, 2});
	t.HashTableInsert({3, 3});
	t.HashTableInsert({4, 4});
	for (int i = 10; i < 100; i++) {
		t.HashTableInsert({i, i});
	}
	auto res = t.HashTableFind(50);
	cout << res->_kv.first << endl;
	t.HashTableErase(50);
	auto res2 = t.HashTableFind(50);
	cout << res2->_kv.first << endl;
}

int main() {

	// test1();
	test2();

	return 0;
}