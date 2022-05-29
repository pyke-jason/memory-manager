/*
 * Ara Vardanyan, Jason Pyke
 * CSE 374 22sp HW 6
 * Memory Manager
 * bench.c
 * benchmarking/test program for Memory Manager
 * executes a large number of calls to functions getmem and freemem to allocate
 * and free blocks of random sizes and in random order. Allow the user to
 * specify parameters that control the test.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <mem.h>

int main(int argc, char **argv) {

    // Setting parameters to default and/or arguments
    int ntrials = 1000;
    int pctget = argc > 2 ? atoi(argv[2]) : 50;
    int pctlarge = argc > 3 ? atoi(argv[3]) : 10;
    int small_limit = argc > 4 ? atoi(argv[4]) : 200;
    int large_limit = argc > 5 ? atoi(argv[5]) : 2000;
    int random_seed = argc > 6 ? atoi(argv[6]) : clock();

    void *memory[ntrials];
    int req_size;
    int end_idx = 0;

    uintptr_t total_size = 0;
    uintptr_t total_free = 0;
    uintptr_t n_free_blocks = 0;

    srand(random_seed);


    for (int i = 0; i < ntrials; i += 1) {

        // if random chance says getmem
        if (rand() % 100 <= pctget) {
            // if random chance says allocate large block
            if (rand() % 100 <= pctlarge) {
                req_size = rand() % (large_limit - small_limit) + small_limit;
            } else {
                req_size = rand() % small_limit + 1;
            }

            memory[end_idx] = getmem(req_size);

            if (memory[end_idx] != NULL) {
                // storing 0xFE in each of first min(16, req_size) bytes of ptr returned by getmem

                int fill_size = 16;
                if (req_size < 16) {
                    fill_size = req_size;
                }
                memset(memory[end_idx], 0xFE, fill_size);
                end_idx += 1;
            }


        } else {
            //freemem case
            if (end_idx > 0) {
                // freeing memory of random previously allocated block
                int free_idx = rand() % end_idx;
                freemem(memory[free_idx]);
                // adjusting memory array bounds
                memory[free_idx] = memory[end_idx - 1];
                end_idx -= 1;
            }
        }

        // printing statistics to stdout
        if (i % (ntrials / 10) == 0) {
            get_mem_stats(&total_size, &total_free, &n_free_blocks);
            double avg =
                n_free_blocks > 0 ? total_free / (double)n_free_blocks : 0;
            printf(

                "CPU TIME: %.3fns | Total storage: %lu, total free storage "
                "blocks: %lu, avg free block bytes: %.2f\n",
                (double)clock() / CLOCKS_PER_SEC, total_size_glob,
                n_free_blocks, avg);
        }


    }



}
