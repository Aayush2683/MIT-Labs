#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Function to dynamically allocate memory for a matrix
int** createMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

// Function to free dynamically allocated memory for a matrix
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to read a matrix from the user
void readMatrix(int** matrix, int rows, int cols) {
    printf("Enter elements of the matrix (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Function to display a matrix
void displayMatrix(int** matrix, int rows, int cols) {
    printf("Matrix (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function for matrix addition
void addMatrices(int** matrixA, int** matrixB, int** result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

// Function for matrix subtraction
void subtractMatrices(int** matrixA, int** matrixB, int** result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
}

// Function for matrix multiplication
void multiplyMatrices(int** matrixA, int** matrixB, int** result, int rowsA, int colsA, int rowsB, int colsB) {
    if (colsA != rowsB) {
        printf("Matrix multiplication is not possible. The number of columns of matrix A must equal the number of rows of matrix B.\n");
        return;
    }
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colsA; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

// Function for element-wise division
void divideMatrices(int** matrixA, int** matrixB, int** result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrixB[i][j] != 0) {
                result[i][j] = matrixA[i][j] / matrixB[i][j];
            } else {
                printf("Error: Division by zero at element [%d][%d].\n", i + 1, j + 1);
                result[i][j] = 0; // Assigning zero in case of division by zero
            }
        }
    }
}

// Function to transpose a matrix
void transposeMatrix(int** matrix, int** result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

// Function to find the determinant of a matrix (only for square matrices)
int determinant(int** matrix, int n) {
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }
    int det = 0;
    int sign = 1;
    int** temp = createMatrix(n, n);
    
    for (int f = 0; f < n; f++) {
        // Getting cofactor of matrix[0][f]
        for (int i = 1; i < n; i++) {
            int colCount = 0;
            for (int j = 0; j < n; j++) {
                if (j == f) continue;
                temp[i - 1][colCount++] = matrix[i][j];
            }
        }
        det += sign * matrix[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    
    freeMatrix(temp, n);
    return det;
}

// Main function to test all the operations
int main() {
    int rowsA, colsA, rowsB, colsB;

    // Read first matrix dimensions
    printf("Enter number of rows and columns for matrix A: ");
    scanf("%d %d", &rowsA, &colsA);
    
    int** matrixA = createMatrix(rowsA, colsA);
    readMatrix(matrixA, rowsA, colsA);
    
    // Read second matrix dimensions
    printf("Enter number of rows and columns for matrix B: ");
    scanf("%d %d", &rowsB, &colsB);
    
    int** matrixB = createMatrix(rowsB, colsB);
    readMatrix(matrixB, rowsB, colsB);

    // Addition
    if (rowsA == rowsB && colsA == colsB) {
        int** resultAdd = createMatrix(rowsA, colsA);
        addMatrices(matrixA, matrixB, resultAdd, rowsA, colsA);
        printf("Matrix A + Matrix B:\n");
        displayMatrix(resultAdd, rowsA, colsA);
        freeMatrix(resultAdd, rowsA);
    } else {
        printf("Matrix addition is not possible. Dimensions must be the same.\n");
    }

    // Subtraction
    if (rowsA == rowsB && colsA == colsB) {
        int** resultSub = createMatrix(rowsA, colsA);
        subtractMatrices(matrixA, matrixB, resultSub, rowsA, colsA);
        printf("Matrix A - Matrix B:\n");
        displayMatrix(resultSub, rowsA, colsA);
        freeMatrix(resultSub, rowsA);
    } else {
        printf("Matrix subtraction is not possible. Dimensions must be the same.\n");
    }

    // Multiplication
    if (colsA == rowsB) {
        int** resultMul = createMatrix(rowsA, colsB);
        multiplyMatrices(matrixA, matrixB, resultMul, rowsA, colsA, rowsB, colsB);
        printf("Matrix A * Matrix B:\n");
        displayMatrix(resultMul, rowsA, colsB);
        freeMatrix(resultMul, rowsA);
    } else {
        printf("Matrix multiplication is not possible. Number of columns in A must equal number of rows in B.\n");
    }

    // Division (element-wise)
    if (rowsA == rowsB && colsA == colsB) {
        int** resultDiv = createMatrix(rowsA, colsA);
        divideMatrices(matrixA, matrixB, resultDiv, rowsA, colsA);
        printf("Matrix A / Matrix B (element-wise):\n");
        displayMatrix(resultDiv, rowsA, colsA);
        freeMatrix(resultDiv, rowsA);
    } else {
        printf("Matrix division is not possible. Dimensions must be the same.\n");
    }

    // Transpose of A
    int** resultTransA = createMatrix(colsA, rowsA);
    transposeMatrix(matrixA, resultTransA, rowsA, colsA);
    printf("Transpose of Matrix A:\n");
    displayMatrix(resultTransA, colsA, rowsA);
    freeMatrix(resultTransA, colsA);

    // Transpose of B
    int** resultTransB = createMatrix(colsB, rowsB);
    transposeMatrix(matrixB, resultTransB, rowsB, colsB);
    printf("Transpose of Matrix B:\n");
    displayMatrix(resultTransB, colsB, rowsB);
    freeMatrix(resultTransB, colsB);

    // Determinant (only for square matrix A)
    if (rowsA == colsA) {
        int detA = determinant(matrixA, rowsA);
        printf("Determinant of Matrix A: %d\n", detA);
    } else {
        printf("Matrix A is not square, determinant cannot be calculated.\n");
    }

    // Free allocated memory for matrices
    freeMatrix(matrixA, rowsA);
    freeMatrix(matrixB, rowsB);

    return 0;
}

