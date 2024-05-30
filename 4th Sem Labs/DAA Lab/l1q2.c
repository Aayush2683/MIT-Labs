#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Graph {
    int vertices;
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
};

void init_graph(struct Graph *graph, int vertices) {
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adj_matrix[i][j] = 0;
        }
    }
}

void add_edge(struct Graph *graph, int u, int v) {
    graph->adj_matrix[u][v] = 1;
    graph->adj_matrix[v][u] = 1;
}

void display_adj_list(struct Graph *graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->vertices; i++) {
        printf("%d -> ", i);
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->adj_matrix[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}

void display_adj_matrix(struct Graph *graph) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->adj_matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int vertices, edges;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    struct Graph graph;
    init_graph(&graph, vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(&graph, u, v);
    }

    display_adj_list(&graph);
    display_adj_matrix(&graph);

    return 0;
}
