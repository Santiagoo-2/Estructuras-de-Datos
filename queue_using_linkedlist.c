#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node *next;
};


struct Queue {
    struct Node *front; 
    struct Node *rear;  
};


struct Queue* createQueue() {
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    if (q == NULL) {
        // Handle memory allocation failure
        perror("Error allocating memory for queue");
        exit(EXIT_FAILURE);
    }
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(struct Queue *q) {
    return (q->front == NULL);
}

void enqueue(struct Queue *q, int k) {
    // 1. Create a new linked list node
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    if (temp == NULL) {
        // Handle memory allocation failure
        perror("Error allocating memory for new node");
        return;
    }
    temp->data = k;
    temp->next = NULL;

    // 2. If the queue is empty, the new node is both front and rear
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    // 3. Otherwise, link the new node at the rear
    q->rear->next = temp;
    q->rear = temp; // Update the rear pointer
}


int dequeue(struct Queue *q) {
    // Check for an empty queue
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1; 
    }

    // 1. Store the previous front
    struct Node *temp = q->front;
    int data = temp->data;

    // 2. Move the front pointer to the next node
    q->front = q->front->next;

    // 3. If front becomes NULL, the queue is now empty, so rear must also be NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }

    // 4. Free the memory of the old front node
    free(temp);
    
    return data;
}


void displayQueue(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node *current = q->front;
    printf("Queue (Front -> Rear): ");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}


int main() {
    struct Queue *queue = createQueue();
    int choice, value;
    
    printf("--- Queue ADT Implementation using Linked List ---\n");

    do {
        printf("\n--- Menu ---\n");
        printf("1. Enqueue (Add element)\n");
        printf("2. Dequeue (Remove element)\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        // Read choice from keyboard
        if (scanf("%d", &choice) != 1) {
            // Handle invalid input (non-integer)
            printf("Invalid input. Please enter a number.\n");
            // Clear the input buffer to prevent an infinite loop
            while (getchar() != '\n');
            choice = 0; // Set choice to an invalid option
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter the integer value to enqueue: ");
                // Read data from keyboard
                if (scanf("%d", &value) == 1) {
                    enqueue(queue, value);
                    printf("%d enqueued successfully.\n", value);
                } else {
                    printf("Invalid input for value.\n");
                    while (getchar() != '\n');
                }
                break;
            case 2:
                value = dequeue(queue);
                if (value != -1) {
                    printf("%d dequeued successfully.\n", value);
                }
                break;
            case 3:
                displayQueue(queue);
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    // Clean up memory before exiting (free all remaining nodes and the queue structure)
    while (!isEmpty(queue)) {
        dequeue(queue); // Dequeue frees the node
    }
    free(queue);

    return 0;
}