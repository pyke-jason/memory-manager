# Ara Vardanyan, Jason Pyke
# CSE 374 22sp HW 6
# Memory Manager
# Makefile

#!/bin/bash	

CC=gcc
CFLAGS=-std=c17 -Wall -g
OFILES =bench.o getmem.o freemem.o get_mem_stats.o mem_utils.o print_heap.o

bench: $(OFILES)
	$(CC) $(CFLAGS) -o bench $(OFILES)

test: bench
	./bench

bench.o: bench.c mem.h
	$(CC) $(CFLAGS) -c bench.c

getmem.o: getmem.c mem_utils.c mem.h mem_impl.h
	$(CC) $(CFLAGS) -c getmem.c

freemem.o: freemem.c mem_utils.c mem.h mem_impl.h
	$(CC) $(CFLAGS) -c freemem.c

get_mem_stats.o: get_mem_stats.c mem.h
	$(CC) $(CFLAGS) -c get_mem_stats.c

mem_utils.o: mem_utils.c mem.h mem_impl.h
	$(CC) $(CFLAGS) -c mem_utils.c

print_heap.o: print_heap.c

clean:
	rm -f *.o t9 *~
