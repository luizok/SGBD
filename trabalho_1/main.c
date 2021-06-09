#include <stdlib.h>
#include <stdio.h>

#include "src/record.h"
#include "src/page.h"
#include "src/dbmanager.h"
#include "src/rid.h"


void test_insert(DB_Manager_t* manager) {

    printf("Insercaozinha top: \n");
    __uint32_t n_pages = manager->n_pages;
    __uint32_t n_records = manager->all_pages[0]->max_records;
    Record_t* record = NULL;
    Rid_t* rid = NULL;

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
}

void test_search(DB_Manager_t* manager) {

    printf("Buscazinha top: \n");
    __uint32_t n_pages = manager->n_pages;
    __uint32_t n_records = manager->all_pages[0]->max_records;
    Rid_t* rid = NULL;

    for(int i=0; i < 2*n_pages*n_records+1; i++) {
        rid = search_record(manager, new_record(i));
        if(rid) {
            printf("%d FOUND IN ", i);
            print_rid(rid);
        } else
            printf("%d NOT FOUND", i);

        printf("\n");
    }

    printf("\n");
}

void test_scan(DB_Manager_t* manager) {

    printf("Scanzin top: \n");
    Record_t*** records = get_records_in_pages(manager);
    Record_t*** curr_page = records;

    for(curr_page; *curr_page != NULL; curr_page++)
        for(Record_t** curr_record = *curr_page; *curr_record != NULL; curr_record++)
            print_record(*curr_record);
}

void test_delete(DB_Manager_t* manager) {

    printf("\nDelecaozinha top: \n");
}

int main(int argc, char** argv) {

    if(argc < 3) {
        printf("Usage: %s <n_pages> <n_records>\n", argv[0]);
        return -1;
    }

    int n_pages = atoi(argv[1]);
    int n_records = atoi(argv[2]);
    DB_Manager_t* manager = new_dbmanager(n_pages, n_records);

    printf("Estadozin inicial: \n");
    print_dbmanager(manager);
    printf("\n");

    test_insert(manager);
    test_search(manager);
    test_scan(manager);
    test_delete(manager);

    return 0;
}
