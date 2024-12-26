#include"my_malloc.h"
void initMemoryPool() {

    head->size = MEMORY_SIZE - BLOCK_SIZE;
    head->next = NULL;
    head->is_used = 1; // Mark as free
}
Block *find_free_block(short size) {
    Block *current = head;
    while (current) {
        if (current->is_used && current->size >= size) {
            return current;
        }
        current = current->next;
        printf("Block found and %p\n",(char *)current);
    }
    return NULL; // No suitable block found
}
void split_block(Block* b, short size) {
    Block* newBlock = (Block*)((char*)b + BLOCK_SIZE + size);
    newBlock->size = b->size - size - BLOCK_SIZE;
    newBlock->next = b->next;
    newBlock->is_used = 1;
    b->size = size+BLOCK_SIZE;
    b->next = newBlock;
    printf("Block splitted in function %d new block size is %d\n",b->size,newBlock->size);
}

void* my_malloc(short size) {
    if (size <0)
    {
        return NULL;
        printf("Size is negative\n");
    }
    if (!flag) {
        initMemoryPool();
        printf("Memory pool initialized\n");
        flag = 1;
    }
    Block* succBlock = find_free_block(size);
    if (succBlock) {
        if (succBlock->size > size + BLOCK_SIZE) {
            split_block(succBlock, size);
            printf("Block splitted\n");
        }
        succBlock->is_used = 0;
        printf("Block allocated\n");
        printf("Block size is %d\n",succBlock->size);
        printf("Block next is %p\n",succBlock->next);
        printf("Block next size is %d\n",succBlock->next->size);
        printf("Block is used %p\n",(char *)succBlock);
        printf("Block size is %d\n",BLOCK_SIZE);
        printf("pointer is %p\n",(succBlock+1));
        return (void*)(succBlock + 1);
    }else{
        return NULL;
        printf("No suitable block found\n");
    }

}
void* my_free(void* ptr) {
    if (!ptr) {
        return NULL;
    }
    Block* block =ptr-(BLOCK_SIZE);
    block->is_used = 1;
    printf("Block freed\n");
    if (block->next && block->next->is_used) {
        block->size += block->next->size + BLOCK_SIZE;
        block->next = block->next->next;
        if(block->size >MEMORY_SIZE)block->size=MEMORY_SIZE;
        printf("Block merged\n");
        printf("Block size is %d\n",block->size);
    }

}

