#include "Arifmetic.h"

int main() {
    cout << "Enter 1 for encoding or 2 for decoding file: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        string inputFilename = "text.txt";
        string outputFilename = "encoded.bin";

        double compression_ratio = encode(inputFilename, outputFilename);
        cout << "Coefficient of compression: " << compression_ratio << endl;
    }
    else if (choice == 2) {
        string inputFilename = "encoded.bin";
        string outputFilename = "decoded.txt";

        if (decode(inputFilename, outputFilename)) {
            cout << "Decoded successfully." << endl;
        }
        else {
            decode(inputFilename, outputFilename);
            cerr << "Decoding error." << endl;
        }
    }
    else {
        cerr << "Invalid input." << endl;
    }

    return 0;
}
