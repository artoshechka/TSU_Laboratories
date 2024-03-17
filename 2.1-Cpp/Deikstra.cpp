#include <bits/stdc++.h>

using namespace std;

void printer(int *massiv, int n) {
    for (int i = 0; i < n; ++i) {
        cout << massiv[i] << " ";
    }
    cout << endl;
}

void invertor(int *massiv, int n, int k) {
    for (int i = k; i < n; ++i) {
        int temp = massiv[i];
        massiv[i] = massiv[n - 1 - (i - k)];
        massiv[n - 1 - (i - k)] = temp;
    }
}

void deikstr_alg(int *massiv, int n) {
    for (int i = n - 1; i > 0; --i) {
        if (massiv[i] > massiv[i - 1]) {
            for (int j = n - 1; j > 0; --j) {
                if (massiv[j] > massiv[i - 1] && j > i - 1) {
                    int temp = massiv[i - 1];
                    massiv[i - 1] = massiv[j];
                    massiv[j] = temp;
                    invertor(massiv, n, i + 1);
                    j = 0;
                    printer(massiv, n);
                    i = n - 1;
                }
            }
        }
    }
}


int main() {
    srand(time(NULL));
    int n, *array;
    n = rand() % 10;
    array = new int[n];
    for (int i = 0; i < n; ++i) {
        array[i] = rand() % 100;
    }
    printer(array, n);
    deikstr_alg(array, n);
    printer(array, n);
    delete array;
    return 0;
}