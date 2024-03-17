#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 1000


int main() {
    int C[N] = {0};
    int n;
    srand(time(NULL));
    scanf("%d", &n);
    int counter = 0;
    for (int *p = C; p < &C[n]; p++) {
        *p = rand() % 2;
        printf("%d ", *p);
        if (*p && *(p - 1) == 0 && p >= &C[2]) {
            ++counter;
        }
    }
    if (counter) printf("\nNear zero elements CAN be founded"); else printf("\nNear zero elements CAN'T be founded");
    return 0;
}

