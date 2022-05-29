/*
 * Ara Vardanyan, Jason Pyke
 * CSE 374 22sp HW 6
 * Memory Manager
 * freemem.c
 * implementation of freemem function
 */

#include <stdio.h>

#include "mem.h"
#include "mem_impl.h"

void freemem(void* p) {
    if (p == NULL) {
        return;
    }
    check_heap();
    Node* nextNode = head;
    Node* prev = NULL;

    Node* new_node = (Node*)((uintptr_t)p - OFFSET);
    Node* right = (Node*)((uintptr_t)new_node + new_node->size + OFFSET);

    // updating bytes in free list
    total_free_glob += new_node->size + OFFSET;

    // current mem address is less than new node mem address
    while (nextNode != NULL && (nextNode <= new_node)) {
        prev = nextNode;
        nextNode = nextNode->next;
    }

    // front of list
    if (prev == NULL) {
        new_node->next = head;
        n_free_blocks_glob += 1;
        head = new_node;
    } else if (nextNode == NULL) {
        // reached the end of list, mem address must be greater than all node's
        // mem address
        prev->next = new_node;
        new_node->next = NULL;
        n_free_blocks_glob += 1;
    }

    Node* left = NULL;
    if (prev != NULL) {
        left = (Node*)((uintptr_t)new_node - prev->size - OFFSET);
    }

    // in between nodes, current mem address > new_node mem address
    // acquiring address of left adjacent block, prev corresponds to left

    // if both adjacent blocks have same address
    if (right && right == nextNode && left && left == prev) {
        prev->size = prev->size + new_node->size + nextNode->size + (OFFSET * 2);
        prev->next = right->next;
        n_free_blocks_glob -= 1;
    } else if (right && right == nextNode) {
        // only right adjacent has same address
        new_node->size = new_node->size + nextNode->size + OFFSET;
        new_node->next = nextNode->next;
        if (prev) {
            prev->next = new_node;
        }
    } else if (left && left == prev) {
        // only left adjacent has same address
        prev->size = prev->size + new_node->size + OFFSET;
        prev->next = nextNode;
    } else {
        // neither, inserting between adjacent blocks
        new_node->next = nextNode;
        if (prev) {
            prev->next = new_node;
        }
        n_free_blocks_glob += 1;
    }
    check_heap();
}
