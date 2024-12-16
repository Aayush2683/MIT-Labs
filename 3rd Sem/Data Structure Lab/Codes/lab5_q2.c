// Convert Decimal to Binary using Stack

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Stack {
    int top;
    int items[MAX];
} Stack;

void initStack(Stack *stack) {
    stack->top = -1;
}

int isFull(Stack *stack) {
    return stack->top == MAX - 1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow!\n");
        return;
    }
    stack->items[++stack->top] = value;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow!\n");
        return -1;
    }
    return stack->items[stack->top--];
}

void decimalToBinary(int decimal) {
    Stack stack;
    initStack(&stack);

    if (decimal == 0) {
        printf("Binary: 0\n");
        return;
    }

    while (decimal > 0) {
        push(&stack, decimal % 2);
        decimal /= 2;
    }

    printf("Binary: ");
    while (!isEmpty(&stack)) {
        printf("%d", pop(&stack));
    }
    printf("\n");
}

int main() {
    int number;

    printf("Enter a decimal number: ");
    scanf("%d", &number);

    if (number < 0) {
        printf("Please enter a non-negative integer.\n");
    } else {
        decimalToBinary(number);
    }

    return 0;
}
