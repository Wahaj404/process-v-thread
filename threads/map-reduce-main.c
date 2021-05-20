#include "map-reduce.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

int mod3(int x) {
    return x % 3;
}

int sum(int x, int y) {
    return x + y;
}

int main() {
    int *arr = (int *) malloc(sizeof(int) * MAX_LENGTH),
        *brr = (int *) malloc(sizeof(int) * MAX_LENGTH);
    for (int i = 0; scanf("%d", arr + i) != EOF; ++i) {}
    mapReduce(arr, MAX_LENGTH, 0, mod3, sum);
}