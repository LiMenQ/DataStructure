#pragma once
#include "RedBlackTree.h"

namespace lmq {
	template<class K, class V> class map {
	public:
		struct MapKeyOfV {
			const K& operator()(const pair<K, V>& kv) {
				return kv.first;
			}
		};

		typedef typename RedBlackTree<K, pair<K, V>, MapKeyOfV>::iterator iterator;

		iterator begin() {
			return _t.begin();
		}

		iterator end() {
			return _t.end();
		}
		
		pair<iterator, bool> insert(const pair<K, V>& kv) {
			return _t.RedBlackTreeInsert(kv);
		}

		iterator find(const K& key) {
			return _t.RedBlackTreeFind(key);
		}

		V& operator[](const K& key) {
			pair<iterator, bool> res = _t.RedBlackTreeInsert(make_pair(key, V()));
			return res.first->second;
		}

	private:
		RedBlackTree<K, pair<K, V>, MapKeyOfV> _t;
	};
}
