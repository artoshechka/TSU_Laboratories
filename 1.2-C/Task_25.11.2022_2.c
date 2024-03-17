#include <stdio.h>

int main() {
    int a, b, c, d;
    printf("Enter four numbers to compare them");
    scanf("%d%d%d%d", &a, &b, &c, &d);
    if (a == b && b == c && c == d) {
        printf("All of tme are equal");
    } else if (a == b && c == d || a == c && b == d || a == d && b == c) {
        printf("They are pairs");
    } else if (a != b && a != c && a != d && b != c && b != d && c != d) {
        printf("All of them are different");
    } else if (a == b) {
        if (a == c) {
            printf("The number of different one is => 4");
        } else printf("The number of different one is => 3");
    } else {
        if (a == c) {
            printf("The number of different one is => 2");
        } else printf("The number of different one is => 1");
    }
    return 0;
}