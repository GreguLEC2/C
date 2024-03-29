#include <stdio.h>
#include <stdlib.h>

// struktura elementu listy
struct Node {
    int data;
    struct Node* next;
};

// funkcja do dodawania elementu na koniec listy
void append(struct Node** head_ref, int new_data) {
    // utwórz nowy element
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref; // pomocniczy wskaźnik na ostatni element

    // ustaw wartość nowego elementu
    new_node->data = new_data;
    new_node->next = NULL;

    // jeśli lista jest pusta, ustaw nowy element jako nagłówek listy
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    // lub znajdź ostatni element listy
    while (last->next != NULL) {
        last = last->next;
    }

    // Powiąż nowy element z ostatnim 
    last->next = new_node;
}

// funkcja do usuwania elementu z listy na podstawie jego indeksu
void remove_by_index(struct Node** head_ref, int index) {
    if (*head_ref == NULL) {
        printf("Lista jest pusta. Nie ma czego usunac.\n");
        return;
    }

    struct Node* temp = *head_ref;

    // usuwanie pierwszego elementu
    if (index == 0) {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    // znajdź poprzedni węzeł elementu do usunięcia
    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->next;
    }

    // Jjeśli indeks jest większy niż ilość elementów w liście
    if (temp == NULL || temp->next == NULL) {
        printf("Indeks wykracza poza rozmiar listy.\n");
        return;
    }

    // usuń węzeł poprzez przekierowanie wskaźnika na następny element
    struct Node* next_node = temp->next->next;
    free(temp->next);
    temp->next = next_node;
}

// funkcja do wyświetlania listy
void print_list(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    // inicjalizacja pustej listy
    struct Node* head = NULL;

    // dodanie elementów na koniec listy
    for (int i = 1; i <= 5; i++) {
        append(&head, i);
    }

    // wyświetlenie listy przed usunięciem elementu
    printf("Lista przed usunieciem elementu: ");
    print_list(head);

    // usunięcie elementu o indeksie 3
    remove_by_index(&head, 3);

    // wyświetlenie listy po usunięciu elementu
    printf("Lista po usunieciem elementu: ");
    print_list(head);

    return 0;
}
