#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// funkcja konwertująca napisaną słownie liczbę na wartość cyfrową
// przyjmuje stały wskaźnik znakowy na słowo 
// zwraca wartość cyfrową (1-9), jeśli słowo odpowiada liczbie, w przeciwnym razie -1
int wordToDigit(const char* word) {
  // porównaj słowo z każdą liczbą od jednego do dziewięciu
  if (strcmp(word, "one") == 0) return 1;
  if (strcmp(word, "two") == 0) return 2;
  if (strcmp(word, "three") == 0) return 3;
  if (strcmp(word, "four") == 0) return 4;
  if (strcmp(word, "five") == 0) return 5;
  if (strcmp(word, "six") == 0) return 6;
  if (strcmp(word, "seven") == 0) return 7;
  if (strcmp(word, "eight") == 0) return 8;
  if (strcmp(word, "nine") == 0) return 9;

  // jeśli nie znaleziono dopasowania, zwróć -1
  return -1;
}

int findFirstAndLastDigit(const char* str) {
  int firstDigit = -1, lastDigit = -1;
  // tablica pomocnicza dla słów zapisanych cyframi
  char word[20] = "";
  int wordIndex = 0;

  // przeszukaj każdy znak w łańcuchu
  for (int i = 0; str[i] != '\0'; i++) {
    // zapamiętaj pierwszą lub zaktualizuj ostatnią
    if (isdigit(str[i])) {
      if (firstDigit == -1) firstDigit = str[i] - '0';
      lastDigit = str[i] - '0';
    } else if (isalpha(str[i])) {
      // zapisz w word i sprawdź funkcją wordToDigit (zakładamy, że istnieje)
      word[wordIndex++] = tolower(str[i]);
      word[wordIndex] = '\0';
      int digit = wordToDigit(word);
      if (digit != -1 && firstDigit == -1) firstDigit = digit;
      wordIndex = 0; // Resetuj indeks dla kolejnego słowa
    } else {
      // inny znak: reset indeksu
      wordIndex = 0;
    }
  }

  // zwróć odpowiednią wartość: brak cyfr, tylko ostatnia tylko pierwsza lub obie
  if (firstDigit == -1) return lastDigit;
  else if (lastDigit == -1) return firstDigit;
  return firstDigit * 10 + lastDigit;
}

int main() {
  int sum = 0;  // suma wartości energetycznych

  // otwórz plik do odczytu i obsłuż błąd
  FILE* file = fopen("input.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  char line[200];
  while (fgets(line, sizeof(line), file) != NULL) {
    // usuń znak końca linii, jeśli istnieje
    if (line[strlen(line) - 1] == '\n') {
      line[strlen(line) - 1] = '\0';
    }
    // dodaj wynik funkcji do sumy
    sum += findFirstAndLastDigit(line);
  }

  fclose(file);

  printf("Suma wszystkich wartości energetycznych = %d", sum);

  return 0;
}
