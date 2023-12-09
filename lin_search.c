#include <stdio.h>
#include <stdlib.h>

char *get_string(int *len) {
    *len = 0;
    int size = 1;
    char *s = (char *) malloc(sizeof(char));
    char c = getchar();
    while (c != '\n') {
        s[(*len)++] = c;
        if (*len >= size) {
            size *= 2;
            s = (char *) realloc(s, size * sizeof(char));
        }
        c = getchar();
    }
    s[*len] = '\0';
    return s;
}

int linear_search(char *string, char *substring, int len_s, int len_ss) {
    int j;
    for (int i = 0; i <= len_s - len_ss; i++) {
        for (j = 0; j < len_ss; j++) {
            if (string[i + j] != substring[j]) {
                j = len_ss;
            }
        }
        if (j == len_ss) {
            return i;
        }
    }

    return -1;
}

int main() {
    int len1, len2;
    printf("Enter string\n");
    char *string = get_string(&len1);
    printf("Enter find string\n");
    char *search = get_string(&len2);
    printf("%d", linear_search(string, search, len1, len2));
    free(string);
    free(search);
    return 0;
}