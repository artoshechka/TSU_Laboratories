#include <stdio.h>

int main() {
    char c;
    int n, pos;
    printf("You can choose robot's start position:\nN-North; S-South; W-West; E-East\nAlso you can give him commands:\n0-continue going; 1-turn left; 2-turn right\n");
    scanf("%c%d", &c, &n);
    switch (c) {
        case 'N':
            pos = 0;
            break;
        case 'E':
            pos = 1;
            break;
        case 'S':
            pos = 2;
            break;
        case 'W':
            pos = 3;
            break;
    }
    if (n == 1) {
        pos = (pos + 3) % 4;
    } else if (n == 2) {
        pos = (pos + 1) % 4;
    }
    switch (pos) {
        case 0:
            printf("North");
            break;
        case 1:
            printf("East");
            break;
        case 2:
            printf("South");
            break;
        case 3:
            printf("West");
            break;
    }
    return 0;
}