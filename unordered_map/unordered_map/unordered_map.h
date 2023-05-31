#pragma once
#include "HashTable.h"

namespace lmq {
	template<class K, class V, class hash = HashCode<K>> class unordered_map {
		struct MapKeyOfT {
			const K& operator()(const pair<K, V>& kv) {
				return kv.first;
			}
		};
	public:
		typedef typename HashTable<K, pair<K, V>, MapKeyOfT, hash>::iterator iterator;
		iterator begin() {
			return _table.begin();
		}

		iterator end() {
			return _table.end();
		}
		
		pair<iterator, bool> insert(const pair<K, V>& kv) {
			return _table.HashTableInsert(kv);
		}

		V& operator[](const K& key) {
			auto res = _table.HashTableInsert({key, V()});
			return res.first->second;
		}

		bool erase(const K& key) {
			return _table.HashTableErase(key);
		}

		iterator find(const K& key) {
			return _table.HashTableFind(key);
		}
		
	private:
		HashTable<K, pair<K, V>, MapKeyOfT, hash> _table;
	};
}