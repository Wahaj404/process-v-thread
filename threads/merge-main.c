#include "merge.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = (int *) malloc(sizeof(int) * MAX_LENGTH);
    for (int i = 0; scanf("%d", arr + i) != EOF; ++i) {}
    mergeSort(arr, MAX_LENGTH);
    free(arr);
}