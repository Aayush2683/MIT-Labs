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

-----------------------------------------------------------------------
// Modification 1: Prefix to Infix Conversion
void prefixToInfix(char *prefix) {
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

            char *infix = (char *)malloc(strlen(op1) + strlen(op2) + 4 * sizeof(char));
            sprintf(infix, "(%s%c%s)", op1, prefix[i], op2);

            push(&stack, infix);

            free(op1);
            free(op2);
        }
    }

    char *result = pop(&stack);
    printf("Infix expression: %s\n", result);

    free(result);
}

// -----------------------------------------------------------------------------
// Modification 2: Postfix to Prefix Conversion
void postfixToPrefix(char *postfix) {
    Stack stack;
    initStack(&stack);

    int len = strlen(postfix);

    for (int i = 0; i < len; i++) {
        if (isspace(postfix[i])) continue;

        if (isalnum(postfix[i])) {
            char *operand = (char *)malloc(2 * sizeof(char));
            operand[0] = postfix[i];
            operand[1] = '\0';
            push(&stack, operand);
        } else if (isOperator(postfix[i])) {
            char *op2 = pop(&stack);
            char *op1 = pop(&stack);

            char *prefix = (char *)malloc(strlen(op1) + strlen(op2) + 2 * sizeof(char));
            sprintf(prefix, "%c%s%s", postfix[i], op1, op2);

            push(&stack, prefix);

            free(op1);
            free(op2);
        }
    }

    char *result = pop(&stack);
    printf("Prefix expression: %s\n", result);

    free(result);
}

// -----------------------------------------------------------------------------
// Modification 3: Evaluate Prefix Expression
int evaluatePrefix(char *prefix) {
    Stack stack;
    initStack(&stack);

    int len = strlen(prefix);

    for (int i = len - 1; i >= 0; i--) {
        if (isspace(prefix[i])) continue;

        if (isdigit(prefix[i])) {
            char *operand = (char *)malloc(2 * sizeof(char));
            operand[0] = prefix[i];
            operand[1] = '\0';
            push(&stack, operand);
        } else if (isOperator(prefix[i])) {
            int op1 = atoi(pop(&stack));
            int op2 = atoi(pop(&stack));
            int result;

            switch (prefix[i]) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
            }

            char *resultStr = (char *)malloc(12 * sizeof(char));
            sprintf(resultStr, "%d", result);
            push(&stack, resultStr);
        }
    }

    int finalResult = atoi(pop(&stack));
    printf("Evaluated result: %d\n", finalResult);

    return finalResult;
}


// Handle Invalid Expressions

int isValidExpression(char* expression) {
    int operands = 0, operators = 0;

    for (int i = strlen(expression) - 1; i >= 0; i--) {
        if (isalnum(expression[i])) { // Operand
            operands++;
        } else { // Operator
            operators++;
            if (operators >= operands) {
                return 0; // Invalid: More operators than operands
            }
        }
    }

    return operands == operators + 1; // Valid if operands = operators + 1
}

void prefixToPostfixValidated(char* prefix) {
    if (!isValidExpression(prefix)) {
        printf("Invalid Expression\n");
        return;
    }

    // Existing conversion logic
    prefixToPostfix(prefix);
}


// Add Parentheses to Postfix or Prefix Expressions

void prefixToPostfixWithParentheses(char* prefix) {
    Stack s;
    initStack(&s);

    int length = strlen(prefix);

    // Scan the prefix expression from right to left
    for (int i = length - 1; i >= 0; i--) {
        if (isalnum(prefix[i])) { // Operand
            char operand[3] = {'(', prefix[i], ')'};
            push(&s, operand);
        } else { // Operator
            char operand1[100], operand2[100], result[100];
            strcpy(operand1, pop(&s));
            strcpy(operand2, pop(&s));

            // Add parentheses and combine
            sprintf(result, "(%s%s%c)", operand1, operand2, prefix[i]);
            push(&s, result);
        }
    }

    // Final postfix expression
    printf("Postfix with Parentheses: %s\n", pop(&s));
}



