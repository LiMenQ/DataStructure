#include "AVLTree.h"

void test1() {
	AVLTree<int, int> tree;
	int a[] = { 5, 4, 3, 2, 1 };
	for (auto x : a) {
		tree.AVLTreeInsert(std::make_pair(x, x));
		cout << tree.AVLTreeHeight() << endl;
		cout << tree.AVLTreeBalance() << endl;
	}
	tree.AVLTreeInorder();
}

void test2() {
	AVLTree<int, int> tree;
	int a[] = { 5, 4, 3, 2, 1 };
	for (auto x : a) {
		tree.AVLTreeInsert(std::make_pair(x, x));
	}
	cout << tree.AVLTreeFind(1) << endl;
	cout << tree.AVLTreeFind(5) << endl;
	cout << tree.AVLTreeFind(4) << endl;
	cout << tree.AVLTreeFind(7) << endl;
}

int main() {

	// test1();
	test2();

	return 0;
}