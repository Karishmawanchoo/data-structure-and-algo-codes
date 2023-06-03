#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    char** array;
};

// Function to create a stack of given capacity
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char**)malloc(stack->capacity * sizeof(char*));
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
void push(struct Stack* stack, char* item) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}

// Function to pop an item from the stack
char* pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return NULL;
    }
    return stack->array[stack->top--];
}

// Function to convert postfix expression to infix
void postfixToInfix(char* postfixExpression, char* infixExpression) {
    int length = strlen(postfixExpression);
    struct Stack* stack = createStack(length);

    for (int i = 0; i < length; i++) {
        if (postfixExpression[i] == ' ' || postfixExpression[i] == '\t') {
            continue; // Skip whitespace characters
        } else if (isalnum(postfixExpression[i])) {
            char* operand = (char*)malloc(2 * sizeof(char));
            operand[0] = postfixExpression[i];
            operand[1] = '\0';
            push(stack, operand);
        } else {
            char* operand2 = pop(stack);
            char* operand1 = pop(stack);

            int resultLength = strlen(operand1) + strlen(operand2) + 4; // 4 for brackets and operator
            char* result = (char*)malloc(resultLength * sizeof(char));

            snprintf(result, resultLength, "(%s%c%s)", operand1, postfixExpression[i], operand2);

            push(stack, result);

            free(operand1);
            free(operand2);
        }
    }

    char* finalResult = pop(stack);
    strcpy(infixExpression, finalResult);

    free(finalResult);
    free(stack->array);
    free(stack);
}

int main() {
    char postfixExpression[100];
    char infixExpression[100];
    printf("Enter a postfix expression: ");
    fgets(postfixExpression, sizeof(postfixExpression), stdin);

    // Remove newline character from fgets
    if (postfixExpression[strlen(postfixExpression) - 1] == '\n') {
        postfixExpression[strlen(postfixExpression) - 1] = '\0';
    }

    postfixToInfix(postfixExpression, infixExpression);
    printf("Infix expression: %s\n", infixExpression);

    return 0;
}
