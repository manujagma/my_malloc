#ifndef MY_MALLOC_H
#define MY_MALLOC_H


#include <stdio.h>
#include <stddef.h>
typedef struct Block {
    short size;
    struct Block* next;
    short is_used;
} Block;
#define MEMORY_SIZE 25000
#define BLOCK_SIZE sizeof(Block)
static char flag = 0;
char memory[MEMORY_SIZE];

void initMemoryPool();

Block *find_free_block(short size);
//@size 
//
//

void split_block(Block* b, short size); 
void* my_malloc(short size);
void* my_free(void* ptr);


#endif // MY_MALLOC_H