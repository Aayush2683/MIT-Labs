// Union and Intersection operation using doubly linked list.

#include <stdio.h>
#include <stdlib.h>

// Definition for doubly linked list node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node with the given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
void insertNode(struct Node** head, int data) {
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
    if (!temp) {
        printf("List is empty.\n");
        return;
    }
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to check if a value exists in the list
int exists(struct Node* head, int data) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == data) {
            return 1; // Found
        }
        temp = temp->next;
    }
    return 0; // Not found
}

// Function to perform the Union operation
struct Node* unionLists(struct Node* head1, struct Node* head2) {
    struct Node* result = NULL;
    struct Node* temp = head1;

    // Insert all elements of head1 into the result list
    while (temp != NULL) {
        insertNode(&result, temp->data);
        temp = temp->next;
    }

    // Insert elements of head2 that are not in result list
    temp = head2;
    while (temp != NULL) {
        if (!exists(result, temp->data)) {
            insertNode(&result, temp->data);
        }
        temp = temp->next;
    }

    return result;
}

// Function to perform the Intersection operation
struct Node* intersectionLists(struct Node* head1, struct Node* head2) {
    struct Node* result = NULL;
    struct Node* temp = head1;

    // Insert only the common elements between head1 and head2 into the result list
    while (temp != NULL) {
        if (exists(head2, temp->data) && !exists(result, temp->data)) {
            insertNode(&result, temp->data);
        }
        temp = temp->next;
    }

    return result;
}

// Function to get user input for the linked list
void inputList(struct Node** head) {
    int n, data;
    printf("Enter the number of elements in the list: ");
    scanf("%d", &n);
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertNode(head, data);
    }
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    // Get user input for two lists
    printf("Enter elements for List 1:\n");
    inputList(&list1);

    printf("Enter elements for List 2:\n");
    inputList(&list2);

    // Print the lists
    printf("\nList 1: ");
    printList(list1);

    printf("List 2: ");
    printList(list2);

    // Union operation
    struct Node* unionResult = unionLists(list1, list2);
    printf("Union of List 1 and List 2: ");
    printList(unionResult);

    // Intersection operation
    struct Node* intersectionResult = intersectionLists(list1, list2);
    printf("Intersection of List 1 and List 2: ");
    printList(intersectionResult);

    return 0;
}

