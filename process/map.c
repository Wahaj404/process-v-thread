#include "map-reduce.h"
#include "util.h"

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void mapHelper(int const *arr, int lo, int hi, int *write, Mapper mapper) {
    for (int i = lo; i < hi; ++i) {
        write[i] = mapper(arr[i]);
    }
}

void map(int const *arr, int size, int *write, Mapper mapper) {
    int processCount = size / THRESHOLD;
    int remaining = size % THRESHOLD;
    for (int i = 0; i < processCount; ++i) {
        if (fork() == 0) {
            mapHelper(arr, i * THRESHOLD, (i + 1) * THRESHOLD, write, mapper);
            exit(0);
        }
    }
    mapHelper(arr, processCount * THRESHOLD,
              processCount * THRESHOLD + remaining, write, mapper);
    for (int i = 0; i < processCount; ++i) {
        wait(NULL);
    }
}