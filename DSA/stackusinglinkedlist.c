#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* top = NULL;

// Function to create a new node
struct Node* createNode(int item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Unable to create node.\n");
        return NULL;
    }
    newNode->data = item;
    newNode->next = NULL;
    return newNode;
}

// Function to check if the stack is empty
int isEmpty() {
    return top == NULL;
}

// Function to push an element onto the stack
void push(int item) {
    struct Node* newNode = createNode(item);
    if (newNode == NULL) {
        return;
    }
    newNode->next = top;
    top = newNode;
    printf("%d pushed onto the stack.\n", item);
}

// Function to pop an element from the stack
void pop() {
    if (isEmpty()) {
        printf("Stack is empty. Unable to pop.\n");
        return;
    }
    struct Node* temp = top;
    top = top->next;
    int poppedValue = temp->data;
    free(temp);
    printf("%d popped from the stack.\n", poppedValue);
}

// Function to display the elements in the stack
void displayStack() {
    if (isEmpty()) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack: ");
    struct Node* current = top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    push(10);
    push(20);
    push(30);

    displayStack();

    pop();
    pop();

    displayStack();

    push(40);

    displayStack();

    pop();
    pop();

    displayStack();

    return 0;
}
