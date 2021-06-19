#include "ext_hash.h"


Ext_Hash_t* new_ext_hash(__uint32_t global_depth, __uint32_t records_per_bucket) {

    Ext_Hash_t* hash = (Ext_Hash_t*) malloc(EXT_HASH_SIZE);
    hash->global_depth = global_depth;
    hash->n_dirs = 1 << global_depth;
    hash->directories = (Bucket_t**) calloc(hash->n_dirs, sizeof(Bucket_t*));
    for(int i=0; i < hash->n_dirs; i++)
        hash->directories[i] = new_bucket(global_depth, records_per_bucket);

    return hash;
}

void print_ext_hash(Ext_Hash_t* hash) {

    if(!hash) {
        printf("NULL_EXT_HASH\n");
        return;
    }

    printf("GD: %02d\n", hash->global_depth);
    for(int i=0; i < hash->n_dirs; i++) {
        printf("%04X -> ", 1 << i);
        print_bucket(hash->directories[i]);
    }
}

Rid_t* remove_record(Record_t* record, Ext_Hash_t* hash) {
    
    printf("REMOVED ");
    print_record(record);
    printf("\n");
    return NULL;
}

Rid_t* add_record(Record_t* record, Ext_Hash_t* hash) {
    
    printf("ADDED ");
    print_record(record);
    printf("\n");
    return NULL;
}

Rid_t* search_record(Record_t* record, Ext_Hash_t* hash) {
    
    printf("SEARCH ");
    print_record(record);
    printf("\n");
    return NULL;
}
