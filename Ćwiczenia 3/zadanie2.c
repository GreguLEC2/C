#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void printPascalTriangle(int N) {
    int arr[N][N]; // Deklaracja tablicy 2D do przechowywania wartości trójkąta

    // Inicjalizacja pierwszej kolumny i przekątnej tablicy jako 1
    for (int line = 0; line < N; line++) {
        arr[line][0] = 1;
        arr[line][line] = 1;
    }

    // Obliczanie wartości trójkąta Pascala i zapisywanie ich w tablicy
    for (int line = 2; line < N; line++) {
        for (int i = 1; i < line; i++) {
            arr[line][i] = arr[line-1][i-1] + arr[line-1][i];
        }
    }

    // Wypisywanie trójkąta Pascala
    for (int line = 0; line < N; line++) {
        for (int i = 0; i <= line; i++) {
            printf("%d ", arr[line][i]);
        }
        printf("\n");
    }
}

int main() {
    int N;
    printf("Podaj wysokość trójkąta Pascala: ");
    scanf("%d", &N);
    printPascalTriangle(N);
    return 0;
}
