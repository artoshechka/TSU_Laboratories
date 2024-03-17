#include <stdio.h>


int main() {
    int n, key = 0, counter = 0, param;
    int array[100] = {0};
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int symb;
        scanf("%d", &symb);
        array[i] = symb;
    }
    for (int i = 0; i < n; ++i) {
        if (array[i] < array[i + 1]) {
            ++key;
        }else if(key>=1){
            ++counter;
            key=0;
        }
        /* else {
            param = 0;
            for (int z = 1; z < key; ++z) {
                param += key - z;
            }
            counter+=(key-1)*key-param;
            key=1;
        }*/
    }
    printf("%d", counter);
    return 0;
}