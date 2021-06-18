#include <stdio.h>
#include <stdlib.h>
#include "src/record.h"
#include "src/bucket.h"
#include "src/ext_hash.h"


int main() {

    Record_t* r1 = new_record(__INT64_MAX__);
    Record_t* r2 = new_record(127);
    Record_t* r3 = new_record(1);

    Bucket_t* bucket = new_bucket(2, 5);

    add_record_to_bucket(r1, bucket);
    add_record_to_bucket(r2, bucket);
    add_record_to_bucket(r3, bucket);

    print_bucket(bucket);

    Ext_Hash_t* hash = new_ext_hash(2, 2);

    print_ext_hash(hash);

    return 0;
}