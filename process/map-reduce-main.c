#include "map-reduce.h"
#include "util.h"

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int mod3(int x) {
    return x % 3;
}

int sum(int x, int y) {
    return x + y;
}

int main() {
    int a = shmget(IPC_PRIVATE, MAX_LENGTH * sizeof(int), IPC_CREAT | 0666);
    if (a < 0) {
        die("shmget");
    }
    int *arr = shmat(a, NULL, 0);
    if (arr == (void *) -1) {
        die("shmat");
    }

    for (int i = 0; scanf("%d", arr + i) != EOF; ++i) {}
    mapReduce(arr, MAX_LENGTH, 0, mod3, sum);

    shmdt(arr);
    shmctl(a, IPC_RMID, NULL);
}