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


// Convert Decimal to Hexadecimal Using Stack

void decimalToHexadecimal(int decimal) {
    Stack stack;
    initStack(&stack);

    while (decimal > 0) {
        int remainder = decimal % 16; 
        push(&stack, remainder);
        decimal /= 16;
    }

    printf("Hexadecimal: ");
    while (!isEmpty(&stack)) {
        int value = pop(&stack);
        if (value < 10) {
            printf("%d", value);
        } else {
            printf("%c", value - 10 + 'A'); 
        }
    }
    printf("\n");
}

// Convert Binary to Decimal Using Stack

void binaryToDecimal(int binary) {
    Stack stack;
    initStack(&stack);

    while (binary > 0) {
        int digit = binary % 10;
        push(&stack, digit);
        binary /= 10;
    }

    int decimal = 0;
    int power = 0;

    while (!isEmpty(&stack)) {
        int digit = pop(&stack);
        decimal += digit * (1 << power); 
        power++;
    }

    printf("Decimal: %d\n", decimal);
}

// Print Binary Representation in Reverse

void decimalToBinaryReverse(int decimal) {
    Stack stack;
    initStack(&stack);

    printf("Reversed Binary: ");
    while (decimal > 0) {
        int remainder = decimal % 2;
        printf("%d", remainder); 
        push(&stack, remainder);
        decimal /= 2;
    }
    printf("\n");
}

// Handle Negative Numbers

void decimalToBinaryWithNegative(int decimal) {
    Stack stack;
    initStack(&stack);

    if (decimal < 0) {
        printf("Binary: -");
        decimal = -decimal; 
    }

    while (decimal > 0) {
        int remainder = decimal % 2;
        push(&stack, remainder);
        decimal /= 2;
    }

    while (!isEmpty(&stack)) {
        printf("%d", pop(&stack));
    }
    printf("\n");
}

