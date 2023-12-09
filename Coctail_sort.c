#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 200000
#define loop(i, a, n) for(int i=a;i<n;++i)
#define reversed_loop(i, a, n) for(int i=a;i<n;--i)

int creating(int n, int a[n]) {
    srand(time(NULL));
    loop(i, 0, n) {
        a[i] = rand() % 100;
    }
}

int sort(int n, int a[n]) {
    int counter = 0;
    loop(i, 0, n - 1) {
        if (a[i] <= a[i + 1]) {
            ++counter;
        } else {
            printf("unsorted");
            break;
        }
    }
    if (counter == n - 1) {
        printf("sorted");
    }


}

int cocktail_sort(int n, int beg, int end, int arr[n]) {
    while (beg < end) {
        int last = 0;
        loop(i, beg, end) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                last = i;
            }
        }
        end = last;
        reversed_loop(i, end, beg) {
            if (arr[i] < arr[i - 1]) {
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                last = i;
            }
            beg = last;

        }
    }
}


int main() {
    int array[N] = {0};
    int len;
    scanf("%d", &len);
    int begining_id = 0, ending_id = len - 1;
    creating(len, array);
    sort(len, array);
    printf("\n---------------------------------\n");
    cocktail_sort(len, begining_id, ending_id, array);
    sort(len, array);
    return 0;
}

