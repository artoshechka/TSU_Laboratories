#include <stdio.h>

int main() {
    int Z;
    scanf("%d", &Z);
    for (int X = 1; X < Z; ++X) {
        for (int Y = 1; Y < Z; ++Y) {
            for (int n = 1; n < Z; ++n) {
                for (int k = 1; k < Z; ++k) {
                    int x = X;
                    int y = Y;
                    for (int i = 1; i < n; ++i) {
                        x *= x;
                    }
                    for (int i = 1; i < k; ++i) {
                        y *= y;
                    }
                    if (Z == x + y) {
                        printf("X %d n %d Y %d k %d \n", X, n, Y, k);
                    }
                }

            }
        }
    }
    return 0;
}