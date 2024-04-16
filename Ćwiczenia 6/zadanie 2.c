#include <stdio.h>

int main() {
  int tablica[10]; // deklaracja tablicy 10 elementów

  // inicjalizacja tablicy wartościami od 0 do 9
  for (int i = 0; i < 10; i++) {
    tablica[i] = i;
  }

  // wskaźnik do pierwszego elementu
  int *wsk = tablica;

  // przechodzenie przez tablicę i wyświetlanie elementów
  for (int i = 0; i < 10; i++) {
    printf("%d ", *wsk); // Wyświetlenie wartości wskazywanej przez wskaźnik
    wsk++; // Inkrementuje wskaźnik, aby wskazywał na kolejny element
  }

  return 0;
}
