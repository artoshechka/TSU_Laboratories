#include "BigNumLib.h"

void test() {
	srand(time(NULL));
	int M = 1000;
	int T = 1000;

	bigNumber A;
	bigNumber B;
	bigNumber C;
	bigNumber D;

	do {
		int n = rand() % M + 1;
		int m = rand() % M + 1;

		bigNumber E(n, 1);
		bigNumber G(m, 1);

		A = E;

		B = G;

		C = A / B;
		D = A % B;

		cout << "m: " << m << " ";
		cout << "n: " << n << " ";
		cout << "T: " << T << endl;

	} while (A == C * B + D && A - D == C * B && D < B && --T);

	cout << T << endl;
}


using namespace std;
int main() {
	srand(time(NULL));
	test();

	/*bigNumber numA(3, 3);
	bigNumber numB;

	cout << "Enter a big number in hexadecimal format: ";
	numB.readHex();;

	cout << "A: ";
	numA.printHex();
	cout << endl
		<< "B: ";
	numB.printHex();
	cout << endl;

	if (numA == numB) {
		cout << "A is equal to B" << endl;
	}
	else {
		cout << "A is not equal to B" << endl;
	}

	if (numA < numB) {
		cout << "A is less than B" << endl;
	}
	else {
		cout << "A is not less than B" << endl;
	}

	if (numA > numB) {
		cout << "A is greater than B" << endl;
	}
	else {
		cout << "A is not greater than B" << endl;
	}

	bigNumber numC = numA + numB;
	cout << "Summary: ";
	numC.printHex();

	cout << "\nSubtraction: ";
	numC -= numB;
	numC.printHex();

	// Ввод целого числа
	int intNum;
	cout << "\nEnter an integer number: ";
	cin >> intNum;

	// Проверка умножения на целое число
	bigNumber numD = numA * intNum;
	cout << "\nMultiplication by integer: ";
	numD.printHex();

	// Проверка умножения на bigNumber
	bigNumber numE = numA * numB;
	cout << "\nMultiplication by BigNumber: ";
	numE.printHex();

	// Проверка деления на целое число
	bigNumber numF = numD / intNum;
	cout << "\nDevision by integer: ";
	numF.printHex();

	// Проверка остатка деления на число
	bigNumber numG = numD % intNum;
	cout << "\nThe remainder of the division by integer: ";
	numG.printHex();

	// Проверка деления

	numF = numE / numB;
	cout << "\nDevision by bigNumber: ";
	numF.printHex();

	// Проверка остатка деления
	numG = numE % numB;
	cout << "\nThe remainder of the division by BigNumber: ";
	numG.printHex();*/

	return 0;
}