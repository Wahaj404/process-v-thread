#include "map-reduce.h"
#include "util.h"

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int reduceHelper(int const *arr, int lo, int hi, int val, Reducer reducer) {
    for (int i = lo; i < hi; ++i) {
        val = reducer(val, arr[i]);
    }
    return val;
}

int reduce(int const *arr, int size, int val, Reducer reducer) {
    int fd[2];
    pipe(fd);
    int processCount = size / THRESHOLD;
    int remaining = size % THRESHOLD;
    for (int i = 0; i < processCount; ++i) {
        if (fork() == 0) {
            close(fd[0]);
            int lo = i * THRESHOLD, hi = (i + 1) * THRESHOLD;
            int red = reduceHelper(arr, lo, hi, val, reducer);
            write(fd[1], &red, sizeof(red));
            close(fd[1]);
            exit(0);
        }
    }
    int lo = processCount * THRESHOLD, hi = lo + remaining;
    int rem = reduceHelper(arr, lo, hi + remaining, val, reducer);
    val = reducer(val, rem);
    for (int i = 0; i < processCount; ++i) {
        wait(NULL);
    }
    for (int i = 0; i < processCount; ++i) {
        int red = 0;
        read(fd[0], &red, sizeof(red));
        val = reducer(val, red);
    }
    close(fd[0]);
    close(fd[1]);
    return val;
}