#include <stdio.h>
#include <stdlib.h>

// struktura elementu listy
struct Node {
    int data;
    struct Node* next;
};

// funkcja do usuwania pierwszego elementu z listy
void pop(struct Node** head_ref) {
    if (*head_ref == NULL) {
        printf("Lista jest pusta. Nie ma czego usunac.\n");
        return;
    }
    // zapamiętaj referencję do obecnego nagłówka listy
    struct Node* temp = *head_ref;
    
    // Przesuń wskaźnik na następny element
    *head_ref = (*head_ref)->next;
    
    // zwolnij pamięć z usuniętego elementu
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

    // dodanie elementów na początek listy
    for (int i = 5; i >= 1; i--) {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->data = i;
        new_node->next = head;
        head = new_node;
    }

    // wyświetlenie listy przed usunięciem pierwszego elementu
    printf("Lista przed usunieciem pierwszego elementu: ");
    print_list(head);

    // usunięcie pierwszego elementu
    pop(&head);

    // wyświetlenie listy po usunięciu pierwszego elementu
    printf("Lista po usunieciu pierwszego elementu: ");
    print_list(head);

    return 0;
}
