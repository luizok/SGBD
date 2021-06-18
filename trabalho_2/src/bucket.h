#ifndef BUCKET_H
#define BUCKET_H


#include <stdlib.h>
#include <stdio.h>
#include "record.h"
#include "bucket.h"


typedef struct Bucket {
    __uint32_t local_depth;
    __uint32_t n_records;
    Record_t** records;
    int index; // TEST PURPOSES
    // struct Bucket* next;
} Bucket_t;

#define BUCKET_SIZE sizeof(Bucket_t)

Bucket_t* new_bucket(__uint32_t local_depth, __uint32_t n_records);
void print_bucket(Bucket_t* bucket);
void add_record_to_bucket(Record_t* record, Bucket_t* bucket);

#endif