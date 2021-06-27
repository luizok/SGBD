#include "bucket.h"


__uint32_t bucket_id = 0;

Bucket_t* new_bucket(__uint32_t local_depth, __uint32_t n_records) {

    Bucket_t* bucket = (Bucket_t*) malloc(BUCKET_SIZE);
    bucket->local_depth = local_depth;
    bucket->n_records = n_records;
    bucket->records = (Record_t**) calloc(n_records, sizeof(Record_t*));
    bucket->index = 0; // TEST PURPOSES
    bucket->bucket_id = bucket_id++;
    // bucket->next = NULL;

    return bucket;
}

void print_bucket(Bucket_t* bucket) {

    if(!bucket) {
        printf("{NULL_BUCKET}\n");
        return;
    }

    printf("{<IDX:%02d, LD:%02d>: ", bucket->bucket_id, bucket->local_depth);
    for(int i=0; i < bucket->n_records; i++) {
        if(bucket->records[i]) {
            print_record(bucket->records[i]);
            printf(", ");
        }
        else
            printf("________, ");
    }
    printf("\x08\x08}\n");
    // print_bucket(bucket->next);
}

__int32_t remove_record_from_bucket(Record_t* record, Bucket_t* bucket) {

   __int32_t rec = search_record_in_bucket(record, bucket);
   if(rec == -1){  
        printf("Isso non ecziste - nenhum elemento removido\n");
        return -1;
   }else{
        free(bucket->records[rec]);
        bucket->records[rec] = NULL;
        //atribuir pra null       
    }
    return rec;
}

__int32_t add_record_to_bucket(Record_t* record, Bucket_t* bucket) {

    if(bucket->index == bucket->n_records)
        return -1;

    bucket->records[bucket->index] = record;

    return bucket->index++;
}

__int32_t search_record_in_bucket(Record_t* record, Bucket_t* bucket) {

    for(int i=0; i <  bucket->n_records; i++)
        if(cmp_records(record, bucket->records[i]) == 0)
            return i;

    return -1;
}
