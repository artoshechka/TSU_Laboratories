#include <iostream>
#include <iomanip> 
#include <queue>

using namespace std;

// класс узла дерева
class Node {
protected:
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

// класс бинарное дерево
class BinaryTree {
protected:
	Node* root;
	// добавление узла
	Node* addNode(Node*, Node*);
	// удаление дерева
	void deleteBinaryTree(Node*);

public:
	// конструкторы по умолчанию
	BinaryTree() {
		root = nullptr;
	}
	// конструктор по длине
	BinaryTree(int length) {
		root = nullptr;
		for (int i = 0; i < length; ++i) {
			int tempValue = rand() % 100;
			this->addNode(tempValue);
		}
	}
	// конструктор по массиву значений
	BinaryTree(int length, int* valueArray) {
		root = nullptr;
		for (int i = 0; i < length; ++i) {
			int tempValue = valueArray[i];
			this->addNode(tempValue);
		}
	}
	// конструктор копирования
	BinaryTree(const BinaryTree& otherTree) {
		root = addNode(root, otherTree.root);
	}
	// деструктор
	~BinaryTree() {
		deleteBinaryTree(root);
	}

	// перегрузка оператора присваивания
	BinaryTree& operator = (const BinaryTree&);

	// поиск узла по ключу
	Node* findNodeByKey(int);

	// добавление узла
	void addNode(int value);

	// удаление узла
	Node* deleteNode();

	// поиск минимума
	Node* findMin();

	// поиск максимума
	Node* findMax();

	// обход по уровням
	void levelOrderTraversal();

	// обход ЛПК (in-order)
	void inorderTraversal(Node* node);
	void inorderTraversal();

	// функция вывода дерева
	void printTree() {
		printTree(root, 0);
	}

private:
	// вспомогательная функция для вывода дерева
	void printTree(Node* node, int spaces) {
		if (node == nullptr) {
			return;
		}
		// Вывод правого поддерева с отступом
		printTree(node->right, spaces + 4);
		// Вывод узла с пробелами для отступа
		cout << setw(spaces) << " " << node->key << endl;
		// Вывод левого поддерева с отступом
		printTree(node->left, spaces + 4);
	}

	// остальные приватные члены класса...
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
	if (root == nullptr) {
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
	return nullptr; // не найден
}

Node* BinaryTree::findMin()
{
	if (root == nullptr) {
		return nullptr;
	}
	Node* currentNode = root;
	while (currentNode->left) {
		currentNode = currentNode->left;
	}
	return currentNode;
}

Node* BinaryTree::findMax()
{
	if (root == nullptr) {
		return nullptr;
	}
	Node* currentNode = root;
	while (currentNode->right) {
		currentNode = currentNode->right;
	}
	return currentNode;
}

void BinaryTree::levelOrderTraversal()
{
	if (root == nullptr) {
		return;
	}
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node* currentNode = q.front();
		q.pop();
		cout << currentNode->key << " ";
		if (currentNode->left) {
			q.push(currentNode->left);
		}
		if (currentNode->right) {
			q.push(currentNode->right);
		}
	}
	cout << endl;
}

void BinaryTree::inorderTraversal(Node* node)
{
	if (node == nullptr) {
		return;
	}
	inorderTraversal(node->left);
	cout << node->key << " ";
	inorderTraversal(node->right);
}

void BinaryTree::inorderTraversal()
{
	inorderTraversal(root);
	cout << endl;
}

int main() {
	int length;
	cout << "Enter the number of elements in the tree: ";
	cin >> length;

	int* values = new int[length];
	cout << "Enter the values for the tree elements:" << endl;
	for (int i = 0; i < length; ++i) {
		cout << "Element " << i + 1 << ": ";
		cin >> values[i];
	}

	BinaryTree tree(length, values);

	cout << "Level Order Traversal: ";
	tree.levelOrderTraversal();

	cout << "Inorder Traversal: ";
	tree.inorderTraversal();

	cout << "Tree Structure:" << endl;
	tree.printTree();

	return 0;
}
