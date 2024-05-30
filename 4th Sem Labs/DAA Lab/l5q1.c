#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int data[MAX_VERTICES];
    int top;
} Stack;

void push(Stack *s, int vertex) {
    s->data[++s->top] = vertex;
}

int pop(Stack *s) {
    return s->data[s->top--];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

typedef struct {
    int vertices;
    int **adjMatrix;
} Graph;

Graph *createGraph(int vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjMatrix = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = (int *)calloc(vertices, sizeof(int));
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
}

void dfsUtil(Graph *graph, int vertex, int *visited, Stack *stack) {
    visited[vertex] = 1;
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[vertex][i] && !visited[i]) {
            dfsUtil(graph, i, visited, stack);
        }
    }
    push(stack, vertex);
}

void topologicalSortDFS(Graph *graph) {
    Stack stack;
    stack.top = -1;
    int visited[MAX_VERTICES] = {0};

    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            dfsUtil(graph, i, visited, &stack);
        }
    }

    printf("Topological Sort (using Depth-first search):\n");
    while (!isEmpty(&stack)) {
        printf("%d ", pop(&stack));
    }
}

void topologicalSortSourceRemoval(Graph *graph) {
    int indegree[MAX_VERTICES] = {0};

    // Calculate in-degree of each vertex
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->adjMatrix[i][j]) {
                indegree[j]++;
            }
        }
    }

    printf("\nTopological Sort (using Source Removal technique):\n");
    for (int count = 0; count < graph->vertices; count++) {
        int found = 0;
        // Find a vertex with in-degree 0
        for (int i = 0; i < graph->vertices; i++) {
            if (indegree[i] == 0) {
                found = 1;
                printf("%d ", i);
                indegree[i] = -1; // Mark as visited
                // Remove edges associated with this vertex
                for (int j = 0; j < graph->vertices; j++) {
                    if (graph->adjMatrix[i][j]) {
                        indegree[j]--;
                    }
                }
                break;
            }
        }
        if (!found) {
            printf("\nError: Graph contains a cycle!\n");
            return;
        }
    }
}

int main() {
    int vertices, edges, src, dest;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    Graph *graph = createGraph(vertices);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &edges);

    printf("Enter the edges (source destination):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src - 1, dest - 1);
    }

    topologicalSortDFS(graph);
    topologicalSortSourceRemoval(graph);

    return 0;
}
