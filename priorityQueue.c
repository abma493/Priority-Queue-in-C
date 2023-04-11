#include "priorityQueue.h"
#include<stdio.h>

/*swaps two elements in an array of a generic type*/
void swap(void**, int32_t, int32_t, int32_t);

PriorityQueue* priorityQueue(size_t mem_size, 
                             int (*fptr)(void*, void*), 
                             void (*pptr)(struct PriorityQueue*))
{
    PriorityQueue* pq = (PriorityQueue*) malloc(sizeof(PriorityQueue));
    pq->size = 0;
    pq->capacity = DEF_SZ;
    pq->mem_size = mem_size;
    pq->flags = (short*) malloc(DEF_SZ * sizeof(short));
    memset(pq->flags, FALSE, pq->capacity * sizeof(short));
    pq->heap = (void**) malloc(DEF_SZ * sizeof(void*));
    pq->compare = fptr;
    pq->to_str = pptr;

    return pq;
}

int16_t add(PriorityQueue* pq, const void* data)
{
    // if the heap needs to be increased in size
    if(pq->size + 1 >= pq->capacity)
    {
        pq->capacity *= 2;
        pq->heap = realloc(pq->heap, (pq->capacity * pq->mem_size));
        pq->flags = realloc(pq->flags, (pq->capacity * sizeof(short)));
        memset(pq->flags, FALSE, pq->capacity * sizeof(short));
    }
    if(pq->heap == NULL)
        return EXIT_FAILURE;
    
    // allocate the void pointer to the size of requested insert data
    pq->heap[pq->size + 1] = malloc(pq->mem_size);

    // insert the data into the heap
    memcpy(pq->heap[pq->size + 1], data, pq->mem_size);

    // percolate UP
    int32_t index = pq->size + 1;
    short found = FALSE;
    while (found == FALSE && hasParent(pq, index) == TRUE)
    {
        int32_t parent = index / 2;

        int cmp_val = pq->compare(pq->heap[index], pq->heap[parent]);
        if(cmp_val < 0)
        {
            swap(pq->heap, index, parent, pq->mem_size);
            index = parent;
        } else
        {
            found = TRUE;
        }
        
    }

    pq->size = pq->size + 1;
    
    // check if tree level contains a duplicate sibling.
    // If so, flag this element.
    int32_t sibling = index + 1;
    if(sibling < pq->capacity && pq->heap[index] == pq->heap[sibling])
        pq->flags[index] = TRUE;

    return EXIT_SUCCESS;
}

void poll(PriorityQueue* pq, void* data)
{
    memcpy(data, pq->heap[1], pq->mem_size);
    pq->heap[1] = pq->heap[pq->size];

    // percolate DOWN
    int32_t index = 1;
    int16_t found = FALSE;

    while (found == FALSE && hasLeft(pq, index) == TRUE)
    {
        int32_t left = index * 2;
        int32_t right = index * 2 + 1;

        // child that will swap with index if necessary
        int32_t child = left;
        int16_t has_right = hasRight(pq, index);
        if(has_right == TRUE && pq->compare(pq->heap[right], pq->heap[left]) < 0)
        {
            child = right;
        } else if(has_right == TRUE && (pq->flags[left] == TRUE && pq->compare(pq->heap[right], pq->heap[left]) == 0))
        {
            child = right;
        } 

        if(pq->heap[index] > pq->heap[child])
        {
            swap(pq->heap, index, child, pq->mem_size);
            index = child;
        } else 
        {
            found = TRUE;
        }
    }
    pq->size = pq->size - 1;
}

void swap(void** arr, int32_t i1, int32_t i2, int32_t mem_size)
{
    uint8_t temp[mem_size];
    memcpy(temp, *(arr + i1), mem_size);
    memcpy(*(arr + i1), *(arr + i2), mem_size);
    memcpy(*(arr + i2), temp, mem_size);
}

int8_t hasParent(PriorityQueue* pq, int32_t index)
{
    return index > 1 ? TRUE : FALSE;
}

int8_t hasLeft(PriorityQueue* pq, int32_t index)
{
    return index * 2 <= pq->size ? TRUE :  FALSE;
}

int8_t hasRight(PriorityQueue* pq, int32_t index)
{
    return index * 2 + 1 <= pq->size ? TRUE : FALSE;
}

void* peek(const PriorityQueue* pq)
{
    if(pq->size > 0)
    {
        void* temp = pq->heap[1];
        return temp;
    }
}

void clear(PriorityQueue* pq)
{
    int i;
    for (i = 1; i < pq->size; i++)
    {
        free(pq->heap[i]);
    }
    free(pq->heap);
    free(pq->flags);
    free(pq);
}



