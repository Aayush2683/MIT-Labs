// Sum of 2 Long int using Circular Doubly Linked List

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int digit;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* header;
} CircularDoublyLinkedList;

CircularDoublyLinkedList* createList() {
    CircularDoublyLinkedList* list = (CircularDoublyLinkedList*)malloc(sizeof(CircularDoublyLinkedList));
    list->header = (Node*)malloc(sizeof(Node));
    list->header->next = list->header;
    list->header->prev = list->header;
    return list;
}

void insertDigit(CircularDoublyLinkedList* list, int digit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->digit = digit;
    Node* last = list->header->prev;
    last->next = newNode;
    newNode->prev = last;
    newNode->next = list->header;
    list->header->prev = newNode;
}

void displayList(CircularDoublyLinkedList* list) {
    Node* temp = list->header->next;
    while (temp != list->header) {
        printf("%d", temp->digit);
        temp = temp->next;
    }
    printf("\n");
}

void displayListReversed(CircularDoublyLinkedList* list) {
    Node* temp = list->header->prev;
    while (temp != list->header) {
        printf("%d", temp->digit);
        temp = temp->prev;
    }
    printf("\n");
}

CircularDoublyLinkedList* addLists(CircularDoublyLinkedList* list1, CircularDoublyLinkedList* list2) {
    CircularDoublyLinkedList* result = createList();
    Node* node1 = list1->header->prev;
    Node* node2 = list2->header->prev;
    int carry = 0;

    while (node1 != list1->header || node2 != list2->header || carry != 0) {
        int sum = carry;
        if (node1 != list1->header) {
            sum += node1->digit;
            node1 = node1->prev;
        }
        if (node2 != list2->header) {
            sum += node2->digit;
            node2 = node2->prev;
        }
        carry = sum / 10;
        insertDigit(result, sum % 10);
    }

    return result;
}

void inputNumber(CircularDoublyLinkedList* list, const char* prompt) {
    char number[1000];
    printf("%s", prompt);
    scanf("%s", number);
    for (int i = 0; number[i] != '\0'; i++) {
        insertDigit(list, number[i] - '0');
    }
}

int main() {
    CircularDoublyLinkedList* list1 = createList();
    CircularDoublyLinkedList* list2 = createList();
    
    inputNumber(list1, "Enter the first large number: ");
    inputNumber(list2, "Enter the second large number: ");
    
    printf("Number 1: ");
    displayList(list1);
    
    printf("Number 2: ");
    displayList(list2);
    
    CircularDoublyLinkedList* result = addLists(list1, list2);
    
    printf("Sum: ");
    displayListReversed(result);
    
    return 0;
}
