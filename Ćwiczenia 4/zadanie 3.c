#include <stdio.h>

// funkcja do zamiany miejscami dwóch elementów w tablicy
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// funkcja do generowania permutacji
void permute(int *array, int start, int end) {
    if (start == end) {
        // wyświetlenie permutacji
        for (int i = 0; i <= end; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    } else {
        for (int i = start; i <= end; i++) {
            // zamiana miejscami elementów start i i
            swap(&array[start], &array[i]);
            // wywołanie permute dla kolejnych elementów
            permute(array, start + 1, end);
            // Ponowna zamiana miejscami
            swap(&array[start], &array[i]);
        }
    }
}

int main() {
    int array[] = {1, 2, 3};
    int n = sizeof(array) / sizeof(array[0]);
    printf("Wszystkie permutacje ciagu:\n");
    permute(array, 0, n - 1);
    return 0;
}
