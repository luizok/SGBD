#include "record.h"


Record_t* new_record(BYTE data) {

    Record_t* record = (Record_t*) malloc(RECORD_SIZE);
    record->data = data;

    return record;
}

void print_record(Record_t* record) {

    printf("data: %02x\n", record->data);
}
