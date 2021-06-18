#ifndef EXT_HASH_H
#define EXT_HASH_H


#include <stdlib.h>
#include <stdio.h>
#include "bucket.h"


typedef struct Ext_Hash {
    __uint32_t global_depth;
    __uint32_t n_dirs;
    Bucket_t** directories;
} Ext_Hash_t;

#define EXT_HASH_SIZE sizeof(Ext_Hash_t)

Ext_Hash_t* new_ext_hash(__uint32_t global_depth, __uint32_t records_per_bucket);
void print_ext_hash(Ext_Hash_t* hash);

#endif