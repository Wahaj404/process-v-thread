#ifndef __MAP_H__
#define __MAP_H__

typedef int (*Mapper)(int);
typedef int (*Reducer)(int, int);

void map(int const *start, int size, int *write, Mapper mapper);

int reduce(int const *start, int size, int init, Reducer reducer);

int mapReduce(int const *start, int size, int init, Mapper mapper,
              Reducer reducer);

#endif // __MAP_H__
