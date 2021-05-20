#include "map-reduce.h"
#include "util.h"

#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int const *start;
    int lo;
    int hi;
    int val;
    Reducer reducer;
} ReduceArg;

int reduceHelper(int const *arr, int lo, int hi, int val, Reducer reducer) {
    for (int i = lo; i < hi; ++i) {
        val = reducer(val, arr[i]);
    }
    return val;
}

void *reduceThreadFunc(void *arg) {
    ReduceArg *rarg = (ReduceArg *) arg;

    int *ret = (int *) malloc(sizeof(int));
    *ret =
        reduceHelper(rarg->start, rarg->lo, rarg->hi, rarg->val, rarg->reducer);
    return ret;
}

int reduce(int const *arr, int size, int val, Reducer reducer) {
    int threadCount = size / THRESHOLD;
    int remaining = size % THRESHOLD;
    pthread_t *ids = (pthread_t *) malloc(threadCount * sizeof(pthread_t));
    ReduceArg *args = (ReduceArg *) malloc(threadCount * sizeof(ReduceArg));
    for (int i = 0; i < threadCount; ++i) {
        ReduceArg arg = {arr, i * THRESHOLD, (i + 1) * THRESHOLD, val, reducer};
        args[i] = arg;
        pthread_create(ids + i, NULL, reduceThreadFunc, args + i);
    }
    val = reducer(val, reduceHelper(arr, threadCount * THRESHOLD,
                                    threadCount * THRESHOLD + remaining, val,
                                    reducer));
    for (int i = 0; i < threadCount; ++i) {
        int *ret = NULL;
        pthread_join(ids[i], (void **) &ret);
        val = reducer(val, *ret);
        free(ret);
    }
    free(ids);
    free(args);
    return val;
}