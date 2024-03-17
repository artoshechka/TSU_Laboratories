#include <stdio.h>
#include <math.h>

int main() {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    for (int x = -d; x <= d; ++x) {
        if(x!=0) {
            if (d % abs(x) == 0) {
                if ((a * x * x * x + b * x * x + c * x + d) == 0) {
                    printf("%d ", x);
                }
            }
        }
    }
    return 0;
}