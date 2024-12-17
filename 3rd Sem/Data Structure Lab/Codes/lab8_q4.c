// reverse the queue using only (enqueue(x), dequeue(), empty())

#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int *arr;
    int front, rear, capacity;
};

struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->arr = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isEmpty(struct Queue* queue) {
    return (queue->front == -1);
}

int isFull(struct Queue* queue) {
    return (queue->rear == queue->capacity - 1);
}

void enqueue(struct Queue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    if (queue->front == -1) {
        queue->front = 0; 
    }
    queue->arr[++queue->rear] = value;
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int value = queue->arr[queue->front];
    if (queue->front == queue->rear) {  
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return value;
}

void reverseQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        return;
    }
    
    int frontElement = dequeue(queue);

    reverseQueue(queue);

    enqueue(queue, frontElement);
}

void displayQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of elements in the queue: ");
    scanf("%d", &n);

    struct Queue* queue = createQueue(n);
    
    printf("Enter %d elements for the queue: \n", n);
    for (int i = 0; i < n; i++) {
        int value;
        printf("Enter element %d: ", i + 1);
        scanf("%d", &value);
        enqueue(queue, value);
    }

    printf("Original Queue: ");
    displayQueue(queue);

    reverseQueue(queue);

    printf("Reversed Queue: ");
    displayQueue(queue);
    
    return 0;
}

