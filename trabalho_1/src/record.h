#ifndef RECORD_H
#define RECORD_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


typedef struct Record {
    BYTE data;
} Record_t;

#define RECORD_SIZE sizeof(Record_t)

Record_t* new_record(BYTE data);
void print_record(Record_t* record);


#endif
