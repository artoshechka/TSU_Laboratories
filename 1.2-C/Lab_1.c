#include <stdio.h>

int main() {
    int k, a = 10;
    scanf("%d", &k);
    if (k % 2 == 0) {
        printf("%d", (a + k/2 - 1) % 10);
    }else printf("%d", (a + k/2) / 10);
    return 0;
}