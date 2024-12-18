// reverse string (words) using doubly linked list


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition for doubly linked list node
struct Node {
    char* data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node with the given word
struct Node* createNode(char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = (char*)malloc(strlen(data) + 1);  // Allocate memory for the word
    strcpy(newNode->data, data);
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
void insertNode(struct Node** head, char* data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to print the doubly linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%s ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to reverse the doubly linked list
void reverseList(struct Node** head) {
    if (*head == NULL) return;  // List is empty, nothing to reverse

    struct Node* temp = NULL;
    struct Node* current = *head;

    // Reverse the pointers of each node
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;  // Move to the next node (which is now prev)
    }

    // Adjust the head pointer to the last node
    if (temp != NULL) {
        *head = temp->prev;
    }
}

// Function to get user input for the linked list
void inputList(struct Node** head) {
    int n;
    char word[100];
    printf("Enter the number of words: ");
    scanf("%d", &n);
    printf("Enter the words:\n");

    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        insertNode(head, word);
    }
}

int main() {
    struct Node* list = NULL;

    // Get user input for the list
    inputList(&list);

    // Print the original list
    printf("\nOriginal List: ");
    printList(list);

    // Reverse the list
    reverseList(&list);

    // Print the reversed list
    printf("Reversed List: ");
    printList(list);

    return 0;
}

