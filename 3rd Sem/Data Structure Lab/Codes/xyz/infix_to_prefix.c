// infix to prefix

#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

struct Stack {
    char arr[MAX];
    int top;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

void push(struct Stack* stack, char value) {
    if (stack->top < MAX - 1) {
        stack->arr[++(stack->top)] = value;
    } else {
        printf("Stack Overflow\n");
    }
}

char pop(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    } else {
        return stack->arr[(stack->top)--];
    }
}

char peek(struct Stack* stack) {
    if (stack->top != -1) {
        return stack->arr[stack->top];
    }
    return -1;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int precedence(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

void reverse(char* expr) {
    int len = strlen(expr);
    for (int i = 0; i < len / 2; i++) {
        char temp = expr[i];
        expr[i] = expr[len - i - 1];
        expr[len - i - 1] = temp;
    }
}

void infixToPostfix(char* infix, char* postfix) {
    struct Stack* stack = createStack();
    int j = 0; 
    
    for (int i = 0; i < strlen(infix); i++) {
        char current = infix[i];

        if (isalnum(current)) {
            postfix[j++] = current;
        }

        else if (current == '(') {
            push(stack, current);
        }

        else if (current == ')') {
            while (stack->top != -1 && peek(stack) != '(') {
                postfix[j++] = pop(stack);
            }
            pop(stack); 
        }

        else if (isOperator(current)) {
            while (stack->top != -1 && precedence(peek(stack)) >= precedence(current)) {
                postfix[j++] = pop(stack);
            }
            push(stack, current);
        }
    }
    

    while (stack->top != -1) {
        postfix[j++] = pop(stack);
    }
    postfix[j] = '\0'; 
}

void infixToPrefix(char* infix, char* prefix) {

    reverse(infix);

    for (int i = 0; i < strlen(infix); i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        } else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }

    char postfix[MAX];
    infixToPostfix(infix, postfix);

    reverse(postfix);

    strcpy(prefix, postfix);
}

int main() {
    char infix[MAX], prefix[MAX];
    
    printf("Enter the infix expression: ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = '\0'; 

    infixToPrefix(infix, prefix);

    printf("Prefix expression: %s\n", prefix);

    return 0;
}
