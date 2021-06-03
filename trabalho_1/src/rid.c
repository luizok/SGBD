#include "rid.h"


Rid_t* new_rid() {

    Rid_t* rid = (Rid_t*) malloc(RID_SIZE);
    
    return rid;
}

void print_rid(Rid_t* rid) {

    if(rid != NULL)
        printf("<page=%d, slot=%d>", rid->page, rid->slot);
    else
        printf("<NULL_RID>");
}