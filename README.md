Ara Vardanyan, Jason Pyke
CSE 374 22sp HW 6
Memory Manager
README

Group Identifier: AE

- Who was responsible for which part of the project, and how was the work divided?

Jason was responsible for getmem, the makefile, and debugging. Ara was responsible for freemem and implemented print heap, check heap, and get_mem_stats. Ara and Jason shared responsibility of the benchmark.

- A brief description of how the heap (free list) data structure is organized and the algorithms used to manage it.

The free list is a linked list consisting of nodes with fields size and next. The next field points to the right-adjacent node in the free list while the size field contains information about the memory address and size of the node. The freemem function returns a block of storage at the given pointer to the pool of available free storage. The getmem function returns a pointer to a new block of storage with at least the given size in bytes of memory. When a substantially large block is partitioned, we keep the subsequent part of the node on the free list and return the first part of the block to the client. Adjacent blocks in the free list are merged when new memory is added to the free list when freemem is called if the blocks lie adjacent to one another in the underlying system.

- A summary of any additional features or improvements in your memory manager or benchmark code. If you did any extra credit parts of the assignment, be sure to describe that.

We did not include any notable additional features.

- A summary of the results you observed on several runs of your bench program. This does not need to be exhaustive (and should not be exhausting), but it should give the reader an idea of how your code worked,
  how fast it was, and how efficient it was in its use of memory.

CPU TIME: 0.001ns | Total storage: 0, total free storage blocks: 0, avg free block bytes: 0.00
CPU TIME: 0.446ns | Total storage: 3768320, total free storage blocks: 5260, avg free block bytes: 175.84
CPU TIME: 1.903ns | Total storage: 6422528, total free storage blocks: 9681, avg free block bytes: 149.72
CPU TIME: 4.118ns | Total storage: 9011200, total free storage blocks: 13974, avg free block bytes: 141.55
CPU TIME: 7.304ns | Total storage: 12681216, total free storage blocks: 18239, avg free block bytes: 140.13
CPU TIME: 11.552ns | Total storage: 16121856, total free storage blocks: 22240, avg free block bytes: 140.04
CPU TIME: 17.082ns | Total storage: 19300352, total free storage blocks: 26421, avg free block bytes: 147.74
CPU TIME: 24.253ns | Total storage: 22347776, total free storage blocks: 30511, avg free block bytes: 134.56
CPU TIME: 31.905ns | Total storage: 24969216, total free storage blocks: 34693, avg free block bytes: 128.87
CPU TIME: 40.916ns | Total storage: 29163520, total free storage blocks: 38782, avg free block bytes: 145.72

For 1 million calls to freemem and getmem, CPU time took about 41 seconds and allocated in total about 3 million bytes of memory. By the end of the benchmark, there were 38,382 total free blocks of storage with an average of 145.72 free bytes per block.

- A summary of any resources you consulted for information about memory management algorithms. Your code, of course, must be your own, but feel free to research and explore memory management topics.

w3schools.com
cplusplus.com
cppreference.com
