#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Function to create a stack of given capacity
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to check if stack is empty
bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to check if stack is full
bool isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Function to push an item to the stack
void push(struct Stack* stack, char item) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}

// Function to pop an item from the stack
char pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->array[stack->top--];
}

// Function to get precedence of an operator
int precedence(char operator) {
    if (operator == '*' || operator == '/')
        return 2;
    else if (operator == '+' || operator == '-')
        return 1;
    else
        return 0;
}

// Function to convert infix expression to postfix
void infixToPostfix(char* infixExpression, char* postfixExpression) {
    int length = strlen(infixExpression);
    struct Stack* stack = createStack(length);
    int postfixIndex = 0;

    for (int i = 0; i < length; i++) {
        if (infixExpression[i] == ' ' || infixExpression[i] == '\t') {
            continue; // Skip whitespace characters
        } else if (isdigit(infixExpression[i])) {
            while (i < length && isdigit(infixExpression[i])) {
                postfixExpression[postfixIndex++] = infixExpression[i++];
            }
            postfixExpression[postfixIndex++] = ' ';
            i--; // Decrement i to process the last digit of the number
        } else if (infixExpression[i] == '(') {
            push(stack, '(');
        } else if (infixExpression[i] == ')') {
            while (!isEmpty(stack) && stack->array[stack->top] != '(') {
                postfixExpression[postfixIndex++] = pop(stack);
                postfixExpression[postfixIndex++] = ' ';
            }
            if (!isEmpty(stack) && stack->array[stack->top] == '(') {
                pop(stack); // Discard the opening parenthesis
            }
        } else {
            while (!isEmpty(stack) && precedence(infixExpression[i]) <= precedence(stack->array[stack->top])) {
                postfixExpression[postfixIndex++] = pop(stack);
                postfixExpression[postfixIndex++] = ' ';
            }
            push(stack, infixExpression[i]);
        }
    }

    while (!isEmpty(stack)) {
        postfixExpression[postfixIndex++] = pop(stack);
        postfixExpression[postfixIndex++] = ' ';
    }

    postfixExpression[postfixIndex] = '\0'; // Null-terminate the postfix expression

    free(stack->array);
    free(stack);
}

int main() {
    char infixExpression[100];
    char postfixExpression[100];
    printf("Enter an infix expression: ");
    fgets(infixExpression, sizeof(infixExpression), stdin);

    // Remove newline character from fgets
    if (infixExpression[strlen(infixExpression) - 1] == '\n') {
        infixExpression[strlen(infixExpression) - 1] = '\0';
    }

    infixToPostfix(infixExpression, postfixExpression);
    printf("Postfix expression: %s\n", postfixExpression);

    return 0;
}
