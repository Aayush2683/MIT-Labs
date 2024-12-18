#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertAtHead(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) *head = newNode;
    else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
}

void insertAtTail(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) *head = newNode;
    else {
        Node* temp = *head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void deleteFromHead(Node** head) {
    if (*head == NULL) return;
    Node* temp = *head;
    *head = (*head)->next;
    if (*head) (*head)->prev = NULL;
    free(temp);
}

void deleteFromTail(Node** head) {
    if (*head == NULL) return;
    Node* temp = *head;
    while (temp->next) temp = temp->next;
    if (temp->prev) temp->prev->next = NULL;
    else *head = NULL;
    free(temp);
}

void displayList(Node* head) {
    if (!head) { printf("List is empty.\n"); return; }
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    int choice, value;
    do {
        printf("\n1. Insert at head\n2. Insert at tail\n3. Delete from head\n4. Delete from tail\n5. Display list\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: printf("Enter value: "); scanf("%d", &value); insertAtHead(&head, value); break;
            case 2: printf("Enter value: "); scanf("%d", &value); insertAtTail(&head, value); break;
            case 3: deleteFromHead(&head); break;
            case 4: deleteFromTail(&head); break;
            case 5: displayList(head); break;
        }
    } while (choice != 6);
    return 0;
}
