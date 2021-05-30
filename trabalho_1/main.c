#include <stdlib.h>
#include <stdio.h>

#include "src/record.h"
#include "src/page.h"
#include "src/dbmanager.h"


int main() {

    Record_t* record = new_record(32);
    print_record(record);

    Page_t* page = new_page(5, "records.txt", 0);

    page->bitmap = 0b1111111001;
    print_page(page);
    printf(" ");
    printf("page is full -> %d\n", is_page_full(page));

    page->bitmap = 0b11111;
    print_page(page);
    printf(" ");
    printf("page is full -> %d\n\n", is_page_full(page));

    int n_pages = 3, n_records = 2;
    DB_Manager_t* manager = new_dbmanager(n_pages, n_records);
    print_dbmanager(manager);
    printf("\n");

    for(int i=0; i < n_pages*n_records; i++) {
        printf("INSERCAO REGISTRO %d\n", i+1);
        insert_record(manager, NULL);
        print_dbmanager(manager);
        printf("\n");
    }

    printf("INSERCAO REGISTRO %d\n", n_pages*n_records+1);
    insert_record(manager, NULL);
    print_dbmanager(manager);
    printf("\n");
}
