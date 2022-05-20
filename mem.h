/*
 * Ara Vardanyan, Jason Pyke
 * CSE 374 22sp HW 6
 * Memory Manager
 * mem.h
 * header file containing declarations of the public functions in the memory
 * manager. This is the interface that clients of getmem/freemem package use.
 */

#ifndef MEM_H
#define MEM_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "mem_impl.h"

// Dont know where to define these yet...
Node* head;
uintptr_t total_size;
uintptr_t total_free;
uintptr_t n_free_blocks;

/* size:    minimum size desired for memory (bytes)
 * returns: pointer to a new block of storage with at least size bytes of memory
 */
void* getmem(uintptr_t size);

/* p: pointer to block of storage
 * returns the block of storage at location p to the pool of available free
 * storage */
void freemem(void* p);

/* total_size:    total amount of storage in bytes acquired by the memory
 * manager so far to use in satisfying allocation requests total_free:    total
 * amount of storage in bytes that is currently stored on the free list,
 *                including any space occupied by header information or links in
 * the free blocks. n_free_blocks: the total number of individual blocks
 * currently stored on the free list stores statistics about the current state
 * of the memory manager in the three integer variables whose addresses are
 * given as argument */
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
                   uintptr_t* n_free_blocks);

/* f: file to print to
 * prints a formatted listing on file f showing the blocks on the free list */
void print_heap(FILE* f);

#endif  // MEM_H
