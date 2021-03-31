#pragma once
#include <string>
using namespace std;
#ifndef NODE_H
#define NODE_H
#define black false
#define red true
class node {
private:
	string key;
	int value;
	node* parent;
	bool color; // false - black, true - red
	node* left, * right;
public:
	node() {
		key = "";
		value = 0;
		parent = nullptr;
		color = red;
		left = nullptr;
		right = nullptr;
	}

	node(string node_key, int node_value, node* node_parent = nullptr, bool node_color = red, node* node_leftChild = nullptr, node* node_rightChild = nullptr) {
		key = node_key;
		value = node_value;
		parent = node_parent;
		color = node_color;
		left = node_leftChild;
		right = node_rightChild;
	}

	node& operator= (node equated_node) {
		key = equated_node.key;
		value = equated_node.value;
		parent = equated_node.parent;
		color = equated_node.color;
		left = equated_node.left;
		right = equated_node.right;
	}

	friend bool operator> (const node& firstCompared, const node& secondCompared) {
		return firstCompared.value > secondCompared.value;
	}

	friend bool operator< (const node& firstCompared, const node& secondCompared) {
		return firstCompared.value < secondCompared.value;
	}

	~node() {
		
	}

	void setParent(node* node_parent) {
		parent = node_parent;
	}

	node* getParent() {
		return parent;
	}

	void setLeftChild(node* leftChild) {
		left = leftChild;
	}

	node* getLeftChild() {
		return left;
	}

	void setRightChild(node* rightChild) {
		right = rightChild;
	}

	node* getRightChild() {
		return right;
	}

	bool isRed() {
		return color;
	}

	void setColor(bool node_color) {
		color = node_color;
	}

	void changeColor() {
		color = !color;
	}

	void leftRotation() {
		//changing parent`s child
		if (value > parent->value) parent->right = right;
		else parent->left = right;
		//changing lower node`s parent and left child
		right->parent = parent;
		right->left = this;
		//changing top node`s parent and right child
		parent = right;
		right = right->left;
		//set top node as parent of lower node`s left child
		right->parent = this;
	}

	void rightRotation() {
		if (value > parent->value) parent->right = left;
		else parent->left = left;

		left->parent = parent;
		left->right = this;

		parent = left;
		left = left->right;

		left->parent = this;
	}
};
#endif