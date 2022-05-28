/*
 * Ara Vardanyan, Jason Pyke
 * CSE 374 22sp HW 6
 * Memory Manager
 * getmem.c
 * implementation of getmem function
 */

#include <stdio.h>
#include <stdlib.h>

#include "mem.h"
#include "mem_impl.h"

#define BIG_BLOCK_SIZE 32768
#define MIN_BLOCK_SIZE 128
void *add_node()
{
    Node *res = (Node *)malloc(BIG_BLOCK_SIZE);
    res->size = BIG_BLOCK_SIZE - 16;
    res->next = NULL;
    return res;
}
void *getmem(uintptr_t size)
{
    if (size <= 0)
    {
        return NULL;
    }
    check_heap();
    // round size to nearest 16
    size = (size / 16 + 1) * 16;
    // empty free list
    if (head == NULL)
    {
        head = add_node();
        total_free_glob += head->size + 16;
        n_free_blocks_glob += 1;
    }
    Node *current = head;
    Node *prev = NULL;
    // haven't found large enough memory block
    while (current != NULL && current->size < size)
    {
        prev = current;
        current = current->next;
    }

    // couldn't find big enough block
    if (current == NULL)
    {
        Node *new_node = add_node();
        total_free_glob += new_node->size + 16;
        current = head;
        // current mem address is less than new node mem address
        while (current != NULL && (current < new_node))
        {
            prev = current;
            current = current->next;
        }
        // insert node into list
        prev->next = new_node;
        new_node->next = current;
        current = new_node;
        n_free_blocks_glob += 1;
    }

    // free node we are taking memory from is substantially large
    printf("current size: %ld, alloc size: %ld\n", current->size, size);

    if (current->size - size > MIN_BLOCK_SIZE + 16)
    {
        Node *replacement_node = (Node *)((uintptr_t)current + size + 16);
        replacement_node->size = current->size - size - 16;
        replacement_node->next = current->next;
        current->next = replacement_node;
        current->size = size;
        n_free_blocks_glob += 1;
    }
    total_free_glob -= current->size + 16;
    n_free_blocks_glob -= 1;
    print_heap(stdout);
    // remove allocated node from free list
    if (prev == NULL)
    {
        head = current->next;
    }
    else
    {
        prev->next = current->next;
    }
    check_heap();

    return (Node *)((uintptr_t)current + 16);
}
