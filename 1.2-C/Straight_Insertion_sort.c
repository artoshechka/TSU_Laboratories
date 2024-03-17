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
    loop(i, 0, n1) {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n__________________________\n");
    loop(i, 1, n1) {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            int tmp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = tmp;
            --j;
        }

    }
    loop(i, 0, n1) {
        printf("%d ", arr[i]);
    }
    return 0;
}