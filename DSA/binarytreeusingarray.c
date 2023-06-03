#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int tree[MAX_SIZE];

// Function to initialize the binary tree array
void initTree() {
    for (int i = 0; i < MAX_SIZE; i++) {
        tree[i] = -1;  // -1 represents an empty node
    }
}

// Function to check if a node is empty
int isEmpty(int index) {
    return tree[index] == -1;
}

// Function to insert a new element into the binary tree
void insert(int value) {
    int index = 0;
    while (!isEmpty(index)) {
        if (value <= tree[index]) {
            index = 2 * index + 1;  // Go to the left child
        } else {
            index = 2 * index + 2;  // Go to the right child
        }
    }
    tree[index] = value;
}

// Function for pre-order traversal
void preOrder(int index) {
    if (!isEmpty(index)) {
        printf("%d ", tree[index]);
        preOrder(2 * index + 1);  // Visit the left child
        preOrder(2 * index + 2);  // Visit the right child
    }
}

// Function for in-order traversal
void inOrder(int index) {
    if (!isEmpty(index)) {
        inOrder(2 * index + 1);  // Visit the left child
        printf("%d ", tree[index]);
        inOrder(2 * index + 2);  // Visit the right child
    }
}

// Function for post-order traversal
void postOrder(int index) {
    if (!isEmpty(index)) {
        postOrder(2 * index + 1);  // Visit the left child
        postOrder(2 * index + 2);  // Visit the right child
        printf("%d ", tree[index]);
    }
}

// Function to search for an element in the binary tree
int search(int value) {
    int index = 0;
    while (!isEmpty(index)) {
        if (value == tree[index]) {
            return index;
        } else if (value < tree[index]) {
            index = 2 * index + 1;  // Go to the left child
        } else {
            index = 2 * index + 2;  // Go to the right child
        }
    }
    return -1;  // Element not found
}

// Function to find the minimum value in the binary tree
int findMinValue(int index) {
    if (isEmpty(index)) {
        return -1;
    }
    while (!isEmpty(2 * index + 1)) {
        index = 2 * index + 1;  // Go to the left child
    }
    return tree[index];
}

// Function to delete a node from the binary tree
void deleteNode(int value) {
    int parentIndex = -1;
    int deleteIndex = search(value);
    if (deleteIndex == -1) {
        printf("Element not found in the binary tree.\n");
        return;
    }
    // Find the parent of the node to be deleted
    while (deleteIndex != 0 && tree[parentIndex] != value) {
        if (value < tree[parentIndex]) {
            parentIndex = 2 * parentIndex + 1;  // Go to the left child
        } else {
            parentIndex = 2 * parentIndex + 2;  // Go to the right child
        }
    }
    // Case 1: Node to be deleted is a leaf node
    if (isEmpty(2 * deleteIndex + 1) && isEmpty(2 * deleteIndex + 2)) {
        tree[deleteIndex] = -1;  // Mark the node as empty
    }
    // Case 2: Node to be deleted has only one child
    else if (isEmpty(2 * deleteIndex + 1)) {
        tree[deleteIndex] = tree[2 * deleteIndex + 2];  // Replace with the right child
        tree[2 * deleteIndex + 2] = -1;  // Remove the right child
    } else if (isEmpty(2 * deleteIndex + 2)) {
        tree[deleteIndex] = tree[2 * deleteIndex + 1];  // Replace with the left child
        tree[2 * deleteIndex + 1] = -1;  // Remove the left child
    }
    // Case 3: Node to be deleted has two children
    else {
        int minValue = findMinValue(2 * deleteIndex + 2);
        deleteNode(minValue);
        tree[deleteIndex] = minValue;
    }
    printf("Node with value %d deleted from the binary tree.\n", value);
}

int main() {
    initTree();

    // Insert elements into the binary tree
    insert(50);
    insert(30);
    insert(70);
    insert(20);
    insert(40);
    insert(60);
    insert(80);

    printf("Pre-order traversal: ");
    preOrder(0);
    printf("\n");

    printf("In-order traversal: ");
    inOrder(0);
    printf("\n");

    printf("Post-order traversal: ");
    postOrder(0);
    printf("\n");

    int searchValue = 60;
    int searchIndex = search(searchValue);
    if (searchIndex != -1) {
        printf("Element %d found at index %d in the binary tree.\n", searchValue, searchIndex);
    } else {
        printf("Element %d not found in the binary tree.\n", searchValue);
    }

    deleteNode(30);

    printf("In-order traversal after deletion: ");
    inOrder(0);
    printf("\n");

    return 0;
}
