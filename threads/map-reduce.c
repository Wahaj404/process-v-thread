#include "map-reduce.h"

#include <stdlib.h>

int mapReduce(int const *arr, int size, int init, Mapper mapper,
              Reducer reducer) {
    int *brr = (int *) malloc(sizeof(int) * size);
    map(arr, size, brr, mapper);
    int ret = reduce(brr, size, init, reducer);
    free(brr);
    return ret;
}