#include "quick.h"

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int partition(int *arr, int lo, int hi) {
    int pivot = arr[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[hi]);
    return i + 1;
}

void quickSortHelper(int *arr, int lo, int hi) {
    if (lo < hi) {
        int pi = partition(arr, lo, hi);
        int hasChild = 0;
        if (pi - 1 - lo > THRESHOLD) {
            if (fork() == 0) {
                quickSortHelper(arr, lo, pi - 1);
                exit(0);
            } else {
                hasChild = 1;
            }
        } else {
            quickSortHelper(arr, lo, pi - 1);
        }
        quickSortHelper(arr, pi + 1, hi);
        if (hasChild) {
            wait(NULL);
        }
    }
}

void quickSort(int *arr, int size) {
    quickSortHelper(arr, 0, size - 1);
}