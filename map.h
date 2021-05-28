#pragma once
#include "node.h"
using namespace std;
#ifndef MAP_H
#define MAP_H
template < class T1, class T2 >
class map {
private:
	node<T1, T2>* root;
public:
	map() {
		root = nullptr;
	}

	map(node<T1, T2>* map_root_node) {
		root = map_root_node;
	}

	void insert(T1 node_key, T2 node_value) {
		node<T1, T2>* newNode = new node(node_key, node_value, root);
		node<T1, T2>* y<T> = nullptr;
		node<T1, T2>* x = root;
		while (x != nullptr) {
			y = x;
			if (newNode < x) x = x->getLeftChild();
			else x = x->getRightChild();
		}
		newNode->setParent(y);
		if (y == nullptr) root = newNode;
		else if (newNode < y) y->setLeftChild(newNode);
		else y->setRightChild(newNode);
		fixup(newNode);
	}

	void fixup(node<T1, T2>* newNode) {
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
						newNode->leftRotation();
					}
					newNode->getParent()->setColor(black);
					newNode->getParent()->getParent()->setColor(red);
					newNode->getParent()->getParent()->rightRotation();
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
							newNode->rightRotation();
						}
						newNode->getParent()->setColor(black);
						newNode->getParent()->getParent()->setColor(red);
						newNode->getParent()->getParent()->leftRotation();
					}
				}
			}
		}
		root->setColor(black);
	}

	void remove(T1 remove_key) {
		
	}
};
#endif