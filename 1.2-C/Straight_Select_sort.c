#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 100
#define loop(i, a, n) for(int i=a;i<n;++i)

int main() {
    int arr[N] = {0};
    int n1;
    srand(time(NULL));
    scanf("%d", &n1);
    int n = n1;
    loop(i, 0, n) {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n__________________________\n");
    loop(j, 1, n1) {
        int maximal = arr[0], maximal_id = 0;
        loop(i, 1, n) {
            if (arr[i] > maximal) {
                maximal = arr[i];
                maximal_id = i;
            }
        }
        int z = arr[maximal_id];
        arr[maximal_id] = arr[n - 1];
        arr[n - 1] = z;
        --n;
    }
    loop(i, 0, n1) {
        printf("%d ", arr[i]);
    }
    return 0;
}