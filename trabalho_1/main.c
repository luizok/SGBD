#include <stdlib.h>
#include <stdio.h>

#include "src/record.h"
#include "src/page.h"
#include "src/dbmanager.h"
#include "src/rid.h"


int main() {

    int n_pages = 3, n_records = 2;
    DB_Manager_t* manager = new_dbmanager(n_pages, n_records);
    Record_t* record = NULL;
    Rid_t* rid = NULL;

    print_dbmanager(manager);
    printf("\n");

    for(int i=0; i < n_pages*n_records; i++) {
        record = new_record(i+1);
        rid = insert_record(manager, record);
        print_rid(rid);
        printf("\n");
        print_dbmanager(manager);
        printf("\n");
    }

    record = new_record(n_pages*n_records+1);
    rid = insert_record(manager, record);
    print_rid(rid);
    printf("\n");
    print_dbmanager(manager);
    printf("\n");
}
