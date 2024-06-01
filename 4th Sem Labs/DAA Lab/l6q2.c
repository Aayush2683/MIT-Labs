#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global variables to store counts
int comparisonCount = 0;
int swapCount = 0;

// Function to swap two elements
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
    swapCount++;
}

// Function to partition the array
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        comparisonCount++;
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Function to implement QuickSort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];

    // Input the elements
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Reset counts
    comparisonCount = 0;
    swapCount = 0;

    // Record the start time
    clock_t start = clock();

    // Sort the array
    quickSort(arr, 0, n - 1);

    // Record the end time
    clock_t end = clock();

    // Calculate the total time taken
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;

    // Print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Print counts
    printf("Comparison count: %d\n", comparisonCount);
    printf("Swap count: %d\n", swapCount);

    // Print the time taken
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}