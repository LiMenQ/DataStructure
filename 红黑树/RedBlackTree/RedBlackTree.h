#pragma once
#include <iostream>

using std::cout;
using std::endl;
using std::pair;

enum Color {
	RED,
    BLACK
};

template<class K, class V> struct RedBlackTreeNode {
	RedBlackTreeNode<K, V>* _parent;
	RedBlackTreeNode<K, V>* _left;
	RedBlackTreeNode<K, V>* _right;
	pair<K, V> _kv;
	Color _color;
	RedBlackTreeNode(const pair<K, V>& kv) 
		: _parent(nullptr), _left(nullptr), _right(nullptr), _color(RED), _kv(kv){}
};

template<class K, class V> class RedBlackTree {
	typedef RedBlackTreeNode<K, V> Node;
public:
	RedBlackTree() : _root(nullptr) {}

	bool RedBlackTreeInsert(const pair<K, V>& kv) {
		if (_root == nullptr) {
			_root = new Node(kv);
			_root->_color = BLACK; // 根结点为黑色
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (cur->_kv.first > kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_kv.first < kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				return false;
			}
		}

		// 找到插入位置 默认设置插入结点为红色
		cur = new Node(kv);
		cur->_color = RED;
		if (cur->_kv.first < parent->_kv.first) {
			parent->_left = cur;
		}
		else {
			parent->_right = cur;
		}
		cur->_parent = parent;

		// 控制平衡 && 调整颜色
		while (parent && parent->_color == RED) {
			Node* grandparent = parent->_parent;
			// parent是grandparent左孩子
			if (grandparent->_left == parent) {
				Node* uncle = grandparent->_right;
				// uncle存在且为红
				if (uncle && uncle->_color == RED) {
					// parent && uncle 染黑 greandparent染红
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandparent->_color = RED;
					
					// 向上调整
					cur = grandparent;
					parent = cur->_parent;
				}
				else {
					// uncle不存在或者uncle为黑
					if (cur == parent->_left) {
						// 右单旋 parent染黑 grandparent染红
						RotateR(grandparent);
						parent->_color = BLACK;
						grandparent->_color = RED;
					}
					else {
						// 左右双旋 cur染黑 grandparent染红
						RotateL(parent);
						RotateR(grandparent);
						cur->_color = BLACK;
						grandparent->_color = RED;
					}
					break;
				}
			}
			else {
				// parent是grandparent右孩子 对称的
				Node* uncle = grandparent->_left;
				if (uncle && uncle->_color == RED) {
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandparent->_color = RED;
					cur = grandparent;
					parent = cur->_parent;
				}
				else {
					if (cur == parent->_right) {
						// 左单旋
						RotateL(grandparent);
						parent->_color = BLACK;
						grandparent->_color = RED;
					}
					else {
						// 右左双旋
						RotateR(parent);
						RotateL(grandparent);
						cur->_color = BLACK;
						grandparent->_color = RED;
					}
					break;
				}
			}
		}
		// 根结点暴力染黑
		_root->_color = BLACK;
		return true;
	}

	bool RedBlackTreeFind(const K& key) {
		Node* cur = _root;
		while (cur) {
			if (cur->_kv.first > key) {
				cur = cur->_left;
			}
			else if (cur->_kv.first < key) {
				cur = cur->_right;
			}
			else {
				return true;
			}
		}
		return false;
	}

	void RedBlackTreeInorder() {
		_RedBlackTreeInorder(_root);
		cout << endl;
	}

	int RedBlackTreeHeight() {
		return _RedBlackTreeHeight(_root);
	}

	bool RedBlackTreeChecked() {
		if (_root && _root->_color == RED) {
			cout << "根结点不是黑色" << endl;
			return false;
		}
		
		// 查找一路中的黑结点数量
		int countNum = 0, blackNum = 0;
		Node* cur = _root;
		while (cur) {
			if (cur->_color == BLACK) {
				countNum++;
			}
			cur = cur->_left;
		}
		return _RedBlackTreeChecked(_root, blackNum, countNum);
	}

private:
	void RotateL(Node* parent) {
		Node* curR = parent->_right;
		Node* curRL = curR->_left;
		parent->_right = curRL;
		if (curRL) curRL->_parent = parent;
		Node* grandparent = parent->_parent;
		curR->_left = parent;
		parent->_parent = curR;
		
		if (parent == _root) {
			_root = curR;
			curR->_parent = nullptr;
		}
		else {
			if (grandparent->_left == parent) {
				grandparent->_left = curR;
			}
			else {
				grandparent->_right = curR;
			}
			curR->_parent = grandparent;
		}
	}

	void RotateR(Node* parent) {
		Node* curL = parent->_left;
		Node* curLR = curL->_right;
		parent->_left = curLR;
		if (curLR) curLR->_parent = parent;
		Node* grandparent = parent->_parent;
		curL->_right = parent;
		parent->_parent = curL;
			
		if (parent == _root) {
			_root = curL;
			curL->_parent = nullptr;
		}
		else {
			if (grandparent->_left == parent) {
				grandparent->_left = curL;
			}
			else {
				grandparent->_right = curL;
			}
			curL->_parent = grandparent;
		}
	}

	void _RedBlackTreeInorder(Node* root) {
		if (root == nullptr)
			return;
		_RedBlackTreeInorder(root->_left);
		cout << root->_kv.first << "-" << root->_kv.second << " ";
		_RedBlackTreeInorder(root->_right);
	}

	int _RedBlackTreeHeight(Node* root) {
		if (root == nullptr)
			return 0;
		return 1 + std::max(_RedBlackTreeHeight(root->_left), _RedBlackTreeHeight(root->_right));
	}

	bool _RedBlackTreeChecked(Node* root, int blackNum, int countNum) {
		if (root == nullptr) {
			if (blackNum != countNum) {
				cout << "每条路径黑色结点数量不一致" << endl;
				return false;
			}
			return true;
		}
		if (root->_color == RED && root->_parent->_color == RED) {
			cout << "路径中出现连续两个红色结点" << endl;
			return false;
		}

		if (root->_color == BLACK) {
			blackNum++;
		}
		return _RedBlackTreeChecked(root->_left, blackNum, countNum) 
			&& _RedBlackTreeChecked(root->_right, blackNum, countNum);
	}

	Node* _root;
};
