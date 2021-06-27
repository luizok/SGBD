#include "ext_hash.h"


FILE* output_file;

__uint32_t hash_func(Record_t* record, __uint32_t depth);
void split_kth_bucket(Ext_Hash_t* hash, __int32_t k, BOOL needsDouble);
void split_records_between_buckets(Ext_Hash_t* hash, __int32_t k);


Ext_Hash_t* new_ext_hash(__uint32_t global_depth, __uint32_t records_per_bucket) {

    Ext_Hash_t* hash = (Ext_Hash_t*) malloc(EXT_HASH_SIZE);
    hash->records_per_bucket = records_per_bucket;
    hash->global_depth = global_depth;
    hash->n_dirs = 1 << global_depth;
    hash->old_n_dirs = hash->n_dirs >> 1;
    hash->directories = (Bucket_t**) calloc(hash->n_dirs, sizeof(Bucket_t*));
    for(int i=0; i < hash->n_dirs; i++)
        hash->directories[i] = new_bucket(global_depth, records_per_bucket);

    return hash;
}

__uint32_t hash_func(Record_t* record, __uint32_t depth) {

    return record->data & (0xFFFFFFFF >> (32 - depth));
}

void split_kth_bucket(Ext_Hash_t* hash, __int32_t k, BOOL needs_double) {

    if(needs_double) {

        hash->old_n_dirs = hash->n_dirs;
        hash->n_dirs <<= 1;
        hash->global_depth++;
        // fprintf(output_file, "DOUBLE DIRS%d\n", 1);

        hash->directories = (Bucket_t**) realloc(hash->directories, hash->n_dirs * sizeof(Bucket_t*));
        hash->directories[k]->local_depth++;

        for(int i=0; i < hash->old_n_dirs; i++) {
            if(i == k)
                hash->directories[hash->old_n_dirs + i] = new_bucket(hash->global_depth, hash->directories[i]->n_records);
            else
                hash->directories[hash->old_n_dirs + i] = hash->directories[i];
        }
    }
    else {
        // hash->directories[k] = new_bucket(hash->global_depth, hash->directories[k]->n_records);
        hash->directories[k]->local_depth++;
    }
}

void split_records_between_buckets(Ext_Hash_t* hash, __int32_t k) {

    __int32_t bucket_a_idx = (0 << k) | k;
    __int32_t bucket_b_idx = (1 << k) | k;

    printf("A = \nB = \n");

    Bucket_t* kth_bucket = new_bucket(hash->directories[k]->local_depth, hash->directories[k]->n_records);
    __uint32_t bucket_idx;

    memcpy(kth_bucket, hash->directories[k], BUCKET_SIZE);
    // free(hash->directories[k]);
    printf("DFHSDJIFGHJFHSJDKF\n");
    print_bucket(kth_bucket);
    print_bucket(hash->directories[k]);

    hash->directories[k] = new_bucket(kth_bucket->local_depth, kth_bucket->n_records);
    for(int i=0; i < kth_bucket->n_records; i++) {
        if(kth_bucket->records[i]) {
            bucket_idx = hash_func(kth_bucket->records[i], hash->global_depth);
            add_record_to_bucket(kth_bucket->records[i], hash->directories[bucket_idx]);
        }
    }
}

void print_ext_hash(Ext_Hash_t* hash) {

    if(!hash) {
        printf("NULL_EXT_HASH\n");
        return;
    }

    printf("GD: %02d\n", hash->global_depth);
    for(int i=0; i < hash->n_dirs; i++) {
        printf("%04X -> ", i & (0xFFFFFFFF >> (32 - hash->global_depth)));
        print_bucket(hash->directories[i]);
    }
}

Rid_t* remove_record(Ext_Hash_t* hash, Record_t* record) {
    
    printf("Remoçãozinha top \n");
    Rid_t* rid = search_record(hash, record);

    if(rid->slot == -1)
        remove_record_from_bucket(record, hash->directories[rid->page]);
    else{//slot nao encontrado
        printf("Slot nao encontrado \n");
        return -1;
    }
    return rid;
}

Rid_t* add_record(Ext_Hash_t* hash, Record_t* record) {

    printf("ADDED RECORD ");
    print_record(record);
    printf("\n");

    Rid_t* rid = new_rid(-1, -1);
    __int32_t bucket_idx = hash_func(record, hash->global_depth);
    __int32_t slot = add_record_to_bucket(record, hash->directories[bucket_idx]);

    if(slot > -1) {
        rid->page = bucket_idx;
        rid->slot = slot;
    } else { // slot ta cheio
        printf("SPLIT BUCKET\n");
        split_kth_bucket(hash, bucket_idx, hash->directories[bucket_idx]->local_depth == hash->global_depth);
        printf("SPLITADO\n");
        split_records_between_buckets(hash, bucket_idx);
        printf("RECORDS SPLITADOS\n");

        bucket_idx = hash_func(record, hash->global_depth);
        rid->page = bucket_idx;
        rid->slot = add_record_to_bucket(record, hash->directories[bucket_idx]);
    }

    return rid;
}

Rid_t* search_record(Ext_Hash_t* hash, Record_t* record) {

    Rid_t* rid = new_rid(-1, -1);
    rid->page = hash_func(record, hash->global_depth);
    rid->slot = search_record_in_bucket(record, hash->directories[rid->page]);

    return rid;
}
