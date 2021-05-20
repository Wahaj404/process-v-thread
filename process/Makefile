CC=gcc
CFLAGS=-std=c17 -c -g
# CFLAGS=-std=c17 -c -O3

all: map-reduce merge quick

map-reduce: map-reduce-main.o map.o reduce.o map-reduce.o util.o
	$(CC) map-reduce-main.o map.o reduce.o map-reduce.o util.o -o map-reduce

map-reduce-main.o: map-reduce-main.c map-reduce.h util.h
	$(CC) $(CFLAGS) map-reduce-main.c -o map-reduce-main.o

map.o: map.c map-reduce.h util.h
	$(CC) $(CFLAGS) map.c -o map.o

reduce.o: reduce.c map-reduce.h util.h
	$(CC) $(CFLAGS) reduce.c -o reduce.o

map-reduce.o: map-reduce.c map-reduce.h util.h
	$(CC) $(CFLAGS) map-reduce.c -o map-reduce.o

merge: merge-main.o merge.o util.o
	$(CC) merge-main.o merge.o util.o -o merge

merge-main.o: merge-main.c merge.h util.h
	$(CC) $(CFLAGS) merge-main.c -o merge-main.o

merge.o: merge.c merge.h util.h
	$(CC) $(CFLAGS) merge.c -o merge.o

quick: quick-main.o quick.o util.o
	$(CC) quick-main.o quick.o util.o -o quick

quick-main.o: quick-main.c quick.h util.h
	$(CC) $(CFLAGS) quick-main.c -o quick-main.o

quick.o: quick.c quick.h util.h
	$(CC) $(CFLAGS) quick.c -o quick.o

util.o: util.c util.h
	$(CC) $(CFLAGS) util.c -o util.o

clean:
	rm -f *.o
	rm -f map-reduce merge quick