#include "rid.h"


Rid_t* new_rid(__int32_t page, __int32_t slot) {

    Rid_t* rid = (Rid_t*) malloc(RID_SIZE);
    rid->page = page;
    rid->slot = slot;
    
    return rid;
}

void print_rid(Rid_t* rid) {

    if(!rid)
        printf("NULL_RID");
    else
        printf("<page=%d, slot=%d>", rid->page, rid->slot);
}