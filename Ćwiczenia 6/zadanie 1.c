#include <stdio.h>

union Dane {
    int liczba_calkowita;
    float liczba_zmiennoprzecinkowa;
    char znak;
};

int main() {
    union Dane dane;

    // przechowywanie i wyświetlanie int
    dane.liczba_calkowita = 10;
    printf("liczba całkowita: %d\n", dane.liczba_calkowita);

    // przechowywanie i wyświetlanie float
    dane.liczba_zmiennoprzecinkowa = 3.14;
    printf("liczba zmiennoprzecinkowa: %f\n", dane.liczba_zmiennoprzecinkowa);

    // przechowywanie i wyświetlanie znaku
    dane.znak = 'a';
    printf("znak: %c\n", dane.znak);

    return 0;
}
