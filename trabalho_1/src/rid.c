#include "rid.h"


Rid_t* new_rid() {

    Rid_t* rid = (Rid_t*) malloc(RID_SIZE);
    
    return rid;
}