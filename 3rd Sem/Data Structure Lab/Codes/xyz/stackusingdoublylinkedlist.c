// stack using doubly linked list

#include <stdio.h>
#include <stdlib.h>

// Definition for doubly linked list node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Definition of the stack using a doubly linked list
struct Stack {
    struct Node* top;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Function to initialize the stack
void initStack(struct Stack* stack) {
    stack->top = NULL;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return (stack->top == NULL);
}

// Function to push an element onto the stack
void push(struct Stack* stack, int data) {
    struct Node* newNode = createNode(data);

    if (isEmpty(stack)) {
        stack->top = newNode;
    } else {
        newNode->next = stack->top;
        stack->top->prev = newNode;
        stack->top = newNode;
    }
    printf("Pushed: %d\n", data);
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty, cannot pop.\n");
        return -1; // Return a sentinel value
    }

    struct Node* temp = stack->top;
    int data = temp->data;

    if (stack->top->next == NULL) { // Only one element in the stack
        stack->top = NULL;
    } else {
        stack->top = stack->top->next;
        stack->top->prev = NULL;
    }

    free(temp);
    return data;
}

// Function to get the top element of the stack
int top(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return -1;
    }
    return stack->top->data;
}

// Function to print the stack
void printStack(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }

    struct Node* temp = stack->top;
    printf("Stack: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Stack stack;
    initStack(&stack);  // Initialize the stack

    int choice, value;

    while (1) {
        printf("\nStack Operations Menu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Top\n");
        printf("4. Print Stack\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Push
                printf("Enter a value to push: ");
                scanf("%d", &value);
                push(&stack, value);
                break;

            case 2: // Pop
                value = pop(&stack);
                if (value != -1) {
                    printf("Popped: %d\n", value);
                }
                break;

            case 3: // Top
                value = top(&stack);
                if (value != -1) {
                    printf("Top of the stack: %d\n", value);
                }
                break;

            case 4: // Print Stack
                printStack(&stack);
                break;

            case 5: // Exit
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

