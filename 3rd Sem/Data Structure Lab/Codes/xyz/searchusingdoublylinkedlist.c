#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a doubly linked list node
typedef struct Node {
    char data[100]; // To store a word or number
    struct Node *prev;
    struct Node *next;
} Node;

// Function to create a new node
Node* createNode(const char *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
void insertNode(Node **head, const char *data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to search for a word or number in the doubly linked list
int search(Node *head, const char *key) {
    Node *temp = head;
    int position = 1; // Position starts at 1
    while (temp != NULL) {
        if (strcmp(temp->data, key) == 0) {
            printf("'%s' found at position %d in the list.\n", key, position);
            return 1; // Found
        }
        temp = temp->next;
        position++;
    }
    printf("'%s' not found in the list.\n", key);
    return 0; // Not found
}

// Function to print the doubly linked list
void printList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%s ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function
int main() {
    Node *head = NULL;
    char input[100];
    char searchWord[100];
    int choice;

    printf("Doubly Linked List - Insert Words or Numbers and Search with Position\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add word/number\n");
        printf("2. Search for a word/number\n");
        printf("3. Display the list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a word or number to add: ");
                scanf("%s", input);
                insertNode(&head, input);
                break;

            case 2:
                if (head == NULL) {
                    printf("The list is empty. Add some words/numbers first.\n");
                    break;
                }
                printf("Enter the word or number to search: ");
                scanf("%s", searchWord);
                search(head, searchWord);
                break;

            case 3:
                if (head == NULL) {
                    printf("The list is empty.\n");
                } else {
                    printf("Current List: ");
                    printList(head);
                }
                break;

            case 4:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
