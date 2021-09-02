#include <stdio.h>

#define ARR_SIZE(x)  (sizeof(x) / sizeof((x)[0]))
#define MY_ARR_SIZE 10


void swap(int *a, int *b) {
    int c = *b;
    *b = *a;
    *a = c;
}

void bubble_sort(int arr[], int arr_size) {
    for(int i = 0; i < arr_size-1; i++) {
        for(int k = 0; k < arr_size-1; k++) {
            if(arr[k] > arr[k+1])
                swap(&arr[k], &arr[k+1]);
        }
    }
}

void print_array(int arr[], int arr_size) {
    for(int i = 0; i < arr_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[MY_ARR_SIZE] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    bubble_sort(arr, MY_ARR_SIZE);
    print_array(arr, MY_ARR_SIZE);
    return 0;
}