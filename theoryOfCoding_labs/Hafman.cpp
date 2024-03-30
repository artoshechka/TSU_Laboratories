#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>

using namespace std;

// Класс, представляющий узел бинарного дерева
class binaryTreeElement
{
public:
    int data;                           // Значение в узле
    binaryTreeElement *left = nullptr;  // Указатель на левого потомка
    binaryTreeElement *right = nullptr; // Указатель на правого потомка

    // Конструктор, инициализирующий значение узла
    binaryTreeElement(int value)
    {
        left = nullptr;
        right = nullptr;
        data = value;
    }
};

// Класс, представляющий бинарное дерево
class binaryTree
{
private:
    binaryTreeElement *root; // Указатель на корень дерева
    int size;                // Количество элементов дерева
    void deleteBinaryTree(binaryTreeElement *);

public:
    // Конструктор, создающий дерево с заданным корневым значением
    binaryTree(int);
    ~binaryTree();                                // Деструктор для удаления дерева
    bool find(int);                               // Метод для поиска элемента в дереве
    void insert(int);                             // Метод для вставки элемента в дерево
    void erase(int);                              // Метод для удаления элемента из дерева
    binaryTreeElement *getRoot() { return root; } // Метод для получения корня дерева
};

// Рекурсивная функция для удаления дерева
void binaryTree::deleteBinaryTree(binaryTreeElement *current)
{
    if (current)
    {
        deleteBinaryTree(current->left);
        deleteBinaryTree(current->right);
        delete current;
    }
}

// Конструктор для бинарного дерева
binaryTree::binaryTree(int key)
{
    root = new binaryTreeElement(key);
    size = 1;
}

// Деструктор для бинарного дерева
binaryTree::~binaryTree()
{
    deleteBinaryTree(root);
}

// Метод для поиска элемента в бинарном дереве
bool binaryTree::find(int key)
{
    binaryTreeElement *current = root;
    while (current && current->data != key)
    {
        if (current->data > key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return current != nullptr;
}

// Метод для вставки элемента в бинарное дерево
void binaryTree::insert(int key)
{
    binaryTreeElement *current = root;
    while (current && current->data != key)
    {
        if (current->data > key && current->left == nullptr)
        {
            current->left = new binaryTreeElement(key);
            ++size;
            return;
        }
        if (current->data < key && current->right == nullptr)
        {
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
void binaryTree::erase(int key)
{
    binaryTreeElement *curr = root;
    binaryTreeElement *parent = nullptr;
    while (curr && curr->data != key)
    {
        parent = curr;
        if (curr->data > key)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    if (!curr)
        return;
    if (curr->left == nullptr)
    {
        if (parent && parent->left == curr)
            parent->left = curr->right;
        if (parent && parent->right == curr)
            parent->right = curr->right;
        --size;
        delete curr;
        return;
    }
    if (curr->right == nullptr)
    {
        if (parent && parent->left == curr)
            parent->left = curr->left;
        if (parent && parent->right == curr)
            parent->right = curr->left;
        --size;
        delete curr;
        return;
    }
    binaryTreeElement *replace = curr->right;
    while (replace->left)
        replace = replace->left;
    int replace_value = replace->data;
    erase(replace_value);
    curr->data = replace_value;
}

// Функция для построения таблицы частот символов в файле
void buildFrequencyTable(const string &filename, vector<int> &frequency)
{
    ifstream file(filename, ios::binary);
    char ch;
    while (file.get(ch))
        frequency[ch]++;
    file.close();
}

// Функция для построения дерева Хаффмана
void buildHuffmanTree(const vector<int> &frequency, binaryTree &tree)
{
    priority_queue<pair<int, binaryTreeElement *>, vector<pair<int, binaryTreeElement *>>, greater<pair<int, binaryTreeElement *>>> pq;
    for (int i = 0; i < 256; ++i)
    {
        if (frequency[i] > 0)
        {
            pq.push({frequency[i], new binaryTreeElement(i)});
        }
    }
    while (pq.size() > 1)
    {
        auto left = pq.top();
        pq.pop();
        auto right = pq.top();
        pq.pop();
        auto parent = new binaryTreeElement(-1); // Внутренний узел
        parent->left = left.second;
        parent->right = right.second;
        pq.push({left.first + right.first, parent});
    }
    tree = binaryTree(-1); // Пустое дерево
    if (!pq.empty())
        tree.getRoot()->left = pq.top().second; // Корень дерева Хаффмана
}

// Функция для генерации кодов Хаффмана для символов
void generateCodes(binaryTreeElement *node, string code, unordered_map<unsigned char, string> &codes)
{
    if (!node)
        return;
    if (node->data != -1)
    {
        codes[node->data] = code;
        return;
    }
    generateCodes(node->left, code + "0", codes);
    generateCodes(node->right, code + "1", codes);
}

// Функция для кодирования файла с использованием таблицы кодов
void encodeFile(const string &inputFilename, const string &outputFilename, const unordered_map<unsigned char, string> &codes)
{
    ifstream inputFile(inputFilename, ios::binary);
    ofstream outputFile(outputFilename, ios::binary);
    char ch;
    string buffer;
    while (inputFile.get(ch))
    {
        buffer += codes.at(ch);
        while (buffer.length() >= 8)
        {
            char byte = 0;
            for (int i = 0; i < 8; ++i)
            {
                byte <<= 1;
                byte |= buffer[i] - '0';
            }
            outputFile.put(byte);
            buffer = buffer.substr(8);
        }
    }
    if (!buffer.empty())
    {
        char byte = 0;
        for (size_t i = 0; i < buffer.length(); ++i)
        {
            byte <<= 1;
            byte |= buffer[i] - '0';
        }
        byte <<= (8 - buffer.length());
        outputFile.put(byte);
    }
    inputFile.close();
    outputFile.close();
}

// Функция для декодирования файла с использованием дерева Хаффмана
void decodeFile(const string &inputFilename, const string &outputFilename, binaryTree &tree)
{
    ifstream inputFile(inputFilename, ios::binary);
    ofstream outputFile(outputFilename, ios::binary);
    binaryTreeElement *current = tree.getRoot()->left; // Корень дерева Хаффмана
    char byte;
    while (inputFile.get(byte))
    {
        for (int i = 7; i >= 0; --i)
        {
            if (byte & (1 << i))
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
            if (current->data != -1)
            {
                outputFile.put(current->data);
                current = tree.getRoot()->left; // Сброс к корню
            }
        }
    }
    inputFile.close();
    outputFile.close();
}

int main()
{
    // Построение таблицы частот символов в файле
    vector<int> frequency(256, 0);
    buildFrequencyTable("file.txt", frequency);

    // Построение дерева Хаффмана на основе таблицы частот
    binaryTree tree(-1); // Пустое дерево
    buildHuffmanTree(frequency, tree);

    // Генерация кодов Хаффмана для символов
    unordered_map<unsigned char, string> codes;
    generateCodes(tree.getRoot()->left, "", codes); // Начиная с корня

    // Выбор режима: кодирование или декодирование файла
    int mark;
    cout << "Enter 1 for encoding or 2 for decoding file: ";
    cin >> mark;

    // Выполнение соответствующего действия в зависимости от выбора
    if (mark == 1)
    {
        encodeFile("file.txt", "encoded_file.bin", codes);
        cout << "File has been encoded successfully." << endl;
    }
    else if (mark == 2)
    {
        decodeFile("encoded_file.bin", "decoded_file.txt", tree);
        cout << "File has been decoded successfully." << endl;
    }
    else
    {
        cout << "Invalid input." << endl;
    }

    return 0;
}
