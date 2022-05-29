/*
 * Ara Vardanyan, Jason Pyke
 * CSE 374 22sp HW 6
 * Memory Manager
 * print_heap.c
 * implementation of print_heap function
 */

#include <stdio.h>

#include "mem_impl.h"

void print_heap(FILE* f) {
    printf("---Printing heap---\n");
    Node* current = head;

    while (current != NULL) {
        // format: Address: [address], Length: [length]
        fprintf(f, "Address: %s%lx", PRIxPTR, (uintptr_t)current);
        fprintf(f, ", Length: %s%lx", PRIxPTR, current->size);
        fprintf(f, "\n");
        current = current->next;
    }
    fprintf(f, "---End of heap---\n");
}
