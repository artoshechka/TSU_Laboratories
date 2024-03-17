#include <stdio.h>

int main() {
    int a, b, c;
    printf("Input 3 number to find the nearest to A(1st number)\nThey need to be different\n");
    scanf("%d%d%d", &a, &b, &c);
    if (a < b && b < c) {
        printf("B is nearer to A \nTheir distance is %d", b - a);
    } else if (a < c && c < b) {
        printf("C is nearer to A \nTheir distance is %d", c - a);
    } else printf("Your input isn't correct");
}