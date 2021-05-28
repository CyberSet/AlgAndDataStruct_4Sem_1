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
			node* y = nullptr;
			node* x = root;
			while()
		}
	}
};
#endif