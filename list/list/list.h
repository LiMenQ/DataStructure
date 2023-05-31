#pragma once
#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

namespace lmq {
	template<class T> struct ListNode {
		ListNode(const T& val = T()) :_next(nullptr), _prev(nullptr), _val(val) {}
		ListNode<T>* _next;
		ListNode<T>* _prev;
		T _val;
	};

	template<class T, class Ref, class Ptr> struct _list_iterator {
		typedef ListNode<T> Node;
		typedef _list_iterator<T, Ref, Ptr> self;
		_list_iterator(Node* node) :_node(node) {}

		Ref operator*() {
			return _node->_val;
		}

		Ptr operator->() {
			return &_node->_val;
		}

		self& operator++() {
			_node = _node->_next;
			return *this;
		}
		
		self operator++(int) {
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		self& operator--() {
			_node = _node->_prev;
			return *this;
		}

		self operator--(int) {
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		bool operator!=(const self& it) const{
			return _node != it._node;
		}

		bool operator==(const self& it) const {
			return _node == it._node;
		}

		Node* _node;
	};

	template<class Iterator, class Ref, class Ptr> class _reverse_iterator {
		typedef _reverse_iterator<Iterator, Ref, Ptr> self;
		/*typedef _reverse_interator<Iterator> self;
		typedef typename Iterator::reference Ref;
		typedef typename Iterator::pointer Ptr;*/
	public:
		_reverse_iterator(Iterator it) :_it(it) {}
		
		Ref operator*() {
			Iterator tmp = _it;
			return *--tmp;
		}

		Ptr operator->() {
			return &operator*();
		}

		self& operator++() {
			--_it;
			return *this;
		}

		self operator++(int) {
			self tmp(*this);
			--_it;
			return tmp;
		}

		self& operator--() {
			++_it;
			return *this;
		}

		self operator--(int) {
			self tmp(*this);
			++_it;
			return tmp;
		}

		bool operator!=(const self& rit) const {
			return _it != rit._it;
		}

		bool operator==(const self& rit) const {
			return _it == rit._it;
		}

	private:
		Iterator _it;
	};

	template<class T> class list{
		typedef ListNode<T> Node;
	public:
		typedef _list_iterator<T, T&, T*> iterator;
		typedef _list_iterator<T, const T&, const T*> const_iterator;
		typedef _reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef _reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;

		iterator begin() {
			return iterator(_head->_next);
		}

		iterator end() {
			return iterator(_head);
		}

		const_iterator begin() const {
			return const_iterator(_head->_next);
		}

		const_iterator end() const {
			return const_iterator(_head);
		}

		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(const_iterator(_head));
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(const_iterator(_head->_next));

		}

		list() {
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}

		list(int n, const int& val = 0) {
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
			for (int i = 0; i < n; ++i) {
				push_back(val);
			}
		}

		list(size_t n, const T& val = T()) {
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
			for (size_t i = 0; i < n; ++i) {
				push_back(val);
			}
		}

		template<class InputIterator> list(InputIterator begin, InputIterator end) {
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
			while (begin != end) {
				push_back(*begin);
				begin++;
			}
		}

		list(const list<T>& lt) {
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
			list<T> tmp(lt.begin(), lt.end());
			std::swap(_head, tmp._head);
		}

		list<T>& operator=(const list<T>& lt) {
			if (this != &lt) {
				list<T> tmp(lt);
				std::swap(_head, tmp._head);
			}
			return *this;
		}

		~list() {
			clear();
			delete _head;
			_head = nullptr;
		}

		void clear() {
			iterator pos = begin();
			while (pos != end()) {
				erase(pos++);
			}
		}

		void push_back(const T& x) {
			insert(end(), x);
		}

		void push_front(const T& x) {
			insert(begin(), x); 
		}

		void pop_back() {
			erase(--end());
		}

		void pop_front() {
			erase(begin());
		}

		iterator insert(iterator pos, const T& x) {
			Node* cur = pos._node;
			Node* newNode = new Node(x);
			cur->_prev->_next = newNode;
			newNode->_prev = cur->_prev;
			newNode->_next = cur;
			cur->_prev = newNode;
			return iterator(newNode);
		}

		iterator erase(iterator pos) {
			assert(pos != end());
			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;
			delete pos._node;
			prev->_next = next;
			next->_prev = prev;
			return iterator(next);
		}

	private:
		Node* _head;
	};
}