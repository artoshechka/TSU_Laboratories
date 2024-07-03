#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

// Класс узла дерева
class Node {
protected:
	int key;      // Ключ узла
	Node* left;   // Указатель на левое поддерево
	Node* right;  // Указатель на правое поддерево

public:
	Node(int Key = 0, Node* Left = nullptr, Node* Right = nullptr)
		: key(Key), left(Left), right(Right) {}

	~Node() {
		left = nullptr;
		right = nullptr;
	}

	friend class BinaryTree;
};

// Класс бинарного дерева
class BinaryTree {
protected:
	Node* root; // Корень дерева

	// Вспомогательная функция для добавления узла
	Node* addNode(Node*, Node*);
	// Вспомогательная функция для удаления дерева
	void deleteBinaryTree(Node*);

	// Вспомогательная функция для удаления по значению
	Node* deleteByValue(Node*, int);

	// Вспомогательная функция для поиска минимального значения в поддереве
	Node* findMin(Node*);

	// Вспомогательная функция для поиска максимального значения в поддереве
	Node* findMax(Node*);

public:
	BinaryTree() : root(nullptr) {}

	BinaryTree(int length) : root(nullptr) {
		for (int i = 0; i < length; ++i) {
			int tempValue = rand() % 100;
			this->addNode(tempValue);
		}
	}

	BinaryTree(int length, int* valueArray) : root(nullptr) {
		for (int i = 0; i < length; ++i) {
			this->addNode(valueArray[i]);
		}
	}

	BinaryTree(const BinaryTree& otherTree) : root(nullptr) {
		root = addNode(root, otherTree.root);
	}

	~BinaryTree() {
		deleteBinaryTree(root);
	}

	BinaryTree& operator=(const BinaryTree&);

	// Функция поиска узла по ключу
	Node* findNodeByKey(int);

	// Функция добавления узла
	void addNode(int value);

	// Функция удаления узла по ключу
	void deleteByKey(int value);

	// Функция удаления узла по указателю
	void deleteNode(Node* node);

	// Функция поиска минимального узла
	Node* findMin();

	// Функция поиска максимального узла
	Node* findMax();

	// Функция вывода дерева
	void printTree() {
		printTree(root, 0);
	}

	// Обход в ширину (уровневый)
	void levelOrderTraversal();

	// Префиксный обход (корень-лево-право)
	void preOrderTraversal();

private:
	// Вспомогательная функция для вывода дерева
	void printTree(Node* node, int spaces);

	// Вспомогательная функция для префиксного обхода
	void preOrderTraversal(Node* node);
};

// Вспомогательная функция для добавления узла
Node* BinaryTree::addNode(Node* currentNode, Node* otherNode) {
	if (!otherNode) {
		return nullptr;
	}
	currentNode = new Node(otherNode->key);
	currentNode->left = addNode(currentNode->left, otherNode->left);
	currentNode->right = addNode(currentNode->right, otherNode->right);
	return currentNode;
}

// Вспомогательная функция для удаления дерева
void BinaryTree::deleteBinaryTree(Node* node) {
	if (node) {
		deleteBinaryTree(node->left);
		deleteBinaryTree(node->right);
		delete node;
	}
}

// Функция добавления узла по значению
void BinaryTree::addNode(int value) {
	if (root == nullptr) {
		root = new Node(value);
		return;
	}
	Node* node = root;
	while (node) {
		if (value < node->key && node->left == nullptr) {
			node->left = new Node(value);
			return;
		}
		else if (value >= node->key && node->right == nullptr) {
			node->right = new Node(value);
			return;
		}
		node = (value < node->key) ? node->left : node->right;
	}
}

// Перегрузка оператора присваивания
BinaryTree& BinaryTree::operator=(const BinaryTree& otherTree) {
	if (this != &otherTree) {
		deleteBinaryTree(root);
		root = addNode(root, otherTree.root);
	}
	return *this;
}

// Функция поиска узла по ключу
Node* BinaryTree::findNodeByKey(int keyValue) {
	Node* currentNode = root;
	while (currentNode) {
		if (currentNode->key == keyValue) {
			return currentNode;
		}
		currentNode = (keyValue < currentNode->key) ? currentNode->left : currentNode->right;
	}
	return nullptr;
}

// Вспомогательная функция для поиска минимального значения в поддереве
Node* BinaryTree::findMin(Node* node) {
	while (node && node->left) {
		node = node->left;
	}
	return node;
}

// Вспомогательная функция для поиска максимального значения в поддереве
Node* BinaryTree::findMax(Node* node) {
	while (node && node->right) {
		node = node->right;
	}
	return node;
}

// Функция поиска минимального узла
Node* BinaryTree::findMin() {
	return findMin(root);
}

// Функция поиска максимального узла
Node* BinaryTree::findMax() {
	return findMax(root);
}

// Функция удаления узла по ключу
void BinaryTree::deleteByKey(int value) {
	root = deleteByValue(root, value);
}

// Вспомогательная функция для удаления узла по значению
Node* BinaryTree::deleteByValue(Node* node, int value) {
	if (!node) {
		return nullptr;
	}

	if (value < node->key) {
		node->left = deleteByValue(node->left, value);
	}
	else if (value > node->key) {
		node->right = deleteByValue(node->right, value);
	}
	else {
		if (!node->left) {
			Node* temp = node->right;
			delete node;
			return temp;
		}
		else if (!node->right) {
			Node* temp = node->left;
			delete node;
			return temp;
		}

		Node* temp = findMin(node->right);
		node->key = temp->key;
		node->right = deleteByValue(node->right, temp->key);
	}
	return node;
}

// Функция удаления узла по указателю
void BinaryTree::deleteNode(Node* node) {
	root = deleteByValue(root, node->key);
}

// Вспомогательная функция для вывода дерева
void BinaryTree::printTree(Node* node, int spaces) {
	if (node == nullptr) {
		return;
	}
	printTree(node->right, spaces + 4);
	cout << setw(spaces) << " " << node->key << endl;
	printTree(node->left, spaces + 4);
}

// Обход в ширину (уровневый)
void BinaryTree::levelOrderTraversal() {
	if (root == nullptr) {
		return;
	}
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node* current = q.front();
		q.pop();
		cout << current->key << " ";
		if (current->left) {
			q.push(current->left);
		}
		if (current->right) {
			q.push(current->right);
		}
	}
	cout << endl;
}

// Префиксный обход (корень-лево-право)
void BinaryTree::preOrderTraversal() {
	preOrderTraversal(root);
	cout << endl;
}

// Вспомогательная функция для префиксного обхода
void BinaryTree::preOrderTraversal(Node* node) {
	if (node == nullptr) {
		return;
	}
	preOrderTraversal(node->left);
	preOrderTraversal(node->right);
	cout << node->key << " ";
}

int main() {
	srand(time(NULL));
	//8 11 2 15 19 13 12 7 10 18
	int length;
	cout << "Enter num of Nodes: ";
	cin >> length;

	int* values = new int[length];
	cout << "Enter Node values:" << endl;
	for (int i = 0; i < length; ++i) {
		cout << "Elem: " << i + 1 << ": ";
		cin >> values[i];
	}

	BinaryTree tree(length,values);

	cout << "Start tree structure:" << endl;
	tree.printTree();

	// Добавление нового элемента
	int newValue;
	cout << "Enter value of Node to add: ";
	cin >> newValue;
	tree.addNode(newValue);

	cout << "Tree after deleting Node " << newValue << ":" << endl;
	tree.printTree();

	// Удаление элемента по значению
	int keyToDelete;
	cout << "Enter valye of Node to delete: ";
	cin >> keyToDelete;
	tree.deleteByKey(keyToDelete);

	cout << "Tree with deleted Node " << keyToDelete << ":" << endl;
	tree.printTree();

	// Обход в ширину (уровневый)
	cout << "Level Order Traversal: ";
	tree.levelOrderTraversal();

	// Префиксный обход (корень-лево-право)
	cout << "Prefix Traversal: ";
	tree.preOrderTraversal();

	//delete[] values;
	return 0;
}
