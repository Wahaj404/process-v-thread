#include "merge.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main() {
    int id = shmget(IPC_PRIVATE, MAX_LENGTH * sizeof(int), IPC_CREAT | 0666);
    if (id < 0) {
        die("shmget");
    }
    int *shm = shmat(id, NULL, 0);
    if (shm == (void *) -1) {
        die("shmat");
    }

    for (int i = 0; scanf("%d", shm + i) != EOF; ++i) {}
    mergeSort(shm, MAX_LENGTH);

    shmdt(shm);
    shmctl(id, IPC_RMID, NULL);
}