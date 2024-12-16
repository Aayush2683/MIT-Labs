// Prefix to Postfix using Stack

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char *data[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, char *value) {
    if (s->top == MAX - 1) {
        printf("Stack overflow!\n");
        exit(1);
    }
    s->data[++(s->top)] = value;
}

char *pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void prefixToPostfix(char *prefix) {
    Stack stack;
    initStack(&stack);

    int len = strlen(prefix);

    for (int i = len - 1; i >= 0; i--) {
        if (isspace(prefix[i])) continue;

        if (isalnum(prefix[i])) {
            char *operand = (char *)malloc(2 * sizeof(char));
            operand[0] = prefix[i];
            operand[1] = '\0';
            push(&stack, operand);
        } else if (isOperator(prefix[i])) {
            char *op1 = pop(&stack);
            char *op2 = pop(&stack);

            char *postfix = (char *)malloc(strlen(op1) + strlen(op2) + 2 * sizeof(char));
            sprintf(postfix, "%s%s%c", op1, op2, prefix[i]);

            push(&stack, postfix);

            free(op1);
            free(op2);
        }
    }

    char *result = pop(&stack);
    printf("Postfix expression: %s\n", result);

    free(result);
}

int main() {
    char prefix[MAX];

    printf("Enter a prefix expression: ");
    fgets(prefix, MAX, stdin);
    prefix[strcspn(prefix, "\n")] = '\0'; 

    prefixToPostfix(prefix);

    return 0;
}
