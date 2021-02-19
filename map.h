#pragma once
#include "node.h"
using namespace std;
#ifndef MAP_H
#define MAP_H
class map {
private:
	node* root;
public:
	map() {
		root = nullptr;
	}

	map(node* map_root_node) {
		root = map_root_node;
	}

	void insert(string node_key, int node_value) {
		node* parent, * grandParent;
		if (root == nullptr) {
			root = new node(node_key, node_value, nullptr, black);
		}
		else{
			node* newNode = new node(node_key, node_value, root);
			while (true) {
				if (newNode > newNode->getParent())  if (newNode->getParent()->getRightChild() != nullptr) newNode->setParent(newNode->getRightChild());
				else break;
				else if (newNode->getParent()->getLeftChild() != nullptr) newNode->setParent(newNode->getLeftChild());
				else break;
			}
			if (newNode > newNode->getParent()) newNode->getParent()->setRightChild(newNode);
			else newNode->getParent()->setLeftChild(newNode);
			while (!newNode->getParent()->isRed()) {
				parent = newNode->getParent();
				grandParent = parent->getParent();
				if (parent < grandParent) {
					if (grandParent->getRightChild()->isRed()) {
						grandParent->getLeftChild()->setColor(black);
						grandParent->getRightChild()->setColor(black);
						grandParent->setColor(red);
						newNode = grandParent;
					}
				}
			}
		}
	}
};
#endif