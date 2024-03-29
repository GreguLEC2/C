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

// funkcja do dodawania elementu na określonym indeksie listy
void insert_at_index(struct Node** head_ref, int index, int new_data) {
    // utwórz nowy element
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;

    // jeśli indeks jest równy 0 wstaw nowy element na początek listy
    if (index == 0) {
        new_node->next = *head_ref;
        *head_ref = new_node;
        return;
    }

    // znajdź węzeł na pozycji index-1
    struct Node* temp = *head_ref;
    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->next;
    }

    // jeśli indeks wykracza poza rozmiar listy
    if (temp == NULL) {
        printf("Indeks wykracza poza rozmiar listy.\n");
        return;
    }

    // wstaw nowy element za węzłem na pozycji index-1
    new_node->next = temp->next;
    temp->next = new_node;
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
    append(&head, 1);
    append(&head, 2);
    append(&head, 4);
    append(&head, 5);

    // wyświetlenie listy przed dodaniem elementu
    printf("Lista przed dodaniem elementu: ");
    print_list(head);

    // dodanie elementu na indeksie 2
    insert_at_index(&head, 2, 3);

    // wyświetlenie listy po dodaniu elementu
    printf("Lista po dodaniu elementu: ");
    print_list(head);

    return 0;
}
