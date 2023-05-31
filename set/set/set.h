#pragma once
#include "BlackRedTree.h"

namespace lmq {
	template<class K> class set {
	public:
		struct SetKeyOfV {
			const K& operator()(const K& k) {
				return k;
			}
		};

		typedef typename RedBlackTree<K, K, SetKeyOfV>::iterator iterator;

		iterator begin() {
			return _t.begin();
		}

		iterator end() {
			return _t.end();
		}

		pair<iterator, bool> insert(const K& key) {
			return _t.RedBlackTreeInsert(key);
		}

		iterator find(const K& key) {
			return _t.RedBlackTreeFind(key);
		}
		
	private:
		RedBlackTree<K, K, SetKeyOfV> _t;
	};
}