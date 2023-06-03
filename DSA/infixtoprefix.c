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

// Function to check if character is an operator
bool isOperator(char character) {
    return (character == '+' || character == '-' || character == '*' || character == '/');
}

// Function to reverse a string
void reverseString(char* str) {
    int length = strlen(str);
    int i, j;
    for (i = 0, j = length - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

// Function to convert infix expression to prefix
void infixToPrefix(char* infixExpression, char* prefixExpression) {
    int length = strlen(infixExpression);
    struct Stack* stack = createStack(length);
    int prefixIndex = 0;

    for (int i = length - 1; i >= 0; i--) {
        if (infixExpression[i] == ' ' || infixExpression[i] == '\t') {
            continue; // Skip whitespace characters
        } else if (isdigit(infixExpression[i])) {
            while (i >= 0 && isdigit(infixExpression[i])) {
                prefixExpression[prefixIndex++] = infixExpression[i--];
            }
            prefixExpression[prefixIndex++] = ' ';
            i++; // Increment i to process the last digit of the number
        } else if (infixExpression[i] == ')') {
            push(stack, ')');
        } else if (infixExpression[i] == '(') {
            while (!isEmpty(stack) && stack->array[stack->top] != ')') {
                prefixExpression[prefixIndex++] = pop(stack);
                prefixExpression[prefixIndex++] = ' ';
            }
            if (!isEmpty(stack) && stack->array[stack->top] == ')') {
                pop(stack); // Discard the closing parenthesis
            }
        } else if (isOperator(infixExpression[i])) {
            while (!isEmpty(stack) && precedence(infixExpression[i]) < precedence(stack->array[stack->top])) {
                prefixExpression[prefixIndex++] = pop(stack);
                prefixExpression[prefixIndex++] = ' ';
            }
            push(stack, infixExpression[i]);
        }
    }

    while (!isEmpty(stack)) {
        prefixExpression[prefixIndex++] = pop(stack);
        prefixExpression[prefixIndex++] = ' ';
    }

    prefixExpression[prefixIndex] = '\0'; // Null-terminate the prefix expression
    reverseString(prefixExpression);

    free(stack->array);
    free(stack);
}

int main() {
    char infixExpression[100];
    char prefixExpression[100];
    printf("Enter an infix expression: ");
    fgets(infixExpression, sizeof(infixExpression), stdin);

    // Remove newline character from fgets
    if (infixExpression[strlen(infixExpression) - 1] == '\n') {
        infixExpression[strlen(infixExpression) - 1] = '\0';
    }

    infixToPrefix(infixExpression, prefixExpression);
    printf("Prefix expression: %s\n", prefixExpression);

    return 0;
}
