// bubble sort

#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked list node
typedef struct Node {
    int data;               // To store the number
    struct Node *prev;      // Pointer to the previous node
    struct Node *next;      // Pointer to the next node
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
void insertNode(Node **head, int data) {
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

// Function to display the doubly linked list
void printList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to sort the doubly linked list in ascending order
void sortAscending(Node *head) {
    if (head == NULL) return;

    Node *i, *j;
    int temp;
    for (i = head; i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                // Swap the data
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// Function to sort the doubly linked list in descending order
void sortDescending(Node *head) {
    if (head == NULL) return;

    Node *i, *j;
    int temp;
    for (i = head; i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data < j->data) {
                // Swap the data
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// Main function
int main() {
    Node *head = NULL;
    int choice, num;

    printf("Doubly Linked List - Sort Numbers in Ascending and Descending Order\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add a number\n");
        printf("2. Display the list\n");
        printf("3. Sort in ascending order\n");
        printf("4. Sort in descending order\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number to add: ");
                scanf("%d", &num);
                insertNode(&head, num);
                break;

            case 2:
                if (head == NULL) {
                    printf("The list is empty.\n");
                } else {
                    printf("Current List: ");
                    printList(head);
                }
                break;

            case 3:
                if (head == NULL) {
                    printf("The list is empty. Add numbers first.\n");
                } else {
                    sortAscending(head);
                    printf("List sorted in ascending order: ");
                    printList(head);
                }
                break;

            case 4:
                if (head == NULL) {
                    printf("The list is empty. Add numbers first.\n");
                } else {
                    sortDescending(head);
                    printf("List sorted in descending order: ");
                    printList(head);
                }
                break;

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
