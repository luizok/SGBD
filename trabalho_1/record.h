#ifndef RECORD_H
#define RECORD_H

#include <stdio.h>
#include <stdlib.h>


typedef struct Record {
    __uint32_t data;
} Record_t;

#define RECORD_SIZE sizeof(Record_t)

Record_t* new_record(__uint32_t data);
void print_record(Record_t* record);


#endif