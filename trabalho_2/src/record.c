#include "record.h"


Record_t* new_record(__int64_t data) {

    Record_t* record = (Record_t*) malloc(RECORD_SIZE);
    record->data = data;

    return record;
}

void print_record(Record_t* record) {

    printf("%08X", record->data);
}

__int32_t cmp_records(Record_t* r1, Record_t* r2) {

    if(!r1 || !r2)
        return -2;

    if(r1->data == r2->data) return 0;
    if(r1->data <= r2->data) return -1;
    else return 1;
}
