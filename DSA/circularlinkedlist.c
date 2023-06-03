#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
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
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the beginning of the circular linked list
void insert(int item) {
    struct Node* newNode = createNode(item);
    if (newNode == NULL) {
        return;
    }
    if (head == NULL) {
        head = newNode;
        newNode->next = head;
    } else {
        struct Node* current = head;
        while (current->next != head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = head;
        head = newNode;
    }
    printf("%d inserted successfully.\n", item);
}

// Function to delete a node with the given key from the circular linked list
void deleteNode(int key) {
    if (head == NULL) {
        printf("Circular linked list is empty. Unable to delete.\n");
        return;
    }

    struct Node* current = head;
    struct Node* prev = NULL;

    // Find the node to be deleted
    while (current->data != key) {
        if (current->next == head) {
            printf("%d not found in the list. Unable to delete.\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }

    // If the node to be deleted is the head node
    if (current == head) {
        struct Node* lastNode = head;
        while (lastNode->next != head) {
            lastNode = lastNode->next;
        }
        head = head->next;
        lastNode->next = head;
        free(current);
        printf("%d deleted successfully.\n", key);
        return;
    }

    // If the node to be deleted is not the head node
    prev->next = current->next;
    free(current);
    printf("%d deleted successfully.\n", key);
}

// Function to search for a given key in the circular linked list
struct Node* search(int key) {
    if (head == NULL) {
        printf("Circular linked list is empty. Unable to search.\n");
        return NULL;
    }

    struct Node* current = head;
    do {
        if (current->data == key) {
            printf("%d found in the list.\n", key);
            return current;
        }
        current = current->next;
    } while (current != head);

    printf("%d not found in the list.\n", key);
    return NULL;
}

// Function to display the elements of the circular linked list
void displayList() {
    if (head == NULL) {
        printf("Circular linked list is empty.\n");
        return;
    }

    struct Node* current = head;
    printf("Circular linked list: ");
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
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
