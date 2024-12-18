// queue using doubly linked list 

#include <stdio.h>
#include <stdlib.h>

// Definition of the doubly linked list node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Definition of the queue structure using a doubly linked list
struct Queue {
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

// Function to initialize the queue
void initQueue(struct Queue* queue) {
    queue->front = queue->rear = NULL;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

// Function to enqueue (insert at the rear)
void enqueue(struct Queue* queue, int data) {
    struct Node* newNode = createNode(data);

    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        newNode->prev = queue->rear;
        queue->rear = newNode;
    }
    printf("Enqueued: %d\n", data);
}

// Function to dequeue (remove from the front)
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty, cannot dequeue.\n");
        return -1; // Return a sentinel value
    }
    
    struct Node* temp = queue->front;
    int data = temp->data;
    
    if (queue->front == queue->rear) {  // Only one element in the queue
        queue->front = queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
        queue->front->prev = NULL;
    }
    
    free(temp);
    return data;
}

// Function to get the front element
int front(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }
    return queue->front->data;
}

// Function to get the rear element
int rear(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }
    return queue->rear->data;
}

// Function to print the queue
void printQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node* temp = queue->front;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Queue queue;
    initQueue(&queue);  // Initialize the queue

    int choice, value;

    while (1) {
        printf("\nQueue Operations Menu:\n");
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

