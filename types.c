#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types.h"

DataType cast_to_type(const void* data, Type type)
{
    DataType value;
    void* ptr;

    value.type = type;
    switch (value.type)
    {
    case INTEGER:
        ptr = malloc(sizeof(int));
        memcpy(ptr, data, sizeof(int));
        value.u_type.integer = *(int*) ptr;
        free(ptr);
        break;
    case STRING:
        int32_t mem_size = DEF_STR_SZ * sizeof(char);
        value.u_type.string = malloc(mem_size);
        memcpy(value.u_type.string, data, mem_size);
        break;
    default:
        value.type = -1;
    }

    return value;
}

void free_str_type(DataType* type)
{
    free(type->u_type.string);
}

int cmp_int(const void* x, const void* y)
{
    int a = *(int*) x;
    int b = *(int*) y;
    if(a == b)
        return 0;
    return a < b ? -1 : 1;  
}

int cmp_str(const void* c1, const void* c2)
{

    char* s1 = (char*) c1;
    char* s2 = (char*) c2;
    return strcmp(s1, s2);
}
