#ifndef RID_H
#define RID_H

#include <stdio.h>
#include <stdlib.h>


typedef struct Rid {
    __int32_t page;
    __int32_t slot;
} Rid_t;

#define RID_SIZE sizeof(Rid_t)

Rid_t* new_rid(__int32_t page, __int32_t slot);
void print_rid(Rid_t* rid);


#endif
