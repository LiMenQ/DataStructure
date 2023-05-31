#pragma once
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::string;

namespace CloseHash {
	enum Status {
		EXIST,
		EMPTY,
		DELETE
	};

	template<class K, class V> struct HashData {
		pair<K, V> _kv;
		Status _status = EMPTY;
	};

	template<class K> struct HashCode {
		size_t operator()(const K& k) {
			return k;
		}
	};

	// 特化
	template<> struct HashCode<string> {
		size_t operator()(const string& s) {
			size_t res = 0;
			for (int i = 0; i < s.size(); i++) {
				res += res * 31 + s[i];	
			}
			return res;
		}
	};

	template<class K, class V, class HashCode = HashCode<K>> class HashTable {
	public:
		HashTable() {
			_v.resize(10, HashData<K, V>());
		}

		bool HashTableErase(const K& key) {
			HashData<K, V>* res = HashTableFind(key);
			if (res == nullptr) {
				return false;
			}
			res->_status = DELETE;
			_n--;
			return true;
		}
		
		HashData<K, V>* HashTableFind(const K& key) {
			HashCode code;
			size_t start = code(key);
			size_t i = 1;
			while (_v[start]._status != EMPTY) {
				if (_v[start]._kv.first == key && _v[start]._status != DELETE) {
					return &_v[start];
				}
				start = start + i * i;
				i++;
				start %= _v.size();
			}
			return nullptr;
		}

		bool HashTableInsert(const pair<K, V>& data) {

			HashData<K, V>* res = HashTableFind(data.first);
			if (res != nullptr) {
				return false;
			}

			if (_n * 10 / _v.size() > 7) {
				// 负载因子大于0.7扩容
				size_t newSize = 2 * _v.size();
				HashTable<K, V, HashCode> newHS;
				newHS._v.resize(newSize, HashData<K, V>());
				for (size_t i = 0; i < _v.size(); i++) {
					newHS.HashTableInsert(_v[i]._kv);
				}
				_v.swap(newHS._v);
			}

			HashCode code;
			// 除留余数法
			size_t start = code(data.first) % _v.size();
			size_t i = 1;
			while (_v[start]._status == EXIST) {
				// 二次探测法
				start = start + i * i;
				i++;
				start %= _v.size();
			}
			_v[start]._kv = data;
			_v[start]._status = EXIST;
			_n++;
			return true;
		}

	private:
		vector<HashData<K, V>> _v;
		size_t _n = 0;  // 真实数据个数
	};
}

namespace OpenHash {
	template<class K, class V> struct HashNode {
		pair<K, V> _kv;
		HashNode<K, V>* _next;
		HashNode(const pair<K, V>& kv) : _kv(kv), _next(nullptr) {}
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

	template<class K, class V, class HashCode = HashCode<K>> class HashTable {
		typedef HashNode<K, V> Node;
	public:
		HashTable() {
			_v.resize(10);
		}

		bool HashTableErase(const K& key) {
			if (HashTableFind(key) == nullptr) {
				return false;
			}

			HashCode code;
			size_t index = code(key) % _v.size();
			Node* pre = nullptr, *cur = _v[index];
			while (cur) {
				if (cur->_kv.first == key) {
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

		Node* HashTableFind(const K& key) {
			
			HashCode code;
			size_t index = code(key) % _v.size();
			Node* cur = _v[index];
			while (cur) {
				if (cur->_kv.first == key) {
					return cur;
				}
				cur = cur->_next;
			}
			return nullptr;
		}

		bool HashTableInsert(const pair<K, V>& kv) {
			
			if (HashTableFind(kv.first)) {
				return false;
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
						size_t newIndex = code(cur->_kv.first) % newSize;
						cur->_next = v[newIndex];
						v[newIndex] = cur;
						cur = pnext;
					}
					_v[i] = nullptr;
				}
				_v.swap(v);
			}

			size_t index = code(kv.first) % _v.size();
			Node* newNode = new Node(kv);
			newNode->_next = _v[index];
			_v[index] = newNode;
			_n++;
			return true;
		}
	
	private:
		vector<Node*> _v;
		size_t _n = 0; // 真实数据个数
	};

}