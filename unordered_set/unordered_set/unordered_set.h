#pragma once
#include "HashTable.h"

namespace lmq {
	template<class K, class hash = HashCode<K>> class unordered_set {
		struct SetKeyOfT {
			const K& operator()(const K& key) {
				return key;
			}
		};
	public:
		typedef typename HashTable<K, K, SetKeyOfT, hash>::iterator iterator;
		iterator begin() {
			return _table.begin();
		}

		iterator end() {
			return _table.end();
		}

		pair<iterator, bool> insert(const K& key) {
			return _table.HashTableInsert(key);
		}

		bool erase(const K& key) {
			return _table.HashTableErase(key);
		}

		iterator find(const K& key) {
			return _table.HashTableFind(key);
		}

	private:
		HashTable<K, K, SetKeyOfT, hash> _table;
	};
}