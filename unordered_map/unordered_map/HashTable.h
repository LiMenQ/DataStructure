#pragma once
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::string;

template<class T> struct HashNode {
	T _data;
	HashNode<T>* _next;
	HashNode(const T& data) : _data(data), _next(nullptr) {}
};

template<class K> struct HashCode {
	size_t operator()(const K& k) {
		return k;
	}
};

template<> struct HashCode<string> {
	size_t operator()(const string& s) {
		size_t res = 0;
		for (int i = 0; i < s.size(); i++) {
			res += res * 31 + s[i];
		}
	}
};

template<class K, class T, class KeyofT, class HashCode> class HashTable;

template<class K, class T, class Ref, class Ptr, class KeyofT, class HashCode> struct _HTIterator {
	typedef HashNode<T> Node;
	typedef _HTIterator<K, T, Ref, Ptr, KeyofT, HashCode> Self;	
	Node* _node;
	HashTable<K, T, KeyofT, HashCode>* _pt;
	_HTIterator(Node* node, HashTable<K, T, KeyofT, HashCode>* pt) : _node(node), _pt(pt) {}
	
	Ref operator*() {
		return _node->_data;
	}

	Ptr operator->() {
		return &_node->_data;
	}

	Self& operator++() {
		if (_node->_next)
			_node = _node->_next;
		else {
			KeyofT key;
			HashCode code;
			size_t index = code(key(_node->_data)) % _pt->_v.size();
			index = index + 1;
			while (index < _pt->_v.size()) {
				if (_pt->_v[index]) {
					break;
				}
				else {
					index++;
				}
			}
			if (index == _pt->_v.size()) {
				_node = nullptr;
			}
			else {
				_node = _pt->_v[index];
			}
		}
		return *this;
	}

	bool operator!=(const Self& s) {
		return _node != s._node;
	}

	bool operator==(const Self& s) {
		return _node == s._node;
	}
	
};

template<class K, class T, class KeyofT, class HashCode> class HashTable {
	typedef HashNode<T> Node;
	template<class K, class T, class Ref, class Ptr, class KeyofT, class HashCode> friend struct _HTIterator;
	typedef HashTable<K, T, KeyofT, HashCode> Self;
public:
	typedef _HTIterator<K, T, T&, T*, KeyofT, HashCode> iterator;
	HashTable() {
		_v.resize(10);
	}

	HashTable(const Self& self) {
		_v.resize(self._v.size());
		for (size_t i = 0; i < self._v.size(); i++) {
			Node* cur = self._v[i];
			while (cur) {
				Node* newNode = new Node(cur->_data);
				newNode->_next = _v[i];
				_v[i] = newNode;
				cur = cur->_next;
			}
		}
	}

	Self& operator=(Self self) {
		std::swap(_n, self._n);
		_v.swap(self._v);
		return *this;
	}

	~HashTable() {
		for (size_t i = 0; i < _v.size(); i++) {
			Node* cur = _v[i];
			while (cur) {
				Node* pnext = cur->_next;
				delete cur;
				cur = pnext;
			}
			_v[i] = nullptr;
		}
	}

	iterator begin() {
		for (size_t i = 0; i < _v.size(); i++) {
			if (_v[i]) {
				return iterator(_v[i], this);
			}
		}
		return end();
	}

	iterator end() {
		return iterator(nullptr, this);
	}

	bool HashTableErase(const K& key) {
		auto res = HashTableFind(key);
		if (res == end()) {
			return false;
		}

		HashCode code;
		KeyofT k;
		size_t index = code(key) % _v.size();
		Node* pre = nullptr, *cur = _v[index];
		while (cur) {
			if (k(cur->_data) == key) {
				if (pre == nullptr) {
					_v[index] = cur->_next;
				}
				else {
					pre->_next = cur->_next;
				}
				delete cur;
				_n--;
				return true;
			}
			pre = cur;
			cur = cur->_next;
		}
		return false;
	}

	iterator HashTableFind(const K& key) {
		HashCode code;
		KeyofT k;
		size_t index = code(key) % _v.size();
		Node* cur = _v[index];
		while (cur) {
			if (k(cur->_data) == key) {
				return iterator(cur, this);
			}
			cur = cur->_next;
		}
		return end();
	}

	pair<iterator, bool> HashTableInsert(const T& data) {

		KeyofT key;
		auto res = HashTableFind(key(data));
		if (res != end()) {
			return {res, false};
		}
		
		HashCode code;
		// 扩容
		if (_n == _v.size()) {
			size_t newSize = 2 * _v.size();
			vector<Node*> v(newSize);
			for (size_t i = 0; i < _v.size(); i++) {
				Node* cur = _v[i];
				while (cur) {
					Node* pnext = cur->_next;
					size_t newIndex = code(key(cur->_data)) % newSize;
					cur->_next = v[newIndex];
					v[newIndex] = cur;
					cur = pnext;
				}
				_v[i] = nullptr;
			}
			_v.swap(v);
		}
		size_t index = code(key(data)) % _v.size();
		Node* newNode = new Node(data);
		newNode->_next = _v[index];
		_v[index] = newNode;
		_n++;
		return {iterator(newNode, this), true};
	}

private:
	vector<Node*> _v;
	size_t _n = 0; // 真实数据个数
};