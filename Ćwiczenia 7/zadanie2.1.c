#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CZERWONE_DOSTEPNE 12
#define ZIELONE_DOSTEPNE 13
#define NIEBIESKIE_DOSTEPNE 14

bool czyMozliwa(int czerwone, int zielone, int niebieskie) {
  // sprawdź, czy dostępne ilości kolorów wystarczą na zamówienie
  if (CZERWONE_DOSTEPNE > czerwone && ZIELONE_DOSTEPNE > zielone && NIEBIESKIE_DOSTEPNE > niebieskie)
    return true;
  return false;
}

char* numer_gry(char* str) {
  // znajdź ostatni element (numer gry) oddzielony spacją
  char* last_elem = NULL;

  char* colon_pos = strchr(str, ':');
  if (colon_pos != NULL)
    *colon_pos = '\0'; // tymczasowo usuń dwukropek

  last_elem = strrchr(str, ' ');
  if (last_elem != NULL)
    last_elem++; // przesuń wskaźnik za ostatnią spację

  return last_elem;
}

void analiza(char input[]) {
  // analizuj tekst wejściowy zawierający informacje o grze

  char* colon_pos = strchr(input, ':');

  char* new_string = _strdup(colon_pos + 2); // kopiuj informacje po dwukropku

  const char delim[] = " ";
  char* token;
  char tokens[100][20];

  int i = 0;

  token = strtok(new_string, delim); // rozdziel tekst po spacji

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

  if (czyMozliwa(sum_red, sum_green, sum_blue)) // sprawdź dostępność kolorów
    printf("Gra %s\n", numer_gry(input)); // wyświetl numer gry jeśli możliwe
}

int main() {

  // otwórz plik "input_2.txt" do odczytu
  FILE* file = fopen("input_2.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  // wypisz nagłówek
  printf("Gry możliwe:\n");

  char line[1000];
  // przeszukuj każdą linię pliku
  while (fgets(line, sizeof(line), file) != NULL) {
    analiza(line); // analizuj zawartość linii
  }

  fclose(file); // zamknij plik

  return 0;
}
 
