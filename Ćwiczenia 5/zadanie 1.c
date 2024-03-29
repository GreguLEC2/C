#include <stdio.h>
#include <stdlib.h>

// struktura elementu listy
struct Node {
    int data;
    struct Node* next;
};

// funkcja do dodawania elementu na początek
void add_first(struct Node** head_ref, int new_data) {
    // utwórz nowy element
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    
    // ustaw jego wartość
    new_node->data = new_data;
    
    // powiąż nowy element aby wskazywał na obecny początek listy
    new_node->next = *head_ref;
    
    // ustaw nowy element jako początek listy
    *head_ref = new_node;
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
    add_first(&head, 3);
    add_first(&head, 5);
    add_first(&head, 7);

    // wyświetlenie listy
    printf("Lista: ");
    print_list(head);

    return 0;
}
