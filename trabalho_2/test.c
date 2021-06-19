#include <stdio.h>
#include <stdlib.h>
#include "src/record.h"
#include "src/bucket.h"
#include "src/ext_hash.h"
#include "src/rid.h"


int main() {

    Record_t* r1 = new_record(__INT64_MAX__);
    Record_t* r2 = new_record(127);
    Record_t* r3 = new_record(1);
    Record_t* r4 = new_record(127);
    Record_t* r5 = new_record(128);

    printf("cmp(r2, r4) = %d\n", cmp_records(r2, r4)); // 0
    printf("cmp(r2, r3) = %d\n", cmp_records(r2, r3)); // -1
    printf("cmp(r3, r2) = %d\n", cmp_records(r3, r2)); // 1
    printf("cmp(r2, NULL) = %d\n", cmp_records(r2, NULL)); // -2

    Bucket_t* bucket = new_bucket(2, 5);

    add_record_to_bucket(r1, bucket);
    add_record_to_bucket(r2, bucket);
    add_record_to_bucket(r3, bucket);

    print_bucket(bucket);

    __int32_t slot = search_record_in_bucket(r2, bucket);
    printf("FOUND AT %d\n", slot);

    slot = search_record_in_bucket(NULL, bucket);
    printf("FOUND AT %d\n", slot);

    slot = search_record_in_bucket(r5, bucket);
    printf("FOUND AT %d\n", slot);

    Ext_Hash_t* hash = new_ext_hash(2, 2);

    print_ext_hash(hash);

    return 0;
}