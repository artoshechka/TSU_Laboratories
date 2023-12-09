#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n; // количество строк
    char **str; // массив указателей на строки
    printf("Enter the number of strings: ");
    scanf("%d", &n);
    str = (char **) malloc(n * sizeof(char *)); // выделение памяти под массив указателей
    for (int i = 0; i < n; i++) {
        str[i] = (char *) malloc(256 * sizeof(char)); // выделение памяти под каждую строку
        printf("Enter the string #%d: ", i + 1);
        scanf("%s", str[i]); // считываем строку из консоли
    }
    printf("\nStrings before removing:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", str[i]); // вывод всех строк перед удалением
    }
    int k = 0; // количество строк, которые нужно сохранить
    for (int i = 0; i < n; i++) {
        int distinct_chars = 0; // количество различных символов в строке
        int freq[256] = {0}; // массив для хранения частоты встречаемости символов в строке
        for (int j = 0; j < strlen(str[i]); j++) {
            freq[(int) str[i][j]]++; // увеличение частоты встречаемости символа в строке
        }
        for (int j = 0; j < 256; j++) {
            if (freq[j] > 0) {
                distinct_chars++; // увеличение количества различных символов в строке
            }
        }
        if (distinct_chars > 1) {
            // удаление строки, если она содержит более одного различного символа
            free(str[i]);
        } else {
            str[k] = str[i];// сохранение памяти, занятой строкой
            k++;
        }
    }
    n = k; // количество строк, которые остались в массиве
    str = (char **) realloc(str, n * sizeof(char *)); // изменение размера массива указателей
    printf("\nStrings after removing:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", str[i]); // вывод всех строк после удаления
    }
    // освобождение памяти, занятой массивом указателей и оставшимися строками
    for (int i = 0; i < n; i++) {
        free(str[i]);
    }
    free(str);
    return 0;
}