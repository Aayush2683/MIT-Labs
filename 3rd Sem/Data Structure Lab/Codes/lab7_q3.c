#include <stdio.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int data[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

void enqueue(Queue *q, int value) {
    if (q->rear < MAX_QUEUE_SIZE - 1) {
        q->rear++;
        q->data[q->rear] = value;
    }
}

int dequeue(Queue *q) {
    if (q->front <= q->rear) {
        int value = q->data[q->front];
        q->front++;
        return value;
    }
    return -1; 
}

bool isEmpty(Queue *q) {
    return q->front > q->rear;
}

bool canGoTogether(int N, int K) {
    Queue q;
    initQueue(&q);

    for (int i = 1; i <= N; i++) {
        enqueue(&q, i);
    }
    while (!isEmpty(&q)) {
        int group[3] = {-1, -1, -1};
        int groupSize = 0;

        for (int i = 0; i < 3 && !isEmpty(&q); i++) {
            group[groupSize++] = dequeue(&q);
        }

        bool vigneshFound = false, lataFound = false;
        for (int i = 0; i < groupSize; i++) {
            if (group[i] == K) vigneshFound = true;
            if (group[i] == K + 1) lataFound = true;
        }

        if (vigneshFound && lataFound) {
            return true; 
        }
    }

    return false; 
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N, K;
        scanf("%d %d", &N, &K);

        if (canGoTogether(N, K)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}
