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
	return 0;
}
