//priority queue using doubly linked list

#include <stdio.h>
#include <stdlib.h>

// Definition for doubly linked list node
struct Node {
    int data;
    int priority;
    struct Node* prev;
    struct Node* next;
};

// Definition of the priority queue using a doubly linked list
struct PriorityQueue {
    struct Node* front;
};

// Function to create a new node
struct Node* createNode(int data, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Function to initialize the priority queue
void initQueue(struct PriorityQueue* pq) {
    pq->front = NULL;
}

// Function to check if the queue is empty
int isEmpty(struct PriorityQueue* pq) {
    return (pq->front == NULL);
}

// Function to enqueue (insert an element based on priority)
void enqueue(struct PriorityQueue* pq, int data, int priority) {
    struct Node* newNode = createNode(data, priority);

    if (isEmpty(pq)) {
        pq->front = newNode;
    } else {
        struct Node* temp = pq->front;

        // If the new node has higher priority than the front node
        if (newNode->priority > temp->priority) {
            newNode->next = pq->front;
            pq->front->prev = newNode;
            pq->front = newNode;
        } else {
            // Traverse the list to find the correct position
            while (temp->next != NULL && temp->next->priority >= newNode->priority) {
                temp = temp->next;
            }

            // Insert the new node at the found position
            newNode->next = temp->next;
            if (temp->next != NULL) {
                temp->next->prev = newNode;
            }
            newNode->prev = temp;
            temp->next = newNode;
        }
    }
    printf("Enqueued: %d with priority %d\n", data, priority);
}

// Function to dequeue (remove the element with the highest priority)
int dequeue(struct PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Queue is empty, cannot dequeue.\n");
        return -1; // Return a sentinel value
    }

    struct Node* temp = pq->front;
    int data = temp->data;

    if (pq->front->next == NULL) { // Only one element in the queue
        pq->front = NULL;
    } else {
        pq->front = pq->front->next;
        pq->front->prev = NULL;
    }

    free(temp);
    return data;
}

// Function to get the front element (highest priority)
int front(struct PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Queue is empty.\n");
        return -1;
    }
    return pq->front->data;
}

// Function to print the priority queue
void printQueue(struct PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node* temp = pq->front;
    printf("Priority Queue (from highest to lowest priority):\n");
    while (temp != NULL) {
        printf("Data: %d, Priority: %d\n", temp->data, temp->priority);
        temp = temp->next;
    }
}

int main() {
    struct PriorityQueue pq;
    initQueue(&pq);  // Initialize the priority queue

    int choice, value, priority;

    while (1) {
        printf("\nPriority Queue Operations Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Front\n");
        printf("4. Print Queue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Enqueue
                printf("Enter a value to enqueue: ");
                scanf("%d", &value);
                printf("Enter the priority: ");
                scanf("%d", &priority);
                enqueue(&pq, value, priority);
                break;

            case 2: // Dequeue
                value = dequeue(&pq);
                if (value != -1) {
                    printf("Dequeued: %d\n", value);
                }
                break;

            case 3: // Front
                value = front(&pq);
                if (value != -1) {
                    printf("Front of the queue: %d\n", value);
                }
                break;

            case 4: // Print Queue
                printQueue(&pq);
                break;

            case 5: // Exit
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

