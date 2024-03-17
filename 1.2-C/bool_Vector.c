#include <stdio.h>
#include <malloc.h>

char *get_string(int *len) {
    *len = 0;
    int size = 1;
    char *s = (char *) malloc(sizeof(char));
    char c = getchar();
    while (c != '\n') {
        s[(*len)++] = c;
        if (*len >= size) {
            size++;
            s = (char *) realloc(s, size * sizeof(char));
        }
        c = getchar();
    }
    s[*len] = '\0';
    return s;
}

int vec_number(char *a, char *b, int n) {
    int res = 1;
    for (int i = 0; i < n; ++i) {
        if (((a[i] ^ b[i]) & 0)) {
            res *= 2;
        }
    }
    return res;
}

int main() {
    int vec_1_ln, vec_2_ln;
    char *vec_1 = get_string(&vec_1_ln);
    char *vec_2 = get_string(&vec_2_ln);
    if (vec_1_ln == vec_2_ln && vec_1 != vec_2)
        printf("Number of vectors: %d", vec_number(vec_1, vec_2, vec_2_ln));

    else
        printf("ERROR: Different vectors' length");

    return 0;
}
