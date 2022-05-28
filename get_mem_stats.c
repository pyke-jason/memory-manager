/*
 * Ara Vardanyan, Jason Pyke
 * CSE 374 22sp HW 6
 * Memory Manager
 * get_mem_stats.c
 * implementation of get_mem_stats function
 */

#include <stdio.h>
#include <mem.h>
#include <mem_impl.h>

void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
                   uintptr_t* n_free_blocks) {
    *total_size = total_size_glob;
    *total_free = total_free_glob;
    *n_free_blocks = n_free_blocks_glob;
}
