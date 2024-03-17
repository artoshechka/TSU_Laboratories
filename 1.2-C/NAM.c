/* A={a,b,c}. Преобразовать слово P так, чтобы сначала шли все символы a,
затем – все символы b и в конце – все символы c. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int StrInEnd(char *S, char *T) {
    int j;
    int len_s= strlen(S);
    int len_ss= strlen(T);
    for (int i = 0; i <= len_s - len_ss; i++) {
        for (j = 0; j < len_ss; j++) {
            if (S[i + j] != T[j]) {
                j = len_ss;
            }
        }
        if (j == len_ss) {
            return 1;
        }
    }

    return 0;
}

int main() {
    char mySS[1000] = "SDAAAAAAABCCDF";
    char mySSq[1000] = "DKF";
    printf("%d",StrInEnd(mySS, mySSq));
}