// Matrix Multiplication

#include <stdio.h>
#include <stdlib.h>

void inputMatrix(int **matrix, int rows, int cols) {
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void displayMatrix(int **matrix, int rows, int cols) {
    printf("Matrix is:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void multiplyMatrices(int **mat1, int **mat2, int **result, int r1, int c1, int r2, int c2) {
    if (c1 != r2) {
        printf("Matrix multiplication is not possible. Number of columns of matrix 1 must equal number of rows of matrix 2.\n");
        return;
    }

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

int main() {
    int r1, c1, r2, c2;

    printf("Enter rows and columns for matrix 1: ");
    scanf("%d %d", &r1, &c1);

    printf("Enter rows and columns for matrix 2: ");
    scanf("%d %d", &r2, &c2);

    if (c1 != r2) {
        printf("Matrix multiplication is not possible. The number of columns of matrix 1 must equal the number of rows of matrix 2.\n");
        return 0;
    }

    int **mat1 = (int **)malloc(r1 * sizeof(int *));
    for (int i = 0; i < r1; i++) {
        mat1[i] = (int *)malloc(c1 * sizeof(int));
    }

    int **mat2 = (int **)malloc(r2 * sizeof(int *));
    for (int i = 0; i < r2; i++) {
        mat2[i] = (int *)malloc(c2 * sizeof(int));
    }

    int **result = (int **)malloc(r1 * sizeof(int *));
    for (int i = 0; i < r1; i++) {
        result[i] = (int *)malloc(c2 * sizeof(int));
    }

    printf("Matrix 1:\n");
    inputMatrix(mat1, r1, c1);
    printf("Matrix 2:\n");
    inputMatrix(mat2, r2, c2);

    printf("\nMatrix 1:\n");
    displayMatrix(mat1, r1, c1);
    printf("\nMatrix 2:\n");
    displayMatrix(mat2, r2, c2);

    multiplyMatrices(mat1, mat2, result, r1, c1, r2, c2);

    printf("\nProduct of Matrix 1 and Matrix 2 is:\n");
    displayMatrix(result, r1, c2);

    for (int i = 0; i < r1; i++) {
        free(mat1[i]);
    }
    free(mat1);

    for (int i = 0; i < r2; i++) {
        free(mat2[i]);
    }
    free(mat2);

    for (int i = 0; i < r1; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}

