#ifndef RID_H
#define RID_H

#include <stdio.h>
#include <stdlib.h>


typedef struct Rid {
    __uint32_t page;
    __uint32_t slot;
} Rid_t;

#define RID_SIZE sizeof(Rid_t)

Rid_t* new_rid();
void print_rid(Rid_t* rid);


#endif
