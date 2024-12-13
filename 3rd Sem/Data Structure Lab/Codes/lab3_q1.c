// Reverse an array using pointers

#include <stdio.h>
#include <stdlib.h>

void Reverse(int *arr, int size) {
    int *start = arr; 
    int *end = arr + size - 1; 
    int temp;

    while (start < end) {
        temp = *start;           
        *start = *end;           
        *end = temp;             
        start++;        
        end--;     
    }
}

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);
    //int arr[n]

    int *arr = (int*)calloc(n,sizeof(int));

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    Reverse(arr, n);

    printf("Reversed array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

