#include <stdio.h>
#include <stdlib.h>

// Structs
typedef struct {
    int index;
    int val;
} GraphNode;

typedef struct node {
    GraphNode gNode;
    struct node *next;
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

// Function Declarations
void insertEnd(Node **list, GraphNode node);
Graph createGraph(int n);
void push(Stack *s, GraphNode n);
GraphNode pop(Stack *s);
void dfs(Graph g, int x, int visited[]);

// Function Definitions
void insertEnd(Node **list, GraphNode node) {
    Node *new_node = malloc(sizeof(Node));
    new_node->gNode = node;
    new_node->next = NULL;
    if (*list == NULL)
        *list = new_node;
    else {
        Node *temp = *list;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
    }
}

Graph createGraph(int n) {
    Graph g;
    g.n = n;
    int i, x, j;
    g.nodes = malloc(n * sizeof(GraphNode));
    g.adjLists = malloc(n * sizeof(Node *));
    int **adjMat = calloc(n, sizeof(int *));
    for (i = 0; i < n; i++) {
        adjMat[i] = calloc(n, sizeof(int));
        g.adjLists[i] = NULL;
        g.nodes[i].index = i;
        printf("Enter the value for vertex %d ", (i + 1));
        scanf("%d", &(g.nodes[i].val));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j)
                adjMat[i][i] = 0;
            else {
                if (adjMat[i][j] != 1 && adjMat[i][j] != -1) {
                    printf("Is vertex %d (val %d) connected to vertex %d (val %d) ? Type 1 if yes, 0 if no ", (i + 1), g.nodes[i].val, (j + 1), g.nodes[j].val);
                    scanf("%d", &x);
                    if (x == 1) {
                        insertEnd(&(g.adjLists[i]), g.nodes[j]);
                        insertEnd(&(g.adjLists[j]), g.nodes[i]);
                        adjMat[i][j] = 1;
                        adjMat[j][i] = 1;
                    } else {
                        adjMat[i][j] = -1;
                        adjMat[j][i] = -1;
                    }
                }
            }
        }
    }
    return g;
}

void push(Stack *s, GraphNode n) {
    (s->nodes)[++(s->tos)] = n;
}

GraphNode pop(Stack *s) {
    return s->nodes[(s->tos)--];
}

void dfs(Graph g, int x, int visited[]) {
    Stack s = { .tos = -1 };
    int ind = 0;
    Node *temp = NULL;
    GraphNode gtemp;

    push(&s, g.nodes[0]);
    visited[0] = 1;
    while (s.tos != -1) {
        gtemp = pop(&s);
        printf("Node %d popped at position %d\n", gtemp.index + 1, ind++);
        if (gtemp.val == x) {
            printf("Value found at node %d\n", gtemp.index + 1);
            return;
        }
        temp = g.adjLists[gtemp.index];
        while (temp != NULL) {
            if (!visited[temp->gNode.index]) {
                push(&s, temp->gNode);
                printf("Node %d pushed to stack\n", temp->gNode.index + 1);
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
    int *visited = calloc(n, sizeof(int));
    Graph g = createGraph(n);
    printf("Enter value to search for ");
    scanf("%d", &x);
    dfs(g, x, visited);
    free(visited);
    return 0;
}