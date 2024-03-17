#include <stdio.h>

int main() {
    int a, a1, b, b1, c, c1;
    printf("Enter coordinates of A =>");
    scanf("%d%d", &a, &a1);
    printf("Enter coordinates of B =>");
    scanf("%d%d", &b, &b1);
    printf("Enter coordinates of C =>");
    scanf("%d%d", &c, &c1);
    printf("Coordinates of D =>");
    if (a == b) {
        printf("%d ", c);
    } else if (a == c) {
        printf("%d ", b);
    }
    if (b1 == c1) {
        printf("%d", a1);
    } else if (b1 == a1) {
        printf("%d", c1);
    }

    return 0;

}