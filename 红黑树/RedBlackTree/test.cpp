#include "RedBlackTree.h"

void test1() {
	RedBlackTree<int, int> rbt;
	int a[] = { 6, 5, 4, 3, 2, 1, 11, 10, 9, 7, 8 };
	// int a[] = { 6, 5, 4, 3, 2, 1, 11, 1};
	for (auto x : a) {
		rbt.RedBlackTreeInsert({x, x});
	}
	rbt.RedBlackTreeInsert({10, 10});
	rbt.RedBlackTreeInorder();
}

void test2() {
	RedBlackTree<int, int> rbt;
	int a[] = { 6, 5, 4, 3, 2, 1, 11, 10, 9, 7, 8 };
	for (auto x : a) {
		rbt.RedBlackTreeInsert({ x, x });
		cout << rbt.RedBlackTreeChecked() << endl;
	}
	cout << rbt.RedBlackTreeHeight() << endl;
	cout << rbt.RedBlackTreeFind(1) << endl;
	cout << rbt.RedBlackTreeFind(9) << endl;
	cout << rbt.RedBlackTreeFind(8) << endl;
	cout << rbt.RedBlackTreeFind(3) << endl;
	cout << rbt.RedBlackTreeFind(0) << endl;
	cout << rbt.RedBlackTreeFind(15) << endl;
	rbt.RedBlackTreeInsert({ 10, 10 });
}

int main() {

	// test1();
	test2();

	return 0;
}