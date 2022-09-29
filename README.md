# Memory Manager

A memory manager written in C and compiled with Make, utilizing a block linked-list with headers.

## Description

The free list is a linked list consisting of nodes with fields size and next. The next field points to the right-adjacent node in the free list while the size field contains information about the memory address and size of the node. The freemem function returns a block of storage at the given pointer to the pool of available free storage. The getmem function returns a pointer to a new block of storage with at least the given size in bytes of memory. When a substantially large block is partitioned, we keep the subsequent part of the node on the free list and return the first part of the block to the client. Adjacent blocks in the free list are merged when new memory is added to the free list when freemem is called if the blocks lie adjacent to one another in the underlying system.


## Benchmarks (Preliminary)

`CPU TIME: 40.916ns | Total storage: 29163520, total free storage blocks: 38782, avg free block bytes: 145.72`

For 1 million calls to freemem and getmem, CPU time took about 41 seconds and allocated in total about 3 million bytes of memory. By the end of the benchmark, there were 38,382 total free blocks of storage with an average of 145.72 free bytes per block.


## Credits

Created with Ara Vardanyan in my Intermediate Programming Concepts and Tools class for UW.