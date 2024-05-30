#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

__global__ void spvm(float *data, int num_rows, int *col_index, int *row_ptr, float *x, float *y)
{
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < num_rows)
    {
        float result = 0;
        int row_start = row_ptr[row];
        int row_end = row_ptr[row + 1];
        for (int ele = row_start; ele < row_end; ++ele)
        {
            result += data[ele] * x[col_index[ele]];
        }
        y[row] = result;
    }
}

int main()
{
    int row, col, data_ind = 0;
    printf("Enter no of rows and columns of matrix A: ");
    scanf("%d %d", &row, &col);

    float *data = (float *)malloc(row * col * sizeof(float));
    float *x = (float *)malloc(row * sizeof(float));
    float *y = (float *)malloc(row * sizeof(float));
    int *row_ptr = (int *)malloc((row + 1) * sizeof(int));
    int *col_index = (int *)malloc(row * col * sizeof(int));
    row_ptr[0] = 0;

    printf("Enter sparse matrix A of size %dx%d:\n", row, col);
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            scanf("%f", &data[i * col + j]);
            if (data[i * col + j] > 0)
            {
                col_index[data_ind] = j;
                data[data_ind++] = data[i * col + j];
            }
        }
        row_ptr[i + 1] = data_ind;
    }

    printf("Data: ");
    for (int i = 0; i < data_ind; ++i)
        printf("%f ", data[i]);
    printf("\nColumn_Index: ");
    for (int i = 0; i < data_ind; ++i)
        printf("%d ", col_index[i]);
    printf("\nRow_Ptr: ");
    for (int i = 0; i < row + 1; ++i)
        printf("%d ", row_ptr[i]);

    printf("\nEnter %d elements of x: ", col);
    for (int i = 0; i < row; ++i)
    {
        scanf("%f", &x[i]);
        printf("%f ", x[i]);
    }

    float *d_data, *d_x, *d_y;
    int *d_row_ptr, *d_col_index;

    cudaMalloc((void **)&d_data, (data_ind + 1) * sizeof(float));
    cudaMalloc((void **)&d_x, row * sizeof(float));
    cudaMalloc((void **)&d_y, row * sizeof(float));
    cudaMalloc((void **)&d_row_ptr, (row + 1) * sizeof(int));
    cudaMalloc((void **)&d_col_index, data_ind * sizeof(int));

    cudaMemcpy(d_data, data, (data_ind + 1) * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, x, row * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_row_ptr, row_ptr, (row + 1) * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_col_index, col_index, data_ind * sizeof(int), cudaMemcpyHostToDevice);

    spvm<<<ceil(row / 256.0), 256>>>(d_data, row, d_col_index, d_row_ptr, d_x, d_y);

    cudaMemcpy(y, d_y, row * sizeof(float), cudaMemcpyDeviceToHost);

    printf("\nFinal Vector:\n");
    for (int i = 0; i < row; ++i)
        printf("%f\n", y[i]);

    cudaFree(d_data);
    cudaFree(d_col_index);
    cudaFree(d_y);
    cudaFree(d_x);

    free(data);
    free(x);
    free(y);
    free(row_ptr);
    free(col_index);

    return 0;
}
