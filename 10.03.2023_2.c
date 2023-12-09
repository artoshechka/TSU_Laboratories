/*
Переставить элементы строк целочисленной матрицы X так, чтобы в первом столбце сначала шли отрицательные элементы, затем нули,
затем положительные элементы, причем сохранить порядок элементов в каждой из этих групп. Массив описать как указатель на указатель.
Пример: 0,-7,-1, 5, 2 -> -7, -1, 0, 5, 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int rows, cols;
    printf("Enter the number of rows and columns:");
    scanf("%d %d", &rows, &cols);
    int **matrix = (int **) malloc(rows * sizeof(int *));
    printf("Start matrix:\n");
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *) malloc(cols * sizeof(int));
    }
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        int *neg = (int *) malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = -100 + rand() % 200;
            if (matrix[i][j] < 0) {
                neg[j] = -1;
            }
            if (matrix[i][j] == 0) {
                neg[j] = 0;
            }
            if (matrix[i][j] > 0) {
                neg[j] = 1;
            }
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < cols; k++) {
                if (neg[j] < neg[k]) {
                    int temp = matrix[i][j];
                    matrix[i][j] = matrix[i][k];
                    matrix[i][k] = temp;
                    temp = neg[j];
                    neg[j] = neg[k];
                    neg[k] = temp;
                }
            }
        }
        free(neg);
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
