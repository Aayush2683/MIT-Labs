//Menu Driven Stack Function

#include <stdio.h>
#include <stdlib.h>

#define MAX 5 

typedef struct {
    char stack[MAX];
    int top;
} Stack;

void initializeStack(Stack* s) {
    s->top = -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, char value) {
    if (isFull(s)) {
        printf("Error: Stack Overflow\n");
    } else {
        s->stack[++(s->top)] = value;
        printf("Pushed '%c' onto the stack.\n", value);
    }
}

char pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Error: Stack Underflow\n");
        return '\0';
    } else {
        char poppedValue = s->stack[(s->top)--];
        printf("Popped '%c' from the stack.\n", poppedValue);
        return poppedValue;
    }
}

void display(Stack* s) {
    if (isEmpty(s)) {
        printf("Error: Stack is empty\n");
    } else {
        printf("Stack elements: ");
        for (int i = s->top; i >= 0; i--) {
            printf("%c ", s->stack[i]);
        }
        printf("\n");
    }
}

void menu() {
    Stack s;
    initializeStack(&s);
    
    int choice;
    char value;

    do {
        printf("\nMenu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter character to push: ");
                scanf(" %c", &value);  
                push(&s, value);
                break;
            case 2:
                pop(&s);
                break;
            case 3:
                display(&s);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);
}

int main() {
    menu(); 
    return 0;
}

