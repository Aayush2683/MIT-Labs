#include <stdio.h>

void bubbleSort(int arr[], int n, int *comp_count, int *swap_count) {
    int i, j, temp;
    *comp_count = 0;
    *swap_count = 0;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            (*comp_count)++;
            if (arr[j] > arr[j+1]) {
                // swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                (*swap_count)++;
            }
        }
    }
}

void printArray(int arr[], int size) {
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int comp_count, swap_count;
    bubbleSort(arr, n, &comp_count, &swap_count);

    printf("Sorted array: \n");
    printArray(arr, n);

    printf("Number of comparisons: %d\n", comp_count);
    
    return 0;
}
