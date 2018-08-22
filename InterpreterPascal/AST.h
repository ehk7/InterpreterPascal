#pragma once
template <class T> class Node {
public:
	T value();
	bool is_leaf();
	Node*parent();
	Node*leftmost_child();
	Node *right_sibling();
	void set_value(T&);
	void insert_first(Node<T>*);
	void insert_next(Node<T>*);
	void remove_first();
	void remove_next();
};

template <class T> class Tree {
public:
	void clear();
	Node<T> * root();
	void newroot(T&, Node<T>*, Node<T>*);
	void print();
};