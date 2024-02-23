#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ROCK 0
#define PAPER 1
#define SCISSORS 2
#define GAMES 10


int main() {
    char name[100];
    printf("Wpisz swoje imię: ");
    scanf("%99s", name);
    printf("Hello, %s\n", name);
    return 0;
}

/*  ZADANIE 2
int main() {
    int grades[2][5] = {
        {5, 4, 3, 4, 5}, // Matematyka
        {3, 4, 5, 2, 3}  // Fizyka
    };
    float sum = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++) {
            sum += grades[i][j];
        }
    }
    printf("Średnia ocen: %.2f\n", sum / 10);
    return 0;
}

*/


/* ZADANIE 3

long factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int size = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < size; i++) {
        printf("Silnia z %d = %ld\n", array[i], factorial(array[i]));
    }
    return 0;
}

*/

/* ZADANIE 4
int main() {
    for (int i = 1; i <= 200; i++) {
        if (i % 5 == 0 && i % 7 == 0)
            printf("FooBar\n");
        else if (i % 5 == 0)
            printf("Foo\n");
        else if (i % 7 == 0)
            printf("Bar\n");
        else
            printf("%d\n", i);
    }
    return 0;
}


int sumOfMultiples(int n) {
    if (n < 0) return 0;
    int sum = 0;
    for (int i = 3; i < n; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            sum += i;
        }
    }
    return sum;
}

*/


/* ZADANIE 5
int main() {
    int number;
    printf("Podaj liczbę: ");
    scanf("%d", &number);
    printf("Suma: %d\n", sumOfMultiples(number));
    return 0;
}
*/

/* ZADANIE 6
int scores[GAMES][3]; // [Runda][0: Wynik użytkownika, 1: Wynik komputera, 2: 0 - remis, 1 - wygrana użytkownika, 2 - wygrana komputera]
int currentGame = 0;

int main() {
    int userChoice, computerChoice, currentGame = 0;
    const char* choices[] = { "kamień", "papier", "nożyce" };
    int scores[GAMES][3]; // Zakładając, że tablica scores jest odpowiednio zainicjowana

    srand(time(NULL));

    while (currentGame < GAMES) {
        printf("Wybierz (0: kamień, 1: papier, 2: nożyce): ");
        scanf("%d", &userChoice);
        if (userChoice < 0 || userChoice > 2) {
            printf("Nieprawidłowy wybór.\n");
            continue;
        }

        computerChoice = rand() % 3;
        printf("Wybrałeś %s, komputer wybrał %s.\n", choices[userChoice], choices[computerChoice]);

        if (userChoice == computerChoice) {
            printf("Remis!\n");
            scores[currentGame][2] = 0;
        }
        else if ((userChoice == ROCK && computerChoice == SCISSORS) ||
            (userChoice == PAPER && computerChoice == ROCK) ||
            (userChoice == SCISSORS && computerChoice == PAPER)) {
            printf("Wygrałeś!\n");
            scores[currentGame][2] = 1;
        }
        else {
            printf("Przegrałeś.\n");
            scores[currentGame][2] = 2;
        }

        scores[currentGame][0] = userChoice;
        scores[currentGame][1] = computerChoice;
        currentGame++;

        if (currentGame >= GAMES) {
            printf("Maksymalna liczba gier osiągnięta. Wpisz 'scores' aby zobaczyć wyniki.\n");
            break; // Zakończ pętlę, aby umożliwić wprowadzenie komendy
        }
    }

    // Oczekiwanie na wprowadzenie komendy po zakończeniu gier
    char command[10];
    scanf("%s", command);
    if (strcmp(command, "scores") == 0) {
        for (int i = 0; i < GAMES; i++) {
            printf("Gra %d: Wybrałeś %s, Komputer wybrał %s, Wynik: ", i + 1, choices[scores[i][0]], choices[scores[i][1]]);
            switch (scores[i][2]) {
            case 0: printf("Remis\n"); break;
            case 1: printf("Wygrana\n"); break;
            case 2: printf("Przegrana\n"); break;
            }
        }
    }

    return 0;
}

*/