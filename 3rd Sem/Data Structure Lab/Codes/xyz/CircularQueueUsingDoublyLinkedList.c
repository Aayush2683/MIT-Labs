//Circular Queue Using Doubly Linked List


#include <stdio.h>
#include <stdlib.h>

// Definition for doubly linked list node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Definition of the circular queue using a doubly linked list
struct CircularQueue {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Function to initialize the circular queue
void initQueue(struct CircularQueue* queue) {
    queue->front = queue->rear = NULL;
}

// Function to check if the queue is empty
int isEmpty(struct CircularQueue* queue) {
    return (queue->front == NULL);
}

// Function to enqueue (add to the rear of the queue)
void enqueue(struct CircularQueue* queue, int data) {
    struct Node* newNode = createNode(data);

    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
        newNode->next = newNode->prev = newNode; // Points to itself
    } else {
        newNode->next = queue->front;
        newNode->prev = queue->rear;
        queue->rear->next = newNode;
        queue->front->prev = newNode;
        queue->rear = newNode; // Update rear to the new node
    }
    printf("Enqueued: %d\n", data);
}

// Function to dequeue (remove from the front of the queue)
int dequeue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty, cannot dequeue.\n");
        return -1; // Return a sentinel value
    }

    int data = queue->front->data;
    struct Node* temp = queue->front;

    if (queue->front == queue->rear) {  // Only one element in the queue
        queue->front = queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
        queue->rear->next = queue->front;
        queue->front->prev = queue->rear;
    }

    free(temp);
    return data;
}

// Function to get the front element of the queue
int front(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }
    return queue->front->data;
}

// Function to get the rear element of the queue
int rear(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }
    return queue->rear->data;
}

// Function to print the queue
void printQueue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node* temp = queue->front;
    printf("Queue: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != queue->front);
    printf("\n");
}

int main() {
    struct CircularQueue queue;
    initQueue(&queue);  // Initialize the queue

    int choice, value;

    while (1) {
        printf("\nCircular Queue Operations Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Front\n");
        printf("4. Rear\n");
        printf("5. Print Queue\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Enqueue
                printf("Enter a value to enqueue: ");
                scanf("%d", &value);
                enqueue(&queue, value);
                break;

            case 2: // Dequeue
                value = dequeue(&queue);
                if (value != -1) {
                    printf("Dequeued: %d\n", value);
                }
                break;

            case 3: // Front
                value = front(&queue);
                if (value != -1) {
                    printf("Front of the queue: %d\n", value);
                }
                break;

            case 4: // Rear
                value = rear(&queue);
                if (value != -1) {
                    printf("Rear of the queue: %d\n", value);
                }
                break;

            case 5: // Print Queue
                printQueue(&queue);
                break;

            case 6: // Exit
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

