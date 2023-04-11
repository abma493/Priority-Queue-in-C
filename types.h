#ifndef TYPES_H
#define TYPES_H

/**
    A header file for basic generic data type handling.

    @author Abraham Martinez
    @version 1.0 
    @date April 2023
*/


#include<stdint.h>

#define SCHAR_SZ 8
#define DEF_STR_SZ 100


typedef enum { INTEGER, STRING } Type;

/*
    A generic data type container that handles genericity by
    the use of explicit types.

    Note: String type MUST be free'd using free_str_type!
*/
typedef struct _generic_data
{
    Type type;              
    union union_type
    {
        int32_t integer;
        char* string;
        // more types can be added here.
    } u_type;
} DataType;

/*
    A generic data type container that handles the genericity
    of all x86 machine data types (i.e., char, char*, int, ...)

    Declarations and use of this type are handled by programmer.
*/
typedef struct _gen_data
{
    int8_t value[SCHAR_SZ];     // container for data type
    int8_t ptr_flag;            // element is of pointer type (i.e., char*)
} Data;


DataType cast_to_type(const void* data, Type);
void free_str_type(DataType*);

int cmp_str(const void*, const void*);
int cmp_int(const void*, const void*);

#endif