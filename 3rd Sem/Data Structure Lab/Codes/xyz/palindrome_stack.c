// palindrome using stack

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

// Stack structure
struct Stack {
    char arr[MAX];
    int top;
};

// Function to create a new stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack* stack, char value) {
    if (stack->top < MAX - 1) {
        stack->arr[++(stack->top)] = value;
    } else {
        printf("Stack Overflow\n");
    }
}

// Function to pop an element from the stack
char pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    } else {
        return stack->arr[(stack->top)--];
    }
}

// Function to check if a string is a palindrome using a stack
int isPalindrome(char* str) {
    struct Stack* stack = createStack();
    int length = strlen(str);

    // Push all characters of the string onto the stack
    for (int i = 0; i < length; i++) {
        push(stack, str[i]);
    }

    // Compare the string with the stack (pop from stack and compare)
    for (int i = 0; i < length; i++) {
        if (str[i] != pop(stack)) {
            return 0; // Not a palindrome
        }
    }
    return 1; // It's a palindrome
}

int main() {
    char str[MAX];

    printf("Enter a string: ");
    fgets(str, MAX, stdin);
    str[strcspn(str, "\n")] = '\0';  // Remove the newline character

    if (isPalindrome(str)) {
        printf("The string is a palindrome.\n");
    } else {
        printf("The string is not a palindrome.\n");
    }

    return 0;
}

