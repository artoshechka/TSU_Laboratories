#include <stdio.h>
#include <math.h>

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("P -> %d \n", 2 * (a + b));
    printf("S -> %d \n", a * b);
    printf("d -> %f \n", sqrt(a * a + b * b));
    return 0;
    }