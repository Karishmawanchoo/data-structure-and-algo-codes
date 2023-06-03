#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int priority;
    struct Node* next;
};

struct PriorityQueue {
    struct Node* front;
};

// Function to create a new node
struct Node* createNode(int item, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Unable to create node.\n");
        return NULL;
    }
    newNode->data = item;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new priority queue
struct PriorityQueue* createPriorityQueue() {
    struct PriorityQueue* queue = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    if (queue == NULL) {
        printf("Memory allocation failed. Unable to create priority queue.\n");
        return NULL;
    }
    queue->front = NULL;
    return queue;
}

// Function to check if the priority queue is empty
int isEmpty(struct PriorityQueue* queue) {
    return queue->front == NULL;
}

// Function to enqueue (insert) an element into the priority queue
void enqueue(struct PriorityQueue* queue, int item, int priority) {
    struct Node* newNode = createNode(item, priority);
    if (newNode == NULL) {
        return;
    }
    if (isEmpty(queue) || priority < queue->front->priority) {
        newNode->next = queue->front;
        queue->front = newNode;
    } else {
        struct Node* current = queue->front;
        while (current->next != NULL && current->next->priority <= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    printf("%d enqueued into the priority queue with priority %d.\n", item, priority);
}

// Function to dequeue (remove) the element with the highest priority from the priority queue
void dequeue(struct PriorityQueue* queue) {
    if (isEmpty(queue)) {
        printf("Priority queue is empty. Unable to dequeue.\n");
        return;
    }
    struct Node* temp = queue->front;
    int dequeuedValue = temp->data;
    queue->front = queue->front->next;
    free(temp);
    printf("%d dequeued from the priority queue.\n", dequeuedValue);
}

// Function to display the elements in the priority queue
void displayPriorityQueue(struct PriorityQueue* queue) {
    if (isEmpty(queue)) {
        printf("Priority queue is empty.\n");
        return;
    }
    printf("Priority queue: ");
    struct Node* current = queue->front;
    while (current != NULL) {
        printf("(%d, %d) ", current->data, current->priority);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct PriorityQueue* queue = createPriorityQueue();

    enqueue(queue, 10, 2);
    enqueue(queue, 20, 1);
    enqueue(queue, 30, 3);

    displayPriorityQueue(queue);

    dequeue(queue);
    dequeue(queue);

    displayPriorityQueue(queue);

    enqueue(queue, 40, 1);

    displayPriorityQueue(queue);

    dequeue(queue);
    dequeue(queue);

    displayPriorityQueue(queue);

    return 0;
}
