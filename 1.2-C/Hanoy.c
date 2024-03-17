#include <stdio.h>
#include <malloc.h>

void printer(int **a, int size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", a[j][i]);
        }
        printf("\n");
    }
}

int emptyRow(int **a, int k, int size) {
    for (int i = size - 1; i >= 0; i--) {
        if (!a[k][i]) {
            return i;
        }
    }
    return -1;
}

void hanoi(int n, char A, char B, char C, int **a, int N) {
    if (n == 1) {

        int from_i = abs('A' - A);
        int from_j = emptyRow(a, from_i, N);
        if (from_j > 0 && from_j < N - 1)from_j++; else if (from_j != N - 1)from_j++;
        int to_i = 3 - abs('C' - C) - 1;
        int to_j = emptyRow(a, to_i, N);
        int t = a[from_i][from_j];
        a[from_i][from_j] = a[to_i][to_j];
        a[to_i][to_j] = t;
        printer(a, N);
        return;
    }
    hanoi(n - 1, A, C, B, a, N);

    int from_i = abs('A' - A);
    int from_j = emptyRow(a, from_i, N);
    if (from_j > 0 && from_j < N - 1)from_j++; else if (from_j != N - 1)from_j++;
    int to_i = 3 - abs('C' - C) - 1;
    int to_j = emptyRow(a, to_i, N);
    int t = a[from_i][from_j];
    a[from_i][from_j] = a[to_i][to_j];
    a[to_i][to_j] = t;
    printer(a, N);

    hanoi(n - 1, B, A, C, a, N);

}

int main() {
    int n = 0;
    printf("Enter number of disks -> ");
    scanf("%d", &n);
    int **masARR = (int **) malloc(3 * sizeof(int *));
    for (int i = 0; i < 3; i++) {
        masARR[i] = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            masARR[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++)masARR[0][i] = i + 1;
    printer(masARR, n);

    hanoi(n, 'A', 'B', 'C', masARR, n);
    return 0;

}