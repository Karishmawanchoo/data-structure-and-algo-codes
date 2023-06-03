#include <stdio.h>

#define MAX_SIZE 100

int queue[MAX_SIZE];
int front = -1;
int rear = -1;

void enqueue(int item) {
    if (rear == MAX_SIZE - 1) {
        printf("Queue is full. Cannot enqueue item.\n");
        return;
    }

    if (front == -1)
        front = 0;

    rear++;
    queue[rear] = item;
    printf("%d enqueued to the queue.\n", item);
}

void dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty. Cannot dequeue item.\n");
        return;
    }

    int item = queue[front];
    front++;

    printf("%d dequeued from the queue.\n", item);

    if (front > rear)
        front = rear = -1;
}

void displayQueue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue: ");
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);

    displayQueue();

    dequeue();
    dequeue();

    displayQueue();

    return 0;
}
n
