/*
 * Ara Vardanyan, Jason Pyke
 * CSE 374 22sp HW 6
 * Memory Manager
 * mem_impl.h
 * header file with declarations of internal implementation details for check_heap function and
 * free list data structure(s). This is information required in more than one of the implementation
 * files, but that is not part of the public interface, which is declared in file mem.h.
*/

#ifndef MEM_IMPL_H_
#define MEM_IMPL_H_

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

/* Free list data structure will consist of nodes that contain size of usable memory for the node
 * and a pointer to the next node in the list */
typedef struct Node {
    struct Node* next;  // pointer to the next node
    uintptr_t size;  // size of usable memory
} Node;


// add free list data structure
Node* list;
uintptr_t total_size;
uintptr_t total_free;
uintptr_t n_free_blocks;

/* checks for possible problems with the free list data structure.
 * uses assert to verify that the free list has the following properties:
 * blocks are ordered with strictly increasing memory addresses
 * block sizes are positive numbers and no smaller than  minimum size used in implementation
 * blocks do not overlap
 * (the start + length of a block is not an address in the middle of a later block on the list)
 * blocks are not touching (the start + length of a block should not be same address as the next
 * block on the list since in that case the two blocks should be combined into one larger block.)
 * if no errors are detected, this function returns silently after performing these tests.
 * If an error is detected, assert fails and causes the program to terminate at that point. */
void check_heap();

#endif  // MEM_IMPL_H_
