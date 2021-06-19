#ifndef EXT_HASH_H
#define EXT_HASH_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bucket.h"
#include "rid.h"


typedef struct Ext_Hash {
    __uint32_t global_depth;
    __uint32_t n_dirs;
    __uint32_t old_n_dirs;
    __uint32_t records_per_bucket;
    Bucket_t** directories;
} Ext_Hash_t;

#define EXT_HASH_SIZE sizeof(Ext_Hash_t)

Ext_Hash_t* new_ext_hash(__uint32_t global_depth, __uint32_t records_per_bucket);
void print_ext_hash(Ext_Hash_t* hash);
Rid_t* remove_record(Record_t* record, Ext_Hash_t* hash);
Rid_t* add_record(Record_t* record, Ext_Hash_t* hash);
Rid_t* search_record(Record_t* record, Ext_Hash_t* hash);

#endif
