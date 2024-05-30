#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to calculate the total cost of assignments
int calculate_cost(int *assignments, int **costs, int n) {
    int total_cost = 0;
    for (int i = 0; i < n; i++) {
        total_cost += costs[i][assignments[i] - 1]; // Adjusting index to start from 1
    }
    return total_cost;
}

// Function to perform brute force search for optimal assignment
void brute_force_assignment(int **costs, int n) {
    int *optimal_assignment = (int*)malloc(n * sizeof(int));
    int min_cost = INT_MAX;
    int opcount = 0;

    // Initialize assignments array with initial indices
    int *assignments = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        assignments[i] = i + 1; // Adjusting index to start from 1
    }

    // Heap's algorithm for generating permutations
    void generate_permutations(int k) {
        if (k == 1) {
            int cost = calculate_cost(assignments, costs, n);
            opcount++; // Count the number of operations
            if (cost < min_cost) {
                min_cost = cost;
                for (int i = 0; i < n; i++) {
                    optimal_assignment[i] = assignments[i];
                }
            }
        } else {
            generate_permutations(k - 1);
            for (int i = 0; i < k - 1; i++) {
                if (k % 2 == 0) {
                    int temp = assignments[i];
                    assignments[i] = assignments[k - 1];
                    assignments[k - 1] = temp;
                } else {
                    int temp = assignments[0];
                    assignments[0] = assignments[k - 1];
                    assignments[k - 1] = temp;
                }
                generate_permutations(k - 1);
            }
        }
    }

    // Generate all permutations recursively
    generate_permutations(n);

    // Print the optimal assignment
    printf("Optimal Assignment: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", optimal_assignment[i]);
    }
    printf("\nMinimum Cost: %d\n", min_cost);
    printf("Operation Count: %d\n", opcount);

    free(assignments);
    free(optimal_assignment);
}

int main() {
    int n;
    printf("Enter the size of the cost matrix: ");
    scanf("%d", &n);

    // Allocate memory for cost matrix
    int **cost_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        cost_matrix[i] = (int*)malloc(n * sizeof(int));
    }

    // Input cost matrix from user
    printf("Enter the elements of the cost matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost_matrix[i][j]);
        }
    }

    // Perform brute force search
    brute_force_assignment(cost_matrix, n);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(cost_matrix[i]);
    }
    free(cost_matrix);

    return 0;
}
