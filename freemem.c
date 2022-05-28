/*
 * Ara Vardanyan, Jason Pyke
 * CSE 374 22sp HW 6
 * Memory Manager
 * freemem.c
 * implementation of freemem function
 */

#include <stdio.h>

#include <mem.h>
#include <mem_impl.h>

void freemem(void* p) {

    if (p == NULL) {
        return;
    }

    Node* current = head;
    Node* prev = NULL;

    Node* new_node = (Node*) ((uintptr_t) p - 16);
    Node* right = (Node*) ((uintptr_t) new_node + new_node -> size + 16);

    // updating bytes in free list
    total_free_glob += new_node -> size + 16;

    // list is empty
    if (current == NULL) {
        head = new_node;
        new_node -> next = NULL;
        n_free_blocks_glob += 1;
        check_heap();
        return;
    }

    // current mem address is less than new node mem address
    while (current != NULL && (current < right)) {
        prev = current;
        current = current -> next;
    }

    // front of list
    if (prev == NULL) {
        // if head has same mem address, merge
        if (right == head) {
            new_node -> next = head -> next;
            new_node -> size = new_node -> size + head -> size + 16;
        } else {
            new_node -> next = head;
            n_free_blocks_glob += 1;
        }
        head = new_node;
        return;
    }

    // reached the end of list, mem address must be greater than all node's mem address
    if (current == NULL) {
        prev -> next = new_node;
        new_node -> next = NULL;
        n_free_blocks_glob += 1;
        check_heap();
        return;
    }

    // in between nodes, current mem address > new_node mem address

    // acquiring address of left adjacent block, prev corresponds to left
    Node* left = (Node*) ((uintptr_t) prev + prev -> size + 16);

    // if both adjacent blocks have same address
    if (right == current && left == prev) {
        prev -> next = current -> next;
        prev -> size = prev -> size + new_node -> size + current -> size + (16 * 2);
        n_free_blocks_glob -= 1;
    } else if (right == current) {
        // only right adjacent has same address
        new_node -> next = current -> next;
        prev -> next = new_node;
        new_node -> size = new_node -> size + current -> size + 16;
    } else if (left == prev) {
        // only left adjacent has same address
        prev -> size = prev -> size + new_node -> size + 16;
    } else {
        // neither, inserting between adjacent blocks
        new_node -> next = current;
        prev -> next = new_node;
        n_free_blocks_glob += 1;
    }
    check_heap();
}
