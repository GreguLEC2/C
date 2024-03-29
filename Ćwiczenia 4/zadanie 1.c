#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int rows, cols;
    printf("Podaj liczbe wierszy: ");
    scanf("%d", &rows);
    printf("Podaj liczbe kolumn: ");
    scanf("%d", &cols);

    // alokacja pamięci dla wierszy macierzy
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        fprintf(stderr, "Nie udało się zaalokować pamięci\n");
        return 1;
    }

    // alokacja pamięci dla kolumn każdego wiersza
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Nie udało się zaalokować pamięci\n");
            // zwolnienie przydzielonej pamięci
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
    }

    // włączenie generatura liczb
    srand(time(NULL));

    // wypełnienie macierzy losowymi liczbami i wyświetlenie 
    printf("Wygenerowana macierz:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100; // Losowe liczby z zakresu 0-99
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // zwolnienie pamięci
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

