#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// �����, �������������� ���� ��������� ������
class BinaryTreeElement {
public:
	unsigned char data;
	BinaryTreeElement* left;
	BinaryTreeElement* right;

	// �����������, ���������������� �������� ����
	BinaryTreeElement(unsigned char value) : data(value), left(nullptr), right(nullptr) {}
};

// �����, �������������� �������� ������
class BinaryTree {
private:
	BinaryTreeElement* root;

	void deleteBinaryTree(BinaryTreeElement* current) {
		if (current) {
			deleteBinaryTree(current->left);
			deleteBinaryTree(current->right);
			delete current;
		}
	}

	// ��������������� ������� ��� ���������� ������������ ���� � ���������
	BinaryTreeElement* findMin(BinaryTreeElement* node) {
		while (node->left) {
			node = node->left;
		}
		return node;
	}

	// ��������������� ������� ��� ������������ �������� ����
	BinaryTreeElement* erase(BinaryTreeElement* node, unsigned char key) {
		if (!node) {
			return nullptr;
		}

		if (key < node->data) {
			node->left = erase(node->left, key);
		}
		else if (key > node->data) {
			node->right = erase(node->right, key);
		}
		else {
			if (!node->left) {
				BinaryTreeElement* temp = node->right;
				delete node;
				return temp;
			}
			else if (!node->right) {
				BinaryTreeElement* temp = node->left;
				delete node;
				return temp;
			}

			BinaryTreeElement* temp = findMin(node->right);
			node->data = temp->data;
			node->right = erase(node->right, temp->data);
		}
		return node;
	}

public:
	// ����������� �� ���������
	BinaryTree() : root(nullptr) {}

	// ����������
	~BinaryTree() { deleteBinaryTree(root); }

	// ������� ��������� ����� ������
	BinaryTreeElement* getRoot() const { return root; }

	// ��������� ������ �����
	void setRoot(BinaryTreeElement* newRoot) { root = newRoot; }

	// ����� �� �����
	bool find(unsigned char key) const {
		BinaryTreeElement* current = root;
		while (current && current->data != key) {
			current = (current->data > key) ? current->left : current->right;
		}
		return current != nullptr;
	}

	// ������� ����
	void insert(unsigned char key);

	// �������� ����
	void erase(unsigned char key);
};

// ����������� �������
void BinaryTree::insert(unsigned char key) {
	if (!root) {
		root = new BinaryTreeElement(key);
		return;
	}
	BinaryTreeElement* current = root;
	while (current) {
		if (current->data > key) {
			if (!current->left) {
				current->left = new BinaryTreeElement(key);
				return;
			}
			current = current->left;
		}
		else if (current->data < key) {
			if (!current->right) {
				current->right = new BinaryTreeElement(key);
				return;
			}
			current = current->right;
		}
		else {
			return;  // ���� ��� ����������
		}
	}
}

// ����������� ��������
void BinaryTree::erase(unsigned char key) {
	root = erase(root, key);
}

// ������� ��� ���������� ������� ������ �������� � �����
unordered_map<unsigned char, int> buildFrequencyTable(const string& filename) {
	ifstream file(filename, ios::binary);
	unordered_map<unsigned char, int> frequency;
	if (!file) {
		cerr << "Error opening file: " << filename << endl;
		return frequency;
	}

	unsigned char ch;
	while (file.get(reinterpret_cast<char&>(ch))) {
		frequency[ch]++;
	}
	return frequency;
}

// ������� ��� ���������� ������ ��������
void buildHuffmanTree(const unordered_map<unsigned char, int>& frequency, BinaryTree& tree) {
	priority_queue<pair<int, BinaryTreeElement*>, vector<pair<int, BinaryTreeElement*>>, greater<pair<int, BinaryTreeElement*>>> pq;
	for (const auto& pair : frequency) {
		pq.push({ pair.second, new BinaryTreeElement(pair.first) });
	}
	while (pq.size() > 1) {
		auto left = pq.top(); pq.pop();
		auto right = pq.top(); pq.pop();
		auto parent = new BinaryTreeElement(0);  // ���������� ����
		parent->left = left.second;
		parent->right = right.second;
		pq.push({ left.first + right.first, parent });
	}
	if (!pq.empty()) {
		tree.setRoot(pq.top().second);  // ������ ������ ��������
	}
}

// ������� ��� ��������� ����� �������� ��� ��������
void generateCodes(BinaryTreeElement* node, const string& code, unordered_map<unsigned char, string>& codes) {
	if (!node) return;
	if (!node->left && !node->right) {  // ���� ������
		codes[node->data] = code;
		return;
	}
	generateCodes(node->left, code + "0", codes);
	generateCodes(node->right, code + "1", codes);
}

// ������� ��� ���������� ������� ����� �������� � ����
void saveHuffmanCodes(const unordered_map<unsigned char, string>& codes, const string& filename) {
	ofstream codeFile(filename, ios::binary);
	if (!codeFile) {
		cerr << "Error opening code file." << endl;
		return;
	}

	size_t tableSize = codes.size();
	codeFile.write(reinterpret_cast<const char*>(&tableSize), sizeof(size_t));

	for (const auto& pair : codes) {
		codeFile.put(pair.first);
		size_t codeLength = pair.second.length();
		codeFile.write(reinterpret_cast<const char*>(&codeLength), sizeof(size_t));
		codeFile.write(pair.second.c_str(), codeLength);
	}

	codeFile.close();
}


// ������� ��� ����������� ����� � �������������� ������� �����
void encodeFile(const string& inputFilename, const string& outputFilename, const unordered_map<unsigned char, string>& codes) {
	ifstream inputFile(inputFilename, ios::binary);
	ofstream outputFile(outputFilename, ios::binary);

	if (!inputFile || !outputFile) {
		cerr << "Error opening input or output file." << endl;
		return;
	}

	unsigned char ch;
	string buffer;
	while (inputFile.get(reinterpret_cast<char&>(ch))) {
		auto it = codes.find(ch);
		if (it != codes.end()) {
			buffer += it->second;
			while (buffer.length() >= 8) {
				char byte = 0;
				for (int i = 0; i < 8; ++i) {
					byte <<= 1;
					byte |= buffer[i] - '0';
				}
				outputFile.put(byte);
				buffer = buffer.substr(8);
			}
		}
	}

	if (!buffer.empty()) {
		char byte = 0;
		for (size_t i = 0; i < buffer.length(); ++i) {
			byte <<= 1;
			byte |= buffer[i] - '0';
		}
		byte <<= (8 - buffer.length());
		outputFile.put(byte);
	}

	inputFile.close();
	outputFile.close();
}

// ������� ��� ������������� ����� � �������������� ������ �������� � ������� �����
void decodeFile(const string& inputFilename, const string& outputFilename, const string& codeFilename) {
	ifstream inputFile(inputFilename, ios::binary);
	ifstream codeFile(codeFilename, ios::binary);
	ofstream outputFile(outputFilename, ios::binary);


	if (!inputFile || !outputFile || !codeFile) {
		cerr << "Error opening input or output file." << endl;
		return;
	}

	// ������ ������ ������� �� ������ �����
	size_t tableSize;
	codeFile.read(reinterpret_cast<char*>(&tableSize), sizeof(size_t));

	// ������ ������� ����� �� �����
	unordered_map<string, unsigned char> inverseCodes;
	for (size_t i = 0; i < tableSize; ++i) {
		unsigned char symbol;
		codeFile.get(reinterpret_cast<char&>(symbol));
		size_t codeLength;
		codeFile.read(reinterpret_cast<char*>(&codeLength), sizeof(size_t));
		string codeBuffer(codeLength, ' ');
		codeFile.read(&codeBuffer[0], codeLength);
		inverseCodes[codeBuffer] = symbol;
	}

	string buffer;
	char ch;
	while (inputFile.get(ch)) {
		for (int i = 7; i >= 0; --i) {
			buffer += (ch & (1 << i)) ? '1' : '0';
			auto it = inverseCodes.find(buffer);
			if (it != inverseCodes.end()) {
				outputFile.put(it->second);
				buffer.clear();
			}
		}
	}

	inputFile.close();
	codeFile.close();
	outputFile.close();
}
