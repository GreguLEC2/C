#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* numer_gry(char* str) {
  // wskaźnik na ostatni element początkowo null
  char* last_elem = NULL;

  // znajdź dwukropek ":" w łańcuchu znaków
  char* colon_pos = strchr(str, ':');
  if (colon_pos != NULL) {
    // jeśli znaleziono dwukropek tymczasowo ustaw znak null na jego miejscu
    *colon_pos = '\0';
  }

  // znajdź ostatnią spację w łańcuchu
  last_elem = strrchr(str, ' ');
  if (last_elem != NULL) {
    // jeśli znaleziono spację przesuń wskaźnik o 1 dalej aby wskazywał na numer gry
    last_elem++;
  }



void analiza(char input[]) {
  // znajdź dwukropek ":" w tekście wejściowym
  char* colon_pos = strchr(input, ':');

  // kopiuj informacje po dwukropku 
  char* new_string = _strdup(colon_pos + 2);

  const char delim[] = " "; // (spacja)
  char* token;
  char tokens[100][20];

  int i = 0;

  // rozdziel tekst po spacji
  token = strtok(new_string, delim);
  while (token != NULL) {
    strcpy(tokens[i], token); // kopiuj fragment tekstu do tablicy
    i++;
    token = strtok(NULL, delim);
  }

  int sum_red = 0;
  int sum_green = 0;
  int sum_blue = 0;

  // zsumuj ilości kolorów dla każdego typu klocka
  for (int j = 0; j < i; j += 2) {
    if (tokens[j + 1][0] == 'r') {
      sum_red += atoi(tokens[j]); // czerwony
    } else if (tokens[j + 1][0] == 'g') {
      sum_green += atoi(tokens[j]); // zielony
    } else {
      sum_blue += atoi(tokens[j]); // niebieski
    }
  }

  // wyświetl numer gry i obliczone wymagania dotyczące kolorów
  printf("Gra %s moze byc rozegrana z co najmniej %d czerwonymi, %d zielonymi i %d niebieskimi kostkami.\n", 
         numer_gry(input), sum_red, sum_green, sum_blue);

  // zwolnić pamięć alokowaną przez _strdup
  free(new_string); 
}


int main() {

  // otwórz plik "input_2.txt" do odczytu
  FILE* file = fopen("input_2.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  char line[1000];
  // przeszukuj każdą linię pliku
  while (fgets(line, sizeof(line), file) != NULL) {
    analiza(line); // Analizuj zawartość linii
  }

  fclose(file); // zamknij plik

  return 0;
}

