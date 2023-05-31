#pragma once
#include <iostream>

using std::cout;
using std::endl;
using std::swap;
using std::pair;
using std::make_pair;

enum Color {
	RED,
	BLACK
};

template<class T> struct RedBlackTreeNode {
	RedBlackTreeNode<T>* _parent;
	RedBlackTreeNode<T>* _left;
	RedBlackTreeNode<T>* _right;
	T _val;
	Color _color;
	RedBlackTreeNode(const T& val)
		: _parent(nullptr), _left(nullptr), _right(nullptr), _color(RED), _val(val) {}
};

template<class T, class Ref, class Ptr> struct RedBlackTreeIterator {
	typedef RedBlackTreeNode<T> Node;
	typedef RedBlackTreeIterator<T, Ref, Ptr> Self;
	Node* _node;
	RedBlackTreeIterator(Node* node) : _node(node) {}

	Ref operator*() {
		return _node->_val;
	}

	Ptr operator->() {
		return &_node->_val;
	}

	bool operator==(const Self& self) {
		return _node == self._node;
	}

	bool operator!=(const Self& self) {
		return _node != self._node;
	}

	Self& operator++() {
		// ���������� ����������
		if (_node->_right) {
			Node* left = _node->_right;
			while (left->_left) {
				left = left->_left;
			}
			_node = left;
		}
		else {
			// ���ݵ��� ���� �����Ƚ���������
			Node* cur = _node;
			Node* parent = _node->_parent;
			while (parent && parent->_right == cur) {
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	Self& operator--() {
		if (_node->_left) {
			Node* right = _node->_left;
			while (right->_right) {
				right = right->_right;
			}
			_node = right;
		}
		else {
			// ����
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && parent->_left == cur) {
				cur = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}

};

template<class K, class V, class KeyOfV> class RedBlackTree {
	typedef RedBlackTreeNode<V> Node;
public:
	typedef RedBlackTreeIterator<V, V&, V*> iterator;

	iterator begin() {
		Node* left = _root;
		while (left && left->_left) {
			left = left->_left;
		}
		return iterator(left);
	}

	iterator end() {
		return iterator(nullptr);
	}

	RedBlackTree() : _root(nullptr) {}

	RedBlackTree(const RedBlackTree<K, V, KeyOfV>& t) {
		_root = RedBlackTreeCopy(t._root);
	}

	RedBlackTree<K, V, KeyOfV>& operator=(RedBlackTree<K, V, KeyOfV>& t) {
		if (this != &t) {
			swap(_root, t._root);
		}
		return *this;
	}

	~RedBlackTree() {
		RedBlackTreeDestory(_root);
		_root = nullptr;
	}

	pair<iterator, bool> RedBlackTreeInsert(const V& val) {
		if (_root == nullptr) {
			_root = new Node(val);
			_root->_color = BLACK; // �����Ϊ��ɫ
			return make_pair(iterator(_root), true);;
		}

		KeyOfV kov;

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (kov(cur->_val) > kov(val)) {
				parent = cur;
				cur = cur->_left;
			}
			else if (kov(cur->_val) < kov(val)) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				return make_pair(iterator(cur), false);
			}
		}

		// �ҵ�����λ�� Ĭ�����ò�����Ϊ��ɫ
		cur = new Node(val);
		Node* returnVal = cur;
		cur->_color = RED;
		if (kov(cur->_val) < kov(parent->_val)) {
			parent->_left = cur;
		}
		else {
			parent->_right = cur;
		}
		cur->_parent = parent;

		// ����ƽ�� && ������ɫ
		while (parent && parent->_color == RED) {
			Node* grandparent = parent->_parent;
			// parent��grandparent����
			if (grandparent->_left == parent) {
				Node* uncle = grandparent->_right;
				// uncle������Ϊ��
				if (uncle && uncle->_color == RED) {
					// parent && uncle Ⱦ�� greandparentȾ��
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandparent->_color = RED;

					// ���ϵ���
					cur = grandparent;
					parent = cur->_parent;
				}
				else {
					// uncle�����ڻ���uncleΪ��
					if (cur == parent->_left) {
						// �ҵ��� parentȾ�� grandparentȾ��
						RotateR(grandparent);
						parent->_color = BLACK;
						grandparent->_color = RED;
					}
					else {
						// ����˫�� curȾ�� grandparentȾ��
						RotateL(parent);
						RotateR(grandparent);
						cur->_color = BLACK;
						grandparent->_color = RED;
					}
					break;
				}
			}
			else {
				// parent��grandparent�Һ��� �ԳƵ�
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
						// ����
						RotateL(grandparent);
						parent->_color = BLACK;
						grandparent->_color = RED;
					}
					else {
						// ����˫��
						RotateR(parent);
						RotateL(grandparent);
						cur->_color = BLACK;
						grandparent->_color = RED;
					}
					break;
				}
			}
		}
		// ����㱩��Ⱦ��
		_root->_color = BLACK;
		return make_pair(iterator(returnVal), true);
	}

	iterator RedBlackTreeFind(const K& key) {
		Node* cur = _root;
		KeyOfV kov;
		while (cur) {
			if (kov(cur->_val) > key) {
				cur = cur->_left;
			}
			else if (kov(cur->_val) < key) {
				cur = cur->_right;
			}
			else {
				return iterator(cur);
			}
		}
		return end();
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

	Node* RedBlackTreeCopy(Node* root) {
		if (root == nullptr) {
			return nullptr;
		}
		Node* newNode = new Node(root->_val);
		newNode->_color = root->_color;
		newNode->_left = RedBlackTreeCopy(root->_left);
		newNode->_right = RedBlackTreeCopy(root->_right);
		if (newNode->_left) newNode->_left->_parent = newNode;
		if (newNode->_right) newNode->_right->_parent = newNode;
		return newNode;
	}

	void RedBlackTreeDestory(Node* root) {
		if (root == nullptr)
			return;
		RedBlackTreeDestory(root->_left);
		RedBlackTreeDestory(root->_right);
		delete root;
	}

	Node* _root;
};