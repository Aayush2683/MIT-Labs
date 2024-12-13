// Iterative Linear Search in 1D array
#include <stdio.h>

int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int main() {
    int numElements, searchKey;

    printf("Enter the total number of elements in the array: ");
    scanf("%d", &numElements);

    int array[numElements];

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < numElements; i++) {
        scanf("%d", &array[i]);
    }

    printf("Enter the element you want to search for: ");
    scanf("%d", &searchKey);

    int resultIndex = linearSearch(array, numElements, searchKey);

    if (resultIndex != -1) {
        printf("Element '%d' found at index - %d.\n", searchKey, resultIndex);
    } else {
        printf("Element not found in the array.\n");
    }

    return 0;
}

