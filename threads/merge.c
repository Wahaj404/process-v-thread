#include "merge.h"

#include "util.h"

#include <pthread.h>
#include <stdlib.h>
#include <string.h> // memcpy

typedef struct {
    int *arr;
    int lo;
    int hi;
} ThreadArg;

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

void *mergeSortThreadFunc(void *arg);

void mergeSortHelper(int *arr, int lo, int hi) {
    if (lo + 1 < hi) {
        int mid = lo + (hi - lo) / 2;

        pthread_t id = 0;
        ThreadArg arg = {arr, lo, mid};
        if (mid - lo > THRESHOLD) {
            pthread_create(&id, NULL, mergeSortThreadFunc, &arg);
        } else {
            mergeSortHelper(arr, lo, mid);
        }
        mergeSortHelper(arr, mid, hi);
        if (id != 0) {
            pthread_join(id, NULL);
        }

        merge(arr, lo, mid, hi);
    }
}

void *mergeSortThreadFunc(void *arg) {
    ThreadArg *marg = (ThreadArg *) arg;
    mergeSortHelper(marg->arr, marg->lo, marg->hi);
    return NULL;
}

void mergeSort(int *arr, int size) {
    mergeSortHelper(arr, 0, size);
}