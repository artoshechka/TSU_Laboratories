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

		// ����������� ����� � ��������� �������������� ������
		string encodedData = encodeFile("text.txt", codes);
		if (encodedData.empty()) {
			cerr << "Failed to encode the file." << endl;
			return 1;
		}

		// ���������� ������� ����� �������� � �������������� ������ � ���� ����
		saveHuffmanCodesAndEncodedData(codes, encodedData, "encoded_file.bin");
		cout << "File has been encoded successfully." << endl;
	}
	else if (mark == 2) {
		// ������������� �����
		decodeFile("encoded_file.bin", "decoded_file.txt");
		cout << "File has been decoded successfully." << endl;
	}
	else {
		cout << "Invalid input." << endl;
		return 1;
	}

	return 0;
}
