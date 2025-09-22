#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

// Queue structure
typedef struct {
    int items[SIZE];
    int front;
    int rear;
    int count;
} Queue;

// Initialize the queue
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

// Check if queue is full
int isFull(Queue *q) {
    return q->count == SIZE;
}

// Check if queue is empty
int isEmpty(Queue *q) {
    return q->count == 0;
}

// Enqueue operation
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full! Cannot enqueue.\n");
        return;
    }
    q->rear = (q->rear + 1) % SIZE;
    q->items[q->rear] = value;
    q->count++;
    printf("%d enqueued successfully.\n", value);
}

// Dequeue operation
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1; 
    }
    int value = q->items[q->front];
    q->front = (q->front + 1) % SIZE;
    q->count--;
    printf("%d dequeued successfully.\n", value);
    return value;
}

// Display the queue
void display(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue content: ");
    for (int i = 0; i < q->count; i++) {
        int index = (q->front + i) % SIZE;
        printf("%d ", q->items[index]);
    }
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);

    int choice, value;

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&q, value);
                display(&q);
                break;

            case 2:
                dequeue(&q);
                display(&q);
                break;

            case 3:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
