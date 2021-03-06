#ifndef RECORD_H
#define RECORD_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


typedef struct Record {
    __int64_t data;
} Record_t;

#define RECORD_SIZE sizeof(Record_t)

Record_t* new_record(__int64_t data);
void print_record(Record_t* record);
__int32_t cmp_records(Record_t* r1, Record_t* r2);


#endif
