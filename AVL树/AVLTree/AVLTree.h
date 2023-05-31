#pragma once
#include <iostream>
using std::cout;
using std::endl;
using std::pair;

template<class K, class V> struct AVLTreeNode {
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	int _bf;  // ƽ������
	AVLTreeNode(const pair<K,V>& kv) 
		: _left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv), _bf(0) {}
};

template<class K, class V> class AVLTree {
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree(): _root(nullptr) {}

	bool AVLTreeInsert(const pair<K, V>& kv) {
		if (_root == nullptr) {
			_root = new Node(kv);
			return true;
		}
		
		// ��������
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

		cur = new Node(kv);
		if (parent->_kv.first > kv.first) {
			parent->_left = cur;
		}
		else {
			parent->_right = cur;
		}

		cur->_parent = parent;

		// ����ƽ������
		while (parent) {
			if (parent->_left == cur) {
				parent->_bf--;
			}
			else {
				parent->_bf++;
			}

			// ƽ������Ϊ0, ����Ӱ�����Ƚ��
			// ƽ������Ϊ1 -1, �������ϵ���
			// ƽ������Ϊ-2 2, ��ת
			if (parent->_bf == 0) {
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1) {
				cur = parent;
				parent = parent->_parent;
			}
			else {
				// �ҵ���
				if (parent->_bf == -2 && cur->_bf == -1) {
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == 1) {
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1) {
					RotateLR(parent);
				}
				else if(parent->_bf == 2 && cur->_bf == -1) {
					RotateRL(parent);
				}

				break;
			}
		}
		return true;
	}

	bool AVLTreeFind(const K& key) {
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

	void AVLTreeInorder() {
		_AVLTreeInorder(_root);
		cout << endl;
	}

	int AVLTreeHeight() {
		return _AVLTreeHeight(_root);
	}

	bool AVLTreeBalance() {
		return _AVLTreeBalance(_root);
	}

private:
	
	// �ҵ��� 1.��cur->right���parent����� 2.��cur���Ҹ���Ϊparent
	void RotateR(Node* parent) {
		
		Node* cur = parent->_left;
		Node* curR = cur->_right;

		parent->_left = curR;
		if (curR) {
			curR->_parent = parent;
		}

		cur->_right = parent;
		Node* pcur = parent->_parent;
		parent->_parent = cur;

		if (pcur == nullptr) {
			_root = cur;
			cur->_parent = nullptr;
		}
		else {
			if (pcur->_left == parent) {
				pcur->_left = cur;
			}
			else {
				pcur->_right = cur;
			}
			cur->_parent = pcur;
		}

		// ����ƽ������
		cur->_bf = 0, parent->_bf = 0;
	}

	// ���� ��cur->left���parent���ұ� cur�������Ϊparent
	void RotateL(Node* parent) {
		Node* cur = parent->_right;
		Node* curL = cur->_left;
		
		parent->_right = curL;
		if (curL) {
			curL->_parent = parent;
		}

		Node* pcur = parent->_parent;
		cur->_left = parent;
		parent->_parent = cur;

		if (pcur == nullptr) {
			_root = cur;
			cur->_parent = nullptr;
		}
		else {
			if (pcur->_left == parent) {
				pcur->_left = cur;
			}
			else {
				pcur->_right = cur;
			}
			cur->_parent = pcur;
		}
		
		cur->_bf = 0, parent->_bf = 0;
	}

	void RotateLR(Node* parent) {
		Node* curL = parent->_left;
		Node* curLR = curL->_right;
		int bf = curLR->_bf;
		RotateL(parent->_left);
		RotateR(parent);

		if (bf == 1) {
			parent->_bf = 0;
			curL->_bf = -1;
			curLR->_bf = 0;
		}
		else if (bf == -1) {
			parent->_bf = 1;
			curL->_bf = 0;
			curLR->_bf = 0;
		}
		else if (bf == 0) {
			parent->_bf = 0;
			curL->_bf = 0;
			curLR->_bf = 0;
		}
			
	}

	void RotateRL(Node* parent) {
		Node* curR = parent->_right;
		Node* curRL = curR->_left;
		int bf = curRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);	
		
		if (bf == 1) {
			parent->_bf = -1;
			curR->_bf = 0;
			curRL->_bf = 0;
		}
		else if (bf == -1) {
			parent->_bf = 0;
			curR->_bf = 1;
			curRL->_bf = 0;
		}
		else if(bf == 0) {
			parent->_bf = 0;
			curR->_bf = 0;
			curRL->_bf = 0;
		}
	}

	void _AVLTreeInorder(Node* root) {
		if (root == nullptr) return;
		_AVLTreeInorder(root->_left);
		cout << root->_kv.first << "-" << root->_kv.second << " ";
		_AVLTreeInorder(root->_right);
	}

	int _AVLTreeHeight(Node* root) {
		if (root == nullptr) return 0;
		return 1 + std::max(_AVLTreeHeight(root->_left), _AVLTreeHeight(root->_right));
	}

	bool _AVLTreeBalance(Node* root) {
		if (root == nullptr) return true;
		int leftHight = _AVLTreeHeight(root->_left);
		int rightHight = _AVLTreeHeight(root->_right);
		int res = rightHight - leftHight;
		if (res != root->_bf) {
			cout << root->_kv.first << "ƽ������Ϊ" << root->_bf << endl;
			cout << root->_kv.first << "ƽ������Ӧ��Ϊ" << res << endl;
		}
		return std::abs(res) < 2 && _AVLTreeBalance(root->_left) && _AVLTreeBalance(root->_right);
	}

	Node* _root;	
};