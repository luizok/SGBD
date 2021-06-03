#include <stdlib.h>
#include <stdio.h>

#include "src/record.h"
#include "src/page.h"
#include "src/dbmanager.h"


int main() {

    int n_pages = 3, n_records = 2;
    DB_Manager_t* manager = new_dbmanager(n_pages, n_records);
    Record_t* record = NULL;

    print_dbmanager(manager);

    printf("\nrecord size = %lu\n", RECORD_SIZE);

    for(int i=0; i < n_pages*n_records; i++) {
        printf("INSERCAO REGISTRO %d\n", i+1);
        record = new_record(i+1);
        insert_record(manager, record);
        print_dbmanager(manager);
        printf("\n");
    }

    printf("INSERCAO REGISTRO %d\n", n_pages*n_records+1);
    record = new_record(n_pages*n_records+1);
    insert_record(manager, record);
    print_dbmanager(manager);
    printf("\n");
}
