#include <stdio.h>

// deklaracja funkcji wyszukiwania
int binary_search(int arr[], int left, int right, int x);

int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 10;
    int result = binary_search(arr, 0, n - 1, x);
    if (result == -1) {
        printf("Element %d nie zostal znaleziony.\n", x);
    } else {
        printf("Element %d zostal znaleziony na indeksie %d.\n", x, result);
    }
    return 0;
}

// definicja funkcji wyszukiwania
int binary_search(int arr[], int left, int right, int x) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        
        // jeśli element znajduje się dokładnie w środku
        if (arr[mid] == x) {
            return mid;
        }
        
        // jeśli element jest mniejszy od elementu w połowie, szukaj w lewej połowie
        if (arr[mid] > x) {
            return binary_search(arr, left, mid - 1, x);
        }
        
        // w przeciwnym razie szukaj w prawej połowie
        return binary_search(arr, mid + 1, right, x);
    }
    
    // jeśli element nie został znaleziony
    return -1;
}
