#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// Класс, представляющий узел бинарного дерева
class binaryTreeElement {
   public:
    int data;                           // Значение в узле
    binaryTreeElement *left = nullptr;  // Указатель на левого потомка
    binaryTreeElement *right = nullptr;  // Указатель на правого потомка

    // Конструктор, инициализирующий значение узла
    binaryTreeElement(int value) {
        left = nullptr;
        right = nullptr;
        data = value;
    }
};

// Класс, представляющий бинарное дерево
class binaryTree {
   private:
    binaryTreeElement *root;  // Указатель на корень дерева
    int size;  // Количество элементов дерева
    void deleteBinaryTree(binaryTreeElement *);

   public:
    // Конструктор, создающий дерево с заданным корневым значением
    binaryTree(int);
    ~binaryTree();  // Деструктор для удаления дерева
    bool find(int);  // Метод для поиска элемента в дереве
    void insert(int);  // Метод для вставки элемента в дерево
    void erase(int);  // Метод для удаления элемента из дерева
    binaryTreeElement *getRoot() {
        return root;
    }  // Метод для получения корня дерева
};

// Рекурсивная функция для удаления дерева
void binaryTree::deleteBinaryTree(binaryTreeElement *current) {
    if (current) {
        deleteBinaryTree(current->left);
        deleteBinaryTree(current->right);
        delete current;
    }
}

// Конструктор для бинарного дерева
binaryTree::binaryTree(int key) {
    root = new binaryTreeElement(key);
    size = 1;
}

// Деструктор для бинарного дерева
binaryTree::~binaryTree() { deleteBinaryTree(root); }

// Метод для поиска элемента в бинарном дереве
bool binaryTree::find(int key) {
    binaryTreeElement *current = root;
    while (current && current->data != key) {
        if (current->data > key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current != nullptr;
}

// Метод для вставки элемента в бинарное дерево
void binaryTree::insert(int key) {
    binaryTreeElement *current = root;
    while (current && current->data != key) {
        if (current->data > key && current->left == nullptr) {
            current->left = new binaryTreeElement(key);
            ++size;
            return;
        }
        if (current->data < key && current->right == nullptr) {
            current->right = new binaryTreeElement(key);
            ++size;
            return;
        }
        if (current->data > key)
            current = current->left;
        else
            current = current->right;
    }
}

// Метод для удаления элемента из бинарного дерева
void binaryTree::erase(int key) {
    binaryTreeElement *curr = root;
    binaryTreeElement *parent = nullptr;
    while (curr && curr->data != key) {
        parent = curr;
        if (curr->data > key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    if (!curr) return;
    if (curr->left == nullptr) {
        if (parent && parent->left == curr) parent->left = curr->right;
        if (parent && parent->right == curr) parent->right = curr->right;
        --size;
        delete curr;
        return;
    }
    if (curr->right == nullptr) {
        if (parent && parent->left == curr) parent->left = curr->left;
        if (parent && parent->right == curr) parent->right = curr->left;
        --size;
        delete curr;
        return;
    }
    binaryTreeElement *replace = curr->right;
    while (replace->left) replace = replace->left;
    int replace_value = replace->data;
    erase(replace_value);
    curr->data = replace_value;
}

// Функция для построения таблицы частот символов в файле
void buildFrequencyTable(const string &filename, vector<int> &frequency) {
    ifstream file(filename, ios::binary);
    char ch;
    while (file.get(ch)) frequency[ch]++;
    file.close();
}

// Функция для подсчета частоты символов в тексте
unordered_map<char, int> count_frequency(const string &text) {
    unordered_map<char, int> frequency;
    for (char c : text) {
        frequency[c]++;
    }
    return frequency;
}

// Функция для построения дерева Хаффмана
void buildHuffmanTree(const vector<int> &frequency, binaryTree &tree) {
    priority_queue<pair<int, binaryTreeElement *>,
                   vector<pair<int, binaryTreeElement *>>,
                   greater<pair<int, binaryTreeElement *>>>
        pq;
    for (int i = 0; i < 256; ++i) {
        if (frequency[i] > 0) {
            pq.push({frequency[i], new binaryTreeElement(i)});
        }
    }
    while (pq.size() > 1) {
        auto left = pq.top();
        pq.pop();
        auto right = pq.top();
        pq.pop();
        auto parent = new binaryTreeElement(-1);  // Внутренний узел
        parent->left = left.second;
        parent->right = right.second;
        pq.push({left.first + right.first, parent});
    }
    tree = binaryTree(-1);  // Пустое дерево
    if (!pq.empty()) tree.getRoot()->left = pq.top().second;  // Корень дерева Х
