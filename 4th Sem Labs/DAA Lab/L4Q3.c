#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int val;
} GraphNode;

typedef struct Node {
    GraphNode gNode;
    struct Node *next;
} Node;

typedef struct {
    GraphNode nodes[100];
    int tos;
} Stack;

typedef struct {
    int n;
    Node **adjLists;
    GraphNode *nodes;
} Graph;

typedef struct {
    GraphNode *nodes;
    int front, rear;
} Queue;

void insertEnd(Node **list, GraphNode node);
Graph createGraph(int);

void enQueue(Queue *q, GraphNode n) {
    if (q->front == -1)
        q->front = 0;
    q->nodes[++(q->rear)] = n;
}

GraphNode deQueue(Queue *q) {
    GraphNode tempNode = q->nodes[(q->front)++];
    if (q->front > q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    return tempNode;
}

void bfs(Graph g, int x, int visited[]) {

    Queue q;
    q.nodes = (GraphNode *)malloc(g.n * sizeof(GraphNode));
    q.front = -1;
    q.rear = -1;
    int ind = 0;
    Node *temp;
    GraphNode gtemp;

    enQueue(&q, g.nodes[0]);
    visited[0] = 1;
    while (q.front != -1) {
        gtemp = deQueue(&q);
        printf("Node %d dequeued at position %d\n", gtemp.index + 1, ind++);
        if (gtemp.val == x) {
            printf("Value found at node %d\n", gtemp.index + 1);
            return;
        }
        temp = g.adjLists[gtemp.index];
        while (temp != NULL) {
            if (visited[temp->gNode.index] == 0) {
                enQueue(&q, temp->gNode);
                visited[temp->gNode.index] = 1;
            }
            temp = temp->next;
        }
    }
    printf("Value not found.\n");
}

int main() {
    int n, x;
    printf("Enter number of nodes in graph ");
    scanf("%d", &n);
    int *visited = (int *)calloc(n, sizeof(int));
    Graph g = createGraph(n);
    printf("Enter value to search for ");
    scanf("%d", &x);
    bfs(g, x, visited);

    // Free allocated memory
    for (int i = 0; i < g.n; i++) {
        Node *current = g.adjLists[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(g.adjLists);
    free(g.nodes);
    free(visited);

    return 0;
}

void insertEnd(Node **list, GraphNode node) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->gNode = node;
    newNode->next = NULL;
    if (*list == NULL)
        *list = newNode;
    else {
        Node *temp = *list;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

Graph createGraph(int n) {
    Graph g;
    g.n = n;
    int i, x, j;
    g.nodes = (GraphNode *)malloc(n * sizeof(GraphNode));
    g.adjLists = (Node **)malloc(n * sizeof(Node *));
    for (i = 0; i < n; i++) {
        g.adjLists[i] = NULL;
        g.nodes[i].index = i;
        printf("Enter the value for vertex %d ", (i + 1));
        scanf("%d", &(g.nodes[i].val));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j) {
                printf("Is vertex %d (val %d) connected to vertex %d (val %d) ? Type 1 if yes, 0 if no ", (i + 1), g.nodes[i].val, (j + 1), g.nodes[j].val);
                scanf("%d", &x);
                if (x == 1) {
                    insertEnd(&(g.adjLists[i]), g.nodes[j]);
                }
            }
        }
    }
    return g;
}

