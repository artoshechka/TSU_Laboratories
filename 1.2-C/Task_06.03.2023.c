#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#define loop(i, a, n) for(int i=a;i<n;++i)

int gcd(int first, int second) {
    while (first && second) {
        if (first > second) {
            first %= second;
        } else {
            second %= first;
        }
    }
    return first + second;
}

void printer(int n, int *a, int *b, int *c) {
    loop(i, 0, n) {
        printf("a: %d b: %d c: %d \n------------------\n", a[i], b[i], c[i]);
    }
}


int main() {
    int *a, *b, *c;
    int n;
    srand(time(NULL));
    scanf("%d", &n);
    a = (int *) malloc(n * sizeof(int));
    b = (int *) malloc(n * sizeof(int));
    c = (int *) malloc(n * sizeof(int));
    loop(i, 0, n) {
        a[i] = rand() % 50;
        b[i] = rand() % 50;
        c[i] = gcd(a[i], b[i]);
    }
    printer(n, a, b, c);
    free(a);
    free(b);
    free(c);
    return 0;
}