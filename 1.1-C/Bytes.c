#include <stdio.h>
#include <math.h>

int main() {
    long int byte;
    scanf("%ld", &byte);
    printf("Tb: %ld \nGb: %ld \nMb: %d \nKb: %d \nb: %d", byte / pow(1024, 4), byte / pow(1024, 3), byte / pow(1024, 2),
           byte / 1024, byte % 1024);
}