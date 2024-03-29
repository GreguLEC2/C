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

    // powiąż nowy element z ostatnim elementem
    last->next = new_node;
}

// funkcja do usuwania pierwszego elementu z listy zawierającej określoną wartość
void remove_by_value(struct Node** head_ref, int value) {
    if (*head_ref == NULL) {
        printf("Lista jest pusta. Nie ma czego usunac.\n");
        return;
    }

    struct Node* temp = *head_ref;
    struct Node* prev = NULL;

    // jeśli pierwszy element ma wartość do usunięcia
    if (temp != NULL && temp->data == value) {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    // znajdź poprzedni węzeł elementu do usunięcia
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    // element nie został znaleziony w liście
    if (temp == NULL) {
        printf("Element o wartosci %d nie zostal znaleziony w liscie.\n", value);
        return;
    }

    // usuń węzeł
    prev->next = temp->next;
    free(temp);
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

    // dodanie elementów na koniec
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 2);

    // wyświetlenie listy przed usunięciem elementu
    printf("Lista przed usunieciem elementu: ");
    print_list(head);

    // usunięcie pierwszego elementu o wartości 2
    remove_by_value(&head, 2);

    // wyświetlenie listy po usunięciu elementu
    printf("Lista po usunieciu elementu: ");
    print_list(head);

    return 0;
}
