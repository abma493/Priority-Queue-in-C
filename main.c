#include "priorityQueue.h"
#include"types.h"
#include<stdio.h>

void to_str_int_pq(const PriorityQueue*);
void to_str_str_pq(const PriorityQueue*);
int32_t run_tests_as_int(PriorityQueue*);
int32_t run_tests_as_str(PriorityQueue*);


int main(int argc, char const *argv[])
{
    PriorityQueue* pq_int;
    PriorityQueue* pq_str;  

    printf("\n------------------- INT PQ TEST --------------------\n");
    pq_int = priorityQueue(sizeof(int), &cmp_int, &to_str_int_pq);
    if(run_tests_as_int(pq_int) == 1)
        exit(EXIT_FAILURE);

    printf("\n------------------- STR PQ TEST --------------------\n");

    pq_str = priorityQueue(30 * sizeof(char), &cmp_str, &to_str_str_pq);
    if(run_tests_as_str(pq_str) == 1)
        exit(EXIT_FAILURE);
    printf("\n");
    return 0;
}

int32_t run_tests_as_str(PriorityQueue* pq_str)
{
    char test_strs[5][30] = {"apple", "orange", "cantaloupe", "date", "grape"};

    int i;
    for(i = 0; i < 5; i++)
    {
        int16_t t = add(pq_str, test_strs[i]);
        if(t == 1)
            return EXIT_FAILURE;
        char* ptr = (char*) peek(pq_str);
        printf("The value at the front of this queue is: %s\n", ptr);
        pq_str->to_str(pq_str);
        printf("\n");
    }
    clear(pq_str);
    return EXIT_SUCCESS;
}

int32_t run_tests_as_int(PriorityQueue* pq_int)
{
    int arr[] = {12, 4, 9, 1, 6, 8, 10};
    int i;
    for (i = 0; i < 7; i++)
    {
        int* f = &arr[i];
        int16_t t = add(pq_int, f);
        if(t == 1)
            return EXIT_FAILURE;
        int* k;
        k = peek(pq_int);

        printf("The value at the front of this queue is: %d\n", *k);
        pq_int->to_str(pq_int);
        printf("\n");
    }
    clear(pq_int);

    return EXIT_SUCCESS;
}

void to_str_int_pq(const PriorityQueue* pq)
{
    int i;
    printf("[ ");
    for (i = 1; i <= pq->size; i++)
    {
        printf("%d", *(int*) pq->heap[i]);
        if(i + 1 <= pq->size)
            printf(", ");
    }
    printf(" ]");
}

void to_str_str_pq(const PriorityQueue* pq)
{
    int i;
    printf("[ ");
    for (i = 1; i <= pq->size; i++)
    {
        printf("%s", (char*) pq->heap[i]);
        if(i + 1 <= pq->size)
            printf(", ");
    }
    printf(" ]");

}

