#include "bucket.h"


Bucket_t* new_bucket(__uint32_t local_depth, __uint32_t n_records) {

    Bucket_t* bucket = (Bucket_t*) malloc(BUCKET_SIZE);
    bucket->local_depth = local_depth;
    bucket->n_records = n_records;
    bucket->records = (Record_t**) calloc(n_records, sizeof(Record_t*));
    bucket->index = 0; // TEST PURPOSES
    // bucket->next = NULL;

    return bucket;
}

void print_bucket(Bucket_t* bucket) {

    if(!bucket) {
        printf("{NULL_BUCKET}\n");
        return;
    }

    printf("{%02d: ", bucket->local_depth);
    for(int i=0; i < bucket->n_records; i++) {
        if(bucket->records[i]) {
            print_record(bucket->records[i]);
            printf(", ");
        }
        else
            printf("________, ");
    }
    printf("\x08\x08}");
    // print_bucket(bucket->next);
}

void add_record_to_bucket(Record_t* record, Bucket_t* bucket) {

    bucket->records[bucket->index] = record;
    bucket->index++;
}
