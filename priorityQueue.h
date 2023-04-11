#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

/**
    A priority queue that can handle generic types and "fair" duplicate insertions.

    This priority queue is implemented as a min-heap using an array.

    @author Abraham Martinez
    @version 1.0 
    @date April 2023
*/

#include<stdint.h> 
#include<stdlib.h>
#include<string.h>

#define DEF_SZ 10

typedef enum boolean { FALSE, TRUE } boolean;

typedef struct PriorityQueue
{
    int16_t size;                           // current size of queue
    int16_t capacity;                       // the capacity of this queue
    ssize_t mem_size;                       // memory size of each queue element
    boolean ptr_flag;                       // queue element is of ptr type (for char*)
    short* flags;                           // "fair" duplicate insertion handler
    void** heap;                            // queue internal structure
    int32_t (*compare)(void*, void*);       // compare function for queue element type
    void (*to_str)(struct PriorityQueue*);  // "to string" function for element type

} PriorityQueue;

/* Constructor for a priority queue*/
PriorityQueue* priorityQueue(size_t mem_size, 
                             int32_t (*fptr)(void*, void*), 
                             void (*pptr)(struct PriorityQueue*),
                             boolean ptr_flag);

/* add function */
int16_t add(PriorityQueue*, const void*);

/* remove function */
void poll(PriorityQueue*, void*);

/* peek function for seeing the front of the queue */
void* peek(const PriorityQueue*);

/* clear the queue by freeing it and its elements */
void clear(PriorityQueue*);

/*member functions for ancestral checks in heap tree */
int8_t hasParent(PriorityQueue*, int32_t);
int8_t hasLeft(PriorityQueue*, int32_t);
int8_t hasRight(PriorityQueue*, int32_t);

#endif