#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

// Function to insert a new node at the beginning of the linked list
void insert(int item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Unable to insert node.\n");
        return;
    }
    newNode->data = item;
    newNode->next = head;
    head = newNode;
    printf("%d inserted successfully.\n", item);
}

// Function to delete a node with the given key from the linked list
void deleteNode(int key) {
    struct Node* prev = NULL;
    struct Node* current = head;

    // If the key is found at the head node
    if (current != NULL && current->data == key) {
        head = current->next;
        free(current);
        printf("%d deleted successfully.\n", key);
        return;
    }

    // Search for the key to be deleted
    while (current != NULL && current->data != key) {
        prev = current;
        current = current->next;
    }

    // If the key is not present in the linked list
    if (current == NULL) {
        printf("%d not found in the list. Unable to delete.\n", key);
        return;
    }

    // Unlink the node from the linked list
    prev->next = current->next;
    free(current);
    printf("%d deleted successfully.\n", key);
}

// Function to search for a given key in the linked list
struct Node* search(int key) {
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

// Function to display the elements of the linked list
void displayList() {
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    printf("Linked list: ");
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    insert(10);
    insert(20);
    insert(30);
    insert(40);

    displayList();

    deleteNode(30);
    deleteNode(50);

    displayList();

    search(20);
    search(50);

    return 0;
}
