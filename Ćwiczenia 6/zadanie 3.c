#include <stdio.h>

int dodaj(int a, int b) {
  return a + b;
}

int mnoz(int a, int b) {
  return a * b;
}

int odejmij(int a, int b) {
  return a - b;
}

typedef int (*operacja)(int, int); // deklaracja typu wskaźnika

int main() {
  int a, b;
  char operacja_char;
  operacja operacja_ptr; // deklaracja wskaźnika do funkcji

  // pobranie danych od użytkownika
  printf("Podaj pierwszą liczbę: ");
  scanf("%d", &a);
  printf("Podaj drugą liczbę: ");
  scanf("%d", &b);

  // pobranie rodzaju operacji od użytkownika
  printf("Wybierz operację (+, -, *): ");
  scanf(" %c", &operacja_char);

  // przypisanie odpowiedniej funkcji do wskaźnika
  switch (operacja_char) {
    case '+':
      operacja_ptr = dodaj;
      break;
    case '-':
      operacja_ptr = odejmij;
      break;
    case '*':
      operacja_ptr = mnoz;
      break;
    default:
      printf("Niepoprawna operacja!\n");
      return 1;
  }

  // wywołanie funkcji za pomocą wskaźnika i wyświetlenie
  int wynik = operacja_ptr(a, b);
  printf("Wynik: %d\n", wynik);

  return 0;
}
