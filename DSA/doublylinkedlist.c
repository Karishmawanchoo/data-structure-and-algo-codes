#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* head = NULL;

// Function to create a new node
struct Node* createNode(int item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Unable to create node.\n");
        return NULL;
    }
    newNode->data = item;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the beginning of the doubly linked list
void insert(int item) {
    struct Node* newNode = createNode(item);
    if (newNode == NULL) {
        return;
    }
    if (head == NULL) {
        head = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    printf("%d inserted successfully.\n", item);
}

// Function to delete a node with the given key from the doubly linked list
void deleteNode(int key) {
    if (head == NULL) {
        printf("Doubly linked list is empty. Unable to delete.\n");
        return;
    }

    struct Node* current = head;

    // If the key is found at the head node
    if (current->data == key) {
        head = current->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        free(current);
        printf("%d deleted successfully.\n", key);
        return;
    }

    // Search for the key to be deleted
    while (current != NULL && current->data != key) {
        current = current->next;
    }

    // If the key is not present in the doubly linked list
    if (current == NULL) {
        printf("%d not found in the list. Unable to delete.\n", key);
        return;
    }

    // Unlink the node from the doubly linked list
    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    free(current);
    printf("%d deleted successfully.\n", key);
}

// Function to search for a given key in the doubly linked list
struct Node* search(int key) {
    if (head == NULL) {
        printf("Doubly linked list is empty. Unable to search.\n");
        return NULL;
    }

    struct Node* current = head;

    while (current != NULL) {
        if (current->data == key) {
            printf("%d found in the list.\n", key);
            return current;
        }
        current = current->next;
    }

    printf("%d not found in the list.\n", key);
    return NULL;
}

// Function to display the elements of the doubly linked list in forward order
void displayForward() {
    if (head == NULL) {
        printf("Doubly linked list is empty.\n");
        return;
    }

    printf("Doubly linked list (Forward): ");
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to display the elements of the doubly linked list in reverse order
void displayReverse() {
    if (head == NULL) {
        printf("Doubly linked list is empty.\n");
        return;
    }

    printf("Doubly linked list (Reverse): ");
    struct Node* current = head;

    // Move to the last node
    while (current->next != NULL) {
        current = current->next;
    }

    // Traverse backward from the last node
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

int main() {
    insert(10);
    insert(20);
    insert(30);
    insert(40);

    displayForward();
    displayReverse();

    deleteNode(30);
    deleteNode(50);

    displayForward();
    displayReverse();

    search(20);
    search(50);

    return 0;
}
