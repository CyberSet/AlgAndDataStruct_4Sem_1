#pragma once
#include "node.h"
#include "list.h"
using namespace std;
#ifndef MAP_H
#define MAP_H
template < class T1, class T2 >
class map {
private:
	node<T1, T2>* nil = new node<T1, T2>();
	node<T1, T2>* root;
public:
	map() {
		nil->setColor(black);
		nil->setLeftChild(nil);
		nil->setRightChild(nil);
		nil->setParent(nil);
		root = nil;
	}

	map(node<T1, T2>* map_root_node) {
		root = map_root_node;
	}

	~map() {
		clear();
	}

	node<T1, T2>* getRoot() {
		return root;
	}

	void leftRotation(node<T1, T2>* x) {
		node<T1, T2>* y = x->getRightChild();
		x->setRightChild(y->getLeftChild());

		if (y->getLeftChild() != nil) y->getLeftChild()->setParent(x);
		if (y != nil) y->setParent(x->getParent());
		if (x->getParent() == nil && y != nil) root = y;
		else if (x == x->getParent()->getLeftChild()) x->getParent()->setLeftChild(y);
		else x->getParent()->setRightChild(y);
		y->setLeftChild(x);

		if (x != nil) x->setParent(y);
	}

	void rightRotation(node<T1, T2>* x) {
		node<T1, T2>* y = x->getLeftChild();
		x->setLeftChild(y->getRightChild());

		if (y->getRightChild() != nil) y->getRightChild()->setParent(x);
		if (y != nil) y->setParent(x->getParent());
		if (x->getParent() == nil && y != nil) root = y;
		else if (x == x->getParent()->getLeftChild()) x->getParent()->setLeftChild(y);
		else x->getParent()->setRightChild(y);
		y->setRightChild(x);

		if (x != nil) x->setParent(y);
	}

	void insert(T1 node_key, T2 node_value) {
		node<T1, T2>* newNode = new node<T1, T2>(node_key, node_value, root, nil, nil);
		node<T1, T2>* y = nil;
		node<T1, T2>* x = root;
		while (x != nil) {
			y = x;
			if (newNode < x) x = x->getLeftChild();
			else x = x->getRightChild();
		}
		newNode->setParent(y);
		if (y == nil) root = newNode;
		else if (&newNode < &y) y->setLeftChild(newNode);
		else y->setRightChild(newNode);
		insFixup(newNode);
	}

	void insFixup(node<T1, T2>* newNode) {
		node<T1, T2>* y = nullptr, * x = nullptr;
		while (newNode->getParent()->isRed()) {
			if (newNode->getParent() == newNode->getParent()->getParent()->getLeftChild()) {
				y = newNode->getParent()->getParent()->getRightChild();
				if (y->isRed()) {
					newNode->getParent()->setColor(black);
					y->setColor(black);
					newNode->getParent()->getParent()->setColor(red);
					newNode = newNode->getParent()->getParent();
				}
				else {
					if (newNode == newNode->getParent()->getRightChild()) {
						newNode = newNode->getParent();
						leftRotation(newNode);
					}
					newNode->getParent()->setColor(black);
					newNode->getParent()->getParent()->setColor(red);
					rightRotation(newNode->getParent()->getParent());
				}
			}
			else {
				if (newNode->getParent() == newNode->getParent()->getParent()->getRightChild()) {
					y = newNode->getParent()->getParent()->getLeftChild();
					if (y->isRed()) {
						newNode->getParent()->setColor(black);
						y->setColor(black);
						newNode->getParent()->getParent()->setColor(red);
						newNode = newNode->getParent()->getParent();
					}
					else {
						if (newNode == newNode->getParent()->getLeftChild()) {
							newNode = newNode->getParent();
							rightRotation(newNode);
						}
						newNode->getParent()->setColor(black);
						newNode->getParent()->getParent()->setColor(red);
						leftRotation(newNode->getParent()->getParent());
					}
				}
			}
		}
		root->setColor(black);
	}

	void delFixup(node<T1, T2>* removeNode) {
		node<T1, T2>*w = removeNode;
		while (removeNode != root && !removeNode->isRed()) {
			if (removeNode != removeNode->getParent()->getLeftChild()) {
				w = removeNode->getParent()->getRightChild();
				if (w->isRed()) {
					w->setColor(black);
					removeNode->getParent()->setColor(red);
					leftRotation(removeNode->getParent());
					w = removeNode->getParent()->getRightChild();
				}
				if (!w->getLeftChild()->isRed() && !w->getRightChild()->isRed()) {
					w->setColor(red);
					removeNode = removeNode->getParent();
				}
				else {
					if (!w->getRightChild()->isRed()) {
						w->getLeftChild()->setColor(black);
						w->setColor(red);
						rightRotation(w);
						w = removeNode->getParent()->getRightChild();
					}
					w->setColor(removeNode->getParent()->isRed());
					removeNode->getParent()->setColor(black);
					w->getRightChild()->setColor(black);
					leftRotation(removeNode->getParent());
					removeNode = root;
				}
			}
			else {
				w = removeNode->getParent()->getLeftChild();
				if (w->isRed()) {
					w->setColor(black);
					removeNode->getParent()->setColor(red);
					rightRotation(removeNode->getParent());
					w = removeNode->getParent()->getLeftChild();
				}
				if (!w->getRightChild()->isRed() && !w->getLeftChild()->isRed()) {
					w->setColor(red);
					removeNode = removeNode->getParent();
				}
				else {
					if (!w->getLeftChild()->isRed()) {
						w->getRightChild()->setColor(black);
						w->setColor(red);
						leftRotation(w);
						w = removeNode->getParent()->getLeftChild();
					}
					w->setColor(removeNode->getParent()->isRed());
					removeNode->getParent()->setColor(black);
					w->getLeftChild()->setColor(black);
					rightRotation(removeNode->getParent());
					removeNode = root;
				}
			}
		}
		removeNode->setColor(black);
	}

	node<T1, T2>* minimum(node<T1, T2>* x) {
		while (x->getLeftChild() != nil) {
			x = x->getLeftChild();
		}
		return x;
	}

	void transplant(node<T1, T2>* u, node<T1, T2>* v) {
		if (u->getParent() == nil) root = v;
		else
			if (u = u->getParent()->getLeftChild()) u->getParent()->setLeftChild(v);
			else u->getParent()->setRightChild(v);
		v->setParent(u->getParent());
	}

	void remove(T1 remove_key) {
		node<T1, T2>* removeNode = find(remove_key);
		if (removeNode != nil) {
			node<T1, T2>* y = removeNode;
			node<T1, T2>* x = nil;
			bool yOrigColor = y->isRed();
			if (removeNode->getLeftChild() == nil) {
				x = removeNode->getRightChild();
				transplant(removeNode, removeNode->getRightChild());
			}
			else {
				if (removeNode->getRightChild() == nil) {
					x = removeNode->getLeftChild();
					transplant(removeNode, removeNode->getLeftChild());
				}
				else {
					y = minimum(removeNode->getRightChild());
					yOrigColor = y->isRed();
					x = y->getRightChild();
					if (y->getParent() == removeNode) x->setParent(y);
					else {
						transplant(y, y->getRightChild());
						y->setRightChild(removeNode->getRightChild());
						y->getRightChild()->setParent(y);
					}
					transplant(removeNode, y);
					y->setLeftChild(removeNode->getLeftChild());
					y->getLeftChild()->setParent(y);
					y->setColor(removeNode->isRed());
				}
			}
			if (yOrigColor == black) delFixup(removeNode);
		}
	}

	node<T1, T2>* find(T1 node_key) {
		node<T1, T2>* findNode = root;
		while (findNode->getKey() != node_key && findNode != nil) {
			if (findNode->getKey() > node_key) findNode = findNode->getLeftChild();
			else findNode = findNode->getRightChild();
		}
		return findNode;
	}

	void print(){
		root->print(nil);
	}

	void clear() {
		while (root != nil) remove(root->getKey());
	}

	list<T1>* get_keys() {
		list<T1>* temp = new list<T1>();
		if(root != nil)get_keys(temp, root);
		return temp;
	}

	void get_keys(list<T1>* temp, node<T1, T2>*cur) {
		temp->push_back(cur->getKey());
		if (cur->getLeftChild() != nil) get_keys(temp, cur->getLeftChild());
		if (cur->getRightChild() != nil) get_keys(temp, cur->getRightChild());
	}

	list<T2>* get_values() {
		list<T2>* temp = new list<T1>();
		if (root != nil)get_values(temp, root);
		return temp;
	}

	void get_values(list<T2>* temp, node<T1, T2>* cur) {
		temp->push_back(cur->getValue());
		if (cur->getLeftChild() != nil) get_values(temp, cur->getLeftChild());
		if (cur->getRightChild() != nil) get_values(temp, cur->getRightChild());
	}
};
#endif