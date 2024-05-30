//Write a program in CUDA to perform parallel Sparse Matrix - Vector multiplication using com-
//pressed sparse row (CSR) storage format. Represent the input sparse matrix in CSR format in the
//host code.

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <string.h>
#include <stdio.h>

// Define matrix dimensions (M and N)
#define M 4
#define N 4

__global__ void onesComplement(int *inMat, int *outMat, int rows, int cols)
{
    int r = blockIdx.y * blockDim.y + threadIdx.y;
    int c = blockIdx.x * blockDim.x + threadIdx.x;

    if (r >= 0 && r < rows && c >= 0 && c < cols)
    {
        if (r > 0 && r < rows - 1 && c > 0 && c < cols - 1)
        {
            // Calculate the index for the current element
            int idx = r * cols + c;
            // Calculate the 1's complement of the element and store it in outMat
            int num = inMat[idx];
            int rev = 0;
            for (int i = 0; num > 0; i++)
            {
                rev *= 10;
                rev += 1 - num % 2;
                num = num / 2;
            }
            outMat[idx] = rev;
        }
        else
        {
            // Copy border elements as-is
            outMat[r * cols + c] = inMat[r * cols + c];
        }
    }
}

int main()
{
    int inMat[M][N];
    int outMat[M][N];

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            inMat[i][j] = i * N + j;
        }
    }

    int *dInMat, *dOutMat; // Device pointers for matrices inMat and outMat

    cudaMalloc((void **)&dInMat, M * N * sizeof(int));
    cudaMalloc((void **)&dOutMat, M * N * sizeof(int));
    cudaMemcpy(dInMat, inMat, M * N * sizeof(int), cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((N + threadsPerBlock.x - 1) / threadsPerBlock.x, (M + threadsPerBlock.y - 1) / threadsPerBlock.y);

    onesComplement<<<numBlocks, threadsPerBlock>>>(dInMat, dOutMat, M, N);

    cudaMemcpy(outMat, dOutMat, M * N * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Matrix inMat:\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", inMat[i][j]);
        }
        printf("\n");
    }

    printf("Matrix outMat (1's complement of non-border elements in binary):\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", outMat[i][j]);
        }
        printf("\n");
    }

    cudaFree(dInMat);
    cudaFree(dOutMat);

    return 0;
}
