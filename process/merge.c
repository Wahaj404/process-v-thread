#include "merge.h"

#include "util.h"

#include <stdlib.h>
#include <string.h> // memcpy
#include <sys/wait.h>
#include <unistd.h>

void merge(int *arr, int lo, int mid, int hi) {
    int const M = mid - lo;
    int const N = hi - mid;
    int *L = (int *) malloc(sizeof(int) * M),
        *R = (int *) malloc(sizeof(int) * N);

    memcpy(L, arr + lo, sizeof(int) * M);
    memcpy(R, arr + mid, sizeof(int) * N);

    int i = 0, j = 0, k = lo;
    while (i < M && j < N) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < M) {
        arr[k++] = L[i++];
    }
    while (j < N) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

void mergeSortHelper(int *arr, int lo, int hi) {
    if (lo + 1 < hi) {
        int mid = lo + (hi - lo) / 2;

        int hasChild = 0;
        if (mid - lo > THRESHOLD) {
            if (fork() == 0) {
                mergeSortHelper(arr, lo, mid);
                exit(0);
            } else {
                hasChild = 1;
            }
        } else {
            mergeSortHelper(arr, lo, mid);
        }
        mergeSortHelper(arr, mid, hi);
        if (hasChild) {
            wait(NULL);
        }
        merge(arr, lo, mid, hi);
    }
}

void mergeSort(int *arr, int size) {
    mergeSortHelper(arr, 0, size);
}