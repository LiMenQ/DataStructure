#include "BinarySearchTree.h"

void test1() {
	BSTree<int> root;
	int a[] = { 2, 5, 8, 4, 3, 1, 0, 7, 9, 6, 6, 6 };
	for (auto x : a) {
		root.BSTreeInsert(x);
		bool res = root.BSTreeFind(x);
		cout << res << " ";
	}
	bool res = root.BSTreeFind(10);
	cout << res << " ";
	res = root.BSTreeFind(11);
	cout << res << " ";
	res = root.BSTreeFind(12);
	cout << res << " ";
	cout << endl;
	root.BSTreeInOrder();
}

void test2() {
	BSTree<int> root;
	int a[] = { 2, 5, 8, 4, 3, 1, 0, 7, 9, 6, 6, 6 };
	for (auto x : a) {
		root.BSTreeInsert(x);
	}
	root.BSTreeInOrder();
	root.BSTreeErase(0);
	root.BSTreeInOrder();
	root.BSTreeErase(2);
	root.BSTreeInOrder();
	root.BSTreeErase(4);
	root.BSTreeInOrder();
	root.BSTreeErase(0);
	root.BSTreeInOrder();
	root.BSTreeErase(7);
	root.BSTreeInOrder();
}

void test3() {
	BSTree<int> root;
	int a[] = { 2, 5, 8, 4, 3, 1, 0, 7, 9, 6, 6, 6 };
	for (auto x : a) {
		root.BSTreeInsertR(x);
		bool res = root.BSTreeFindR(x);
		cout << res << " ";
	}
	bool res = root.BSTreeFindR(10);
	cout << res << " ";
	res = root.BSTreeFindR(11);
	cout << res << " ";
	res = root.BSTreeFindR(12);
	cout << res << " ";
	cout << endl;
	root.BSTreeInOrder();
}

void test4() {
	BSTree<int> root;
	int a[] = { 2, 5, 8, 4, 3, 1, 0, 7, 9, 6, 6, 6 };
	for (auto x : a) {
		root.BSTreeInsertR(x);
	}
	root.BSTreeInOrder();
	root.BSTreeEraseR(0);
	root.BSTreeInOrder();
	root.BSTreeEraseR(2);
	root.BSTreeInOrder();
	root.BSTreeEraseR(4);
	root.BSTreeInOrder();
	root.BSTreeEraseR(0);
	root.BSTreeInOrder();
	root.BSTreeEraseR(7);
	root.BSTreeInOrder();
}

int main() {

	// test1();
	// test2();
	// test3();
	test4();

	return 0;
}