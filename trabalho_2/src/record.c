#include "record.h"


Record_t* new_record(__int64_t data) {

    Record_t* record = (Record_t*) malloc(RECORD_SIZE);
    record->data = data;

    return record;
}

void print_record(Record_t* record) {

    printf("%08X", record->data);
}
