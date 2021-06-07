#include <stdlib.h>
#include <stdio.h>

#include "src/record.h"
#include "src/page.h"
#include "src/dbmanager.h"
#include "src/rid.h"


int main(int argc, char** argv) {

    if(argc < 3) {
        printf("Usage: %s <n_pages> <n_records>\n", argv[0]);
        return -1;
    }

    int n_pages = atoi(argv[1]);
    int n_records = atoi(argv[2]);
    DB_Manager_t* manager = new_dbmanager(n_pages, n_records);
    Record_t* record = NULL;
    Rid_t* rid = NULL;

    print_dbmanager(manager);
    printf("\n");

    for(int i=0; i < n_pages*n_records; i++) {
        record = new_record(2*i);
        rid = insert_record(manager, record);
        printf("%d INSERTED IN ", 2*i );
        print_rid(rid);
        printf("\n");
        print_dbmanager(manager);
        printf("\n");
    }

    record = new_record(2*n_pages*n_records);
    rid = insert_record(manager, record);
    if(!rid)
    printf("%d NOT INSERTED\n", 2*n_pages*n_records);

    print_dbmanager(manager);
    printf("\n\n");

    for(int i=0; i < 2*n_pages*n_records+1; i++) {
        rid = search_record(manager, new_record(i));
        if(rid) {
            printf("%d FOUND IN ", i);
            print_rid(rid);
        } else
            printf("%d NOT FOUND", i);

        printf("\n");
    }
    printf("Scanzin top: \n");
    Record_t*** records = get_records_in_pages(manager);


}
