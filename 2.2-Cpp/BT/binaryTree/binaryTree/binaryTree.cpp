﻿#include <iostream>

class Node {
	int key;
	Node* right;
	Node* left;
public:
	Node(int Key = 0, Node* Left = nullptr, Node* Right = nullptr) {
		key = Key;
		left = Left;
		right = Right;
	}
	~Node() {
		key = 0;
		left = nullptr;
		right = nullptr;
	}
	friend class BinaryTree;
};

class BinaryTree {
protected:
	Node* root;
	//добавление узла
	Node* addNode(Node*, Node*);
	//удаление дерева
	void deleteBinaryTree(Node*);
public:
	//конструкторы + деструктор
	BinaryTree() {
		root = nullptr;
	}
	BinaryTree(int length) {
		root = nullptr;
		for (int i = 0; i < length; ++i) {
			int tempValue = rand() % 100;
			this->addNode(tempValue);
		}
	}
	BinaryTree(int length, int* valueArray) {
		root = nullptr;
		for (int i = 0; i < length; ++i) {
			int tempValue = valueArray[i];
			this->addNode(tempValue);
		}
	}
	BinaryTree(const BinaryTree& otherTree) {
		root = addNode(root, otherTree.root);
	}
	~BinaryTree() {
		deleteBinaryTree(root);
	}

	//перегрузка оператора присваивания
	BinaryTree& operator = (const BinaryTree&);

	//поиск узла по ключу
	Node* findNodeByKey(int);

	//добавление узла
	void addNode(int value);

	//удаление узла
	Node* deleteNode();
};
Node* BinaryTree::addNode(Node* currentNode, Node* otherNode)
{
	if (!otherNode) {
		return nullptr;
	}
	currentNode = new Node(otherNode->key);
	currentNode->left = addNode(currentNode->left, otherNode->left);
	currentNode->right = addNode(currentNode->right, otherNode->right);
	return currentNode;
}

void BinaryTree::deleteBinaryTree(Node* node)
{
	if (node) {
		deleteBinaryTree(node->left);
		deleteBinaryTree(node->right);
		delete node;
	}
}

void BinaryTree::addNode(int value)
{
	if (root == nullptr) {
		root = new Node(value);
		return;
	}
	Node* node = root;
	while (node) {
		if (node->key > value && node->left == nullptr) {
			node->left = new Node(value);
			return;
		}
		else if (node->key <= value && node->right == nullptr) {
			node->right = new Node(value);
			return;
		}
		if (node->key > value) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
}

BinaryTree& BinaryTree::operator=(const BinaryTree& otherTree)
{
	if (this != &otherTree) {
		deleteBinaryTree(root);
		root = addNode(root, otherTree.root);
	}
	return *this;
}

Node* BinaryTree::findNodeByKey(int keyValue)
{
	if (root = nullptr) {
		return nullptr;
	}
	Node* currentNode = root;
	while (currentNode) {
		if (currentNode->key == keyValue) {
			return currentNode;
		}
		else if (currentNode->key > keyValue && currentNode->left == nullptr) {
			return nullptr;
		}
		else if (currentNode->key <= keyValue && currentNode->right == nullptr) {
			return nullptr;
		}
		if (currentNode->key > keyValue) {
			currentNode = currentNode->left;
		}
		else {
			currentNode = currentNode->right;
		}
	}
}
