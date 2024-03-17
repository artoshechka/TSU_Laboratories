#include <stdio.h>
#include <math.h>

int main() {
    int x, y;
    float A, B;
    printf("Enter x kg and A rub, y kg and B rub");
    scanf("%d%f%d%f", &x, &A, &y, &B);
    printf("Cost of shocolate sweets: %f \n Cost of iriscs %f \n shoc > iris in %f times", A / x, B / y,
           (A / x) / (B / y));
    return 0;
}