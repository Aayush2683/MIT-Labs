//Write a program in CUDA to read MXN matrix A and replace 1 st row of this matrix by same
//elements, 2 nd row elements by square of each element and 3 rd row elements by cube of each element
//and so on.

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

__global__ void modifyRows(int *mat, int width)
{
    int rowId = threadIdx.x + blockIdx.x * blockDim.x;
    int element;

    for (int colId = 0; colId < width; colId++)
    {
        element = mat[rowId * width + colId];
        mat[rowId * width + colId] = powf(element, rowId + 1);
    }
}

int main()
{
    int matrix[100][100], linearMatrix[10000];
    int *dMatrix, numRows, numCols, matrixSize, index = 0;

    printf("Enter the number of rows and columns of the matrix: ");
    scanf("%d %d", &numRows, &numCols);
    matrixSize = numRows * numCols * sizeof(int);

    printf("Enter the matrix of size %dx%d:\n", numRows, numCols);

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            scanf("%d", &matrix[i][j]);
            linearMatrix[index++] = matrix[i][j];
        }
    }

    cudaMalloc((void **)&dMatrix, matrixSize);
    cudaMemcpy(dMatrix, linearMatrix, matrixSize, cudaMemcpyHostToDevice);

    modifyRows<<<1, numRows>>>(dMatrix, numCols);

    cudaMemcpy(linearMatrix, dMatrix, matrixSize, cudaMemcpyDeviceToHost);

    printf("Resultant Matrix:\n");
    index = 0;

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            matrix[i][j] = linearMatrix[index++];
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    cudaFree(dMatrix);
    return 0;
}
