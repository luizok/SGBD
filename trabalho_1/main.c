#include <stdlib.h>
#include <stdio.h>

#include "record.h"

int main() {

    Record_t* record = new_record(32);
    print_record(record);
}