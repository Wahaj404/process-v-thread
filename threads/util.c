#include "util.h"

#include <stdio.h>

void printArray(int const *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    puts("");
}

void assertSorted(int const *arr, int size) {
    for (int i = 1; i < size; ++i) {
        if (arr[i - 1] > arr[i]) {
            puts("unsorted");
        }
    }
}