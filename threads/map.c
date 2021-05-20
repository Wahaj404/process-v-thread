#include "map-reduce.h"
#include "util.h"

#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int const *start;
    int lo;
    int hi;
    int *write;
    Mapper mapper;
} MapArg;

void mapHelper(int const *arr, int lo, int hi, int *write, Mapper mapper) {
    for (int i = lo; i < hi; ++i) {
        write[i] = mapper(arr[i]);
    }
}

void *mapThreadFunc(void *arg) {
    MapArg *marg = (MapArg *) arg;
    mapHelper(marg->start, marg->lo, marg->hi, marg->write, marg->mapper);
    return NULL;
}

void map(int const *arr, int size, int *write, Mapper mapper) {
    int threadCount = size / THRESHOLD;
    int remaining = size % THRESHOLD;
    pthread_t *ids = (pthread_t *) malloc(threadCount * sizeof(pthread_t));
    MapArg *args = (MapArg *) malloc(threadCount * sizeof(MapArg));
    for (int i = 0; i < threadCount; ++i) {
        MapArg arg = {arr, i * THRESHOLD, (i + 1) * THRESHOLD, write, mapper};
        args[i] = arg;
        pthread_create(ids + i, NULL, mapThreadFunc, args + i);
    }
    mapHelper(arr, threadCount * THRESHOLD, threadCount * THRESHOLD + remaining,
              write, mapper);
    for (int i = 0; i < threadCount; ++i) {
        pthread_join(ids[i], NULL);
    }
    free(ids);
    free(args);
}