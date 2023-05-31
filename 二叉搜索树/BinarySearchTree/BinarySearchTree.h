#pragma once
#include <iostream>
using std::cout;
using std::endl;

template<class K> struct BSTreeNode {
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;
	BSTreeNode(const K& key = K()) : _left(nullptr), _right(nullptr), _key(key) {}
};

template<class K> class BSTree {
	typedef BSTreeNode<K> Node;
public:
	BSTree() : _root(nullptr) {}

	bool BSTreeInsert(const K& key) {
		if (_root == nullptr) {
			_root = new Node(key);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (cur->_key > key) {
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				return false;
			}
		}
		
		cur = new Node(key);

		if (parent->_key > key) {
			parent->_left = cur;
		}
		else {
			parent->_right = cur;
		}

		return true;
	}

	bool BSTreeErase(const K& key) {
		Node* parent = nullptr;
		Node* cur = _root;
		
		while (cur) {
			if (cur->_key > key) {
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				// ��ʼɾ��
				if (cur->_left == nullptr) {
					// ������Ϊ�գ����ӵ�������
					if (parent == nullptr) {
						_root = cur->_right;
					}
					else {
						if (parent->_left = cur) {
							parent->_left = cur->_right;
						}
						else {
							parent->_right = cur->_right;
						}
					}
					delete cur;
				}
				else if (cur->_right == nullptr) {
					// ������Ϊ�գ����ӵ�������
					if (parent == nullptr) {
						_root = cur->_left;
					}
					else {
						if (parent->_left = cur) {
							parent->_left = cur->_left;
						}
						else {
							parent->_right = cur->_left;
						}
					}
					delete cur;
				}
				else {
					// ������������Ϊ�գ��ҵ���������С�ģ��滻ɾ��
					Node* minParent = cur;
					Node* minChild = cur->_right;
					while (minChild->_left) {
						minParent = minChild;
						minChild = minChild->_left;
					}
					cur->_key = minChild->_key;
					
					if (minParent->_left == minChild) {
						minParent->_left = minChild->_right;
					}
					else {
						minParent->_right = minChild->_right;
					}
					delete minChild;
				}
				return true;
			}
		}
		return false;
	}

	void BSTreeInOrder() {
		_BSTreeInOrder(_root);
		cout << endl;
	}

	bool BSTreeFind(const K& key) {
		Node* cur = _root;
		while (cur) {
			if (cur->_key > key) {
				cur = cur->_left;
			}
			else if (cur->_key < key) {
				cur = cur->_right;
			}
			else {
				return true;
			}
		}
		return false;
	}

	bool BSTreeFindR(const K& key) {
		return _BSTreeFindR(_root, key);
	}

	bool BSTreeInsertR(const K& key) {
		return _BSTreeInsertR(_root, key);
	}

	bool BSTreeEraseR(const K& key) {
		return _BSTreeEraseR(_root, key);
	}

private:

	void _BSTreeInOrder(Node* _root) {
		if (_root == nullptr) return;
		_BSTreeInOrder(_root->_left);
		cout << _root->_key << " ";
		_BSTreeInOrder(_root->_right);
	}

	bool _BSTreeFindR(Node* root, const K& key) {
		if (root == nullptr) {
			return false;
		}
		if (root->_key > key) {
			return _BSTreeFindR(root->_left, key);
		}
		else if (root->_key < key) {
			return _BSTreeFindR(root->_right, key);
		}
		else {
			return true;
		}
	}

	bool _BSTreeInsertR(Node*& root,const K& key) {
		if (root == nullptr) {
			// �����λ�ò���
			// root��nullptr���߸��ڵ������
			root = new Node(key);
			return true;
		}

		if (root->_key > key) {
			return _BSTreeInsertR(root->_left, key);
		}
		else if (root->_key < key) {
			return _BSTreeInsertR(root->_right, key);
		}
		else {
			return false;
		}
	}

	bool _BSTreeEraseR(Node*& root, const K& key) {
		if (root == nullptr) {
			return false;
		}
		if (root->_key > key) {
			return _BSTreeEraseR(root->_left, key);
		}else if(root->_key < key){
			return _BSTreeEraseR(root->_right, key);
		}
		else {
			// ��ʼɾ��
			Node* del = root;
			if (root->_left == nullptr) {
				root = root->_right;
			}
			else if (root->_right == nullptr) {
				root = root->_left;
			}
			else {
				Node* minChild = root->_right;
				while (minChild->_left) {
					minChild = minChild->_left;
				}
				std::swap(minChild->_key, root->_key);
				return _BSTreeEraseR(root->_right, key);
			}
			delete del;
			return true;
		}
	}

	Node* _root;
};