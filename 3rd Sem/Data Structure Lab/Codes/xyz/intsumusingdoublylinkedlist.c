// sum of int using doubly linked list

#include <stdio.h>
#include <stdlib.h>

// Definition for doubly linked list node
struct Node {
    int data;       // Data field to store the digit
    struct Node* prev;  // Pointer to the previous node
    struct Node* next;  // Pointer to the next node
};

// Function to create a new node with the given digit
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
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to add two numbers represented by doubly linked lists
struct Node* addNumbers(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    struct Node* temp1 = num1;
    struct Node* temp2 = num2;
    int carry = 0;

    // Add digits while there are nodes in either num1 or num2, or there is a carry
    while (temp1 != NULL || temp2 != NULL || carry != 0) {
        int sum = carry;

        // Add digit from num1 if available
        if (temp1 != NULL) {
            sum += temp1->data;
            temp1 = temp1->next;
        }

        // Add digit from num2 if available
        if (temp2 != NULL) {
            sum += temp2->data;
            temp2 = temp2->next;
        }

        // Calculate new carry and digit to store
        carry = sum / 10;
        insertNode(&result, sum % 10);
    }

    return result;
}

// Function to get user input for the linked list representation of a number
void inputNumber(struct Node** head) {
    char num[100];
    printf("Enter a number: ");
    scanf("%s", num);

    for (int i = 0; num[i] != '\0'; i++) {
        insertNode(head, num[i] - '0'); // Convert char to int
    }
}

int main() {
    struct Node* num1 = NULL;
    struct Node* num2 = NULL;

    // Get user input for two numbers
    inputNumber(&num1);
    inputNumber(&num2);

    // Print the numbers
    printf("\nNumber 1: ");
    printList(num1);

    printf("Number 2: ");
    printList(num2);

    // Add the two numbers
    struct Node* sum = addNumbers(num1, num2);

    // Print the sum
    printf("Sum: ");
    printList(sum);

    return 0;
}

