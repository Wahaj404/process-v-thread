#include "map-reduce.h"

#include "util.h"

#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int mapReduce(int const *arr, int size, int init, Mapper mapper,
              Reducer reducer) {
    int id = shmget(IPC_PRIVATE, size * sizeof(int), IPC_CREAT | 0666);
    if (id < 0) {
        die("shmget");
    }
    int *brr = shmat(id, NULL, 0);
    if (brr == (void *) -1) {
        die("shmat");
    }
    map(arr, size, brr, mapper);
    int ret = reduce(brr, size, init, reducer);
    shmdt(brr);
    shmctl(id, IPC_RMID, NULL);
    return ret;
}