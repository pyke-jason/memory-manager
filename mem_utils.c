/*
 * Ara Vardanyan, Jason Pyke
 * CSE 374 22sp HW 6
 * Memory Manager
 * mem_utils.c
 * implementation of check_heap function
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "mem.h"
#include "mem_impl.h"

#define MIN_SIZE 16

void check_heap() {
#ifndef DNDEBUG
    // If no free list
    if (!head) {
        return;
    }
    Node *current = head;
    while (current != NULL) {
        // asserting block sizes > minimum size
        assert(current->size >= MIN_SIZE);

        Node *nextNode = current->next;

        if (nextNode != NULL) {
            // asserting blocks are ordered with increasing memory addresses
            assert(current < nextNode);
            // asserting blocks do not overlap and are not touching
            assert((uintptr_t)current + current->size + OFFSET <
                   (uintptr_t)nextNode);
        }
        current = current->next;
    }
#endif
}
