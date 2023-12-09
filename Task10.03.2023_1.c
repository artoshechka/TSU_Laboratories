#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int rows, cols, max_row, max_col, max_elem = 0;
    printf("Enter the number of rows and columns:");
    scanf("%d %d", &rows, &cols);

    int **matrix = (int **) malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *) malloc(cols * sizeof(int));
    }


    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100;
            if (max_elem < matrix[i][j]) {
                max_elem = matrix[i][j];
                max_row = i;
                max_col = j;
            }
        }
    }
    printf("Start matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = max_row; i > 0 ; --i) {
        int *temp1 = matrix[i];
        matrix[i] = matrix[i - 1];
        matrix[i - 1] = temp1;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = max_col; j > 0; --j) {
            int temp2 = matrix[i][j];
            matrix[i][j] = matrix[i][j - 1];
            matrix[i][j - 1] = temp2;
        }
    }

    printf("Modified matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }


    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
