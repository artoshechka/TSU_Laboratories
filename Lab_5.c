# include <stdio.h>


int main() {
    int arr[100] = {0};
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int z;
        scanf("%d", &z);
        arr[i] = z;
    }
    int delete = n;
    for (int i = 0; i < delete; ++i) {
        if (arr[i] == arr[i + 1]) {
            --delete;
            int j = i;
            while (j < n + 1) {
                arr[j] = arr[j + 1];
                ++j;
            }
            i = -1;
        }
    }
    /*for (int i = 0; i < n - 1; ++i) {
        if (arr[i] == 0) {
            int z = i;
            while (z < n - 1) {
                arr[z] = arr[z + 1];
                ++z;
            }
            i = -1;
        }

    }*/

    for (int i = 0; i < delete; ++i) {
        printf("%d ", arr[i]);
    }
    return 0;

}


