#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int heapify(int arr[], int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    int operations = 0; // Variable to count operations

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    operations += 3; // Comparison and assignment operations

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        operations += 3; // Swap operation requires 3 assignments
        operations += heapify(arr, n, largest);
    }

    return operations;
}

void buildMaxHeap(int arr[], int n) {
    int total_operations = 0;
    for (int i = (n / 2) - 1; i >= 0; i--) 
        total_operations += heapify(arr, n, i);
    printf("Total operations during heap construction: %d\n", total_operations);
}

void heapSort(int arr[], int n) {
    buildMaxHeap(arr, n);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) 
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) 
        scanf("%d", &arr[i]);

    printf("Array before sorting:\n");
    printArray(arr, n);

    clock_t start = clock();
    heapSort(arr, n);
    clock_t end = clock();

    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Array after sorting:\n");
    printArray(arr, n);

    printf("Time taken for sorting: %f seconds\n", time_taken);

    return 0;
}
