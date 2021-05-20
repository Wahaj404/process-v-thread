#ifndef __UTIL_H__
#define __UTIL_H__

#define MAX_LENGTH 10000000
#define THRESHOLD  (MAX_LENGTH / 12)

void printArray(int const *arr, int size);

void assertSorted(int const *arr, int size);

#define swap(x, y)                                                             \
    int _t = x;                                                                \
    x = y;                                                                     \
    y = _t;

#endif // __UTIL_H__
