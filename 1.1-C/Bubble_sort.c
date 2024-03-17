#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 100
#define loop(i, a, n) for(int i=a;i<n;++i)


int main() {
    int arr[N] = {0};
    int n;
    srand(time(NULL));
    scanf("%d", &n);
    loop(i, 0, n) {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n__________________________ \n");
    loop(i, 0, n - 1) {
        loop(j, 0, n - i - 1) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    loop(i, 0, n) {
        printf("%d ", arr[i]);
    }
    return 0;
}
