#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int heapify(int arr[], int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2, ops = 0;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        ops += 3;
        ops += heapify(arr, n, largest);
    }

    return ops;
}

void buildHeap(int arr[], int n) {
    int ops = 0;
    for (int i = n / 2 - 1; i >= 0; i--) ops += heapify(arr, n, i);
    printf("Total operations during heap construction: %d\n", ops);
}

void heapSort(int arr[], int n) {
    buildHeap(arr, n);
    for (int i = n - 1; i > 0; i--) { 
        swap(&arr[0], &arr[i]); 
        heapify(arr, i, 0); 
    }
}

void printArray(int arr[], int n) {
    for (int i = n - 1; i >= 0; --i) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("Array before heapify:\n");
    printArray(arr, n);

    heapSort(arr, n);

    printf("Array after sorting in descending order:\n");
    printArray(arr, n);

    return 0;
}