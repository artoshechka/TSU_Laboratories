#include "Hufman.h"
int main() {
	// Выбор режима: кодирование или декодирование файла
	int mark;
	cout << "Enter 1 for encoding or 2 for decoding file: ";
	cin >> mark;

	// Выполнение соответствующего действия в зависимости от выбора
	if (mark == 1) {
		// Построение таблицы частот символов в файле
		unordered_map<unsigned char, int> frequency = buildFrequencyTable("text.txt");
		if (frequency.empty()) {
			cerr << "Failed to build frequency table." << endl;
			return 1;
		}

		// Построение дерева Хаффмана на основе таблицы частот
		BinaryTree tree;
		buildHuffmanTree(frequency, tree);

		// Генерация кодов Хаффмана для символов
		unordered_map<unsigned char, string> codes;
		generateCodes(tree.getRoot(), "", codes);

		// Сохранение таблицы кодов Хаффмана в файл
		saveHuffmanCodes(codes, "huffman_codes.bin");

		// Кодирование файла
		encodeFile("text.txt", "encoded_file.bin", codes);
		cout << "File has been encoded successfully." << endl;
	}
	else if (mark == 2) {
		// Декодирование файла
		decodeFile("encoded_file.bin", "decoded_file.txt", "huffman_codes.bin");
		cout << "File has been decoded successfully." << endl;
	}
	else {
		cout << "Invalid input." << endl;
		return 1;
	}

	return 0;
}
