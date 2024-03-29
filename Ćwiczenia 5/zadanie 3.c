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

    // jeśli lista jest pusta ustaw nowy element jako nagłówek listy
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    // lub znajdź ostatni element listy
    while (last->next != NULL) {
        last = last->next;
    }

    // powiąż nowy element z ostatnim elementem
    last->next = new_node;
}

// funkcja do usuwania ostatniego elementu z listy
void remove_last(struct Node** head_ref) {
    if (*head_ref == NULL) {
        printf("Lista jest pusta. Nie ma czego usunac.\n");
        return;
    } else if ((*head_ref)->next == NULL) {
        // jeśli lista ma tylko jeden element zwolnij pamięć i ustaw wskaźnik na NULL
        free(*head_ref);
        *head_ref = NULL;
    } else {
        struct Node* temp = *head_ref;
        // przesuń się do przedostatniego elementu
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        // zwolnij pamięć ostatniego elementu
        free(temp->next);
        // Ustaw wskaźnik na NULL w ostatnim elemencie przed usunięciem
        temp->next = NULL;
    }
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

    // wyświetlenie listy przed usunięciem ostatniego elementu
    printf("Lista przed usunieciem ostatniego elementu: ");
    print_list(head);

    // usunięcie ostatniego elementu
    remove_last(&head);

    // wyświetlenie listy po usunięciu ostatniego elementu
    printf("Lista po usunieciu ostatniego elementu: ");
    print_list(head);

    return 0;
}
