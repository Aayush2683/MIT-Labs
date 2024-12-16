// Reverse Stack using recursion

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Stack {
    int arr[MAX];
    int top;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int value) {
    if (stack->top < MAX - 1) {
        stack->arr[++(stack->top)] = value;
    } else {
        printf("Stack Overflow\n");
    }
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    } else {
        return stack->arr[(stack->top)--];
    }
}

void insertAtBottom(struct Stack* stack, int value) {
    if (isEmpty(stack)) {
        push(stack, value);
    } else {
        int topValue = pop(stack);
        insertAtBottom(stack, value);
        push(stack, topValue);
    }
}

void reverseStack(struct Stack* stack) {
    if (!isEmpty(stack)) {
        int topValue = pop(stack);
        reverseStack(stack);
        insertAtBottom(stack, topValue);
    }
}

void display(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

int main() {
    struct Stack* stack = createStack();

    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    push(stack, 5);
    
    printf("Original stack: ");
    display(stack);

    reverseStack(stack);
    
    printf("Reversed stack: ");
    display(stack);

    return 0;
}

