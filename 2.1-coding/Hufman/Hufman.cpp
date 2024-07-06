#include "Hufman.h"
int main() {
	// ����� ������: ����������� ��� ������������� �����
	int mark;
	cout << "Enter 1 for encoding or 2 for decoding file: ";
	cin >> mark;

	// ���������� ���������������� �������� � ����������� �� ������
	if (mark == 1) {
		// ���������� ������� ������ �������� � �����
		unordered_map<unsigned char, int> frequency = buildFrequencyTable("text.txt");
		if (frequency.empty()) {
			cerr << "Failed to build frequency table." << endl;
			return 1;
		}

		// ���������� ������ �������� �� ������ ������� ������
		BinaryTree tree;
		buildHuffmanTree(frequency, tree);

		// ��������� ����� �������� ��� ��������
		unordered_map<unsigned char, string> codes;
		generateCodes(tree.getRoot(), "", codes);

		// ���������� ������� ����� �������� � ����
		saveHuffmanCodes(codes, "huffman_codes.bin");

		// ����������� �����
		encodeFile("text.txt", "encoded_file.bin", codes);
		cout << "File has been encoded successfully." << endl;
	}
	else if (mark == 2) {
		// ������������� �����
		decodeFile("encoded_file.bin", "decoded_file.txt", "huffman_codes.bin");
		cout << "File has been decoded successfully." << endl;
	}
	else {
		cout << "Invalid input." << endl;
		return 1;
	}

	return 0;
}
