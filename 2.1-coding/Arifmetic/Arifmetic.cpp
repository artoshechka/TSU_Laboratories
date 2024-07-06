#include "Arifmetic.h"
int main() {
	cout << "Enter 1 for encoding or 2 for decoding file : ";
	int choice;
	cin >> choice;

	if (choice == 1) {
		string inputFilename = "text.txt";
		string outputFilename = "encoded.bin";
		string rangesFilename = "ranges.dat";

		double compression_ratio = encode(inputFilename, outputFilename, rangesFilename);
		cout << "Coef of compression: " << compression_ratio << endl;
	}
	else if (choice == 2) {
		string inputFilename = "encoded.bin";
		string outputFilename = "decoded.txt";
		string rangesFilename = "ranges.dat";

		if (decode(inputFilename, outputFilename, rangesFilename)) {
			cout << "decoded" << endl;
		}
		else {
			cerr << "Decoding error." << endl;
		}
	}
	else {
		cerr << "Invalid input." << endl;
	}

	return 0;
}
