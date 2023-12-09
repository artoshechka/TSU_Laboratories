#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 200000

int main() {
    srand(time(NULL));
    int n, len = 0, mx_len = 0;
    scanf("%d", &n);
    int arr[N] = {0}; //задаем массив сост из 0 элементов
    int mn = arr[0], mn_i = 0, start_id, end_id;
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 1000; //элементы до 1000
        printf("%d ", arr[i]);
    }
    printf("\n");
    for (int i = 1; i < n - 1; ++i) {
        if (mn > arr[i]) { //найти мин элемент
            mn = arr[i];
            mn_i = i;
        }
    }
    start_id = mn_i; //минимальный элемент
    for (int i = mn_i; i < n - 1; ++i) {
        if (arr[i] > arr[i + 1]) { //понимаем что это последовательность
            ++len; //считаем длину последовательности
        } else {
            if (len > mx_len) {
                mx_len = len;
                end_id = i;
                start_id = end_id - len;
            }
            len = 0;

        }
    }
    printf("%d %d", start_id, end_id); //выводим индексы максимально возр последовательность
    return 0;
}