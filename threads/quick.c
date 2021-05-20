#include "quick.h"

#include "util.h"

#include <pthread.h>

typedef struct {
    int *arr;
    int lo;
    int hi;
} ThreadArg;

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

void *quickSortThreadFunc(void *arg);

void quickSortHelper(int *arr, int lo, int hi) {
    if (lo < hi) {
        int pi = partition(arr, lo, hi);
        pthread_t id = 0;
        ThreadArg arg = {arr, lo, pi - 1};
        if (arg.hi - arg.lo > THRESHOLD) {
            pthread_create(&id, NULL, quickSortThreadFunc, &arg);
        } else {
            quickSortHelper(arr, lo, pi - 1);
        }
        quickSortHelper(arr, pi + 1, hi);
        if (id != 0) {
            pthread_join(id, NULL);
        }
    }
}

void *quickSortThreadFunc(void *arg) {
    ThreadArg *qarg = (ThreadArg *) arg;
    quickSortHelper(qarg->arr, qarg->lo, qarg->hi);
    return NULL;
}

void quickSort(int *arr, int size) {
    quickSortHelper(arr, 0, size - 1);
}