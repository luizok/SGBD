#include <stdlib.h>
#include <stdio.h>

#include "record.h"
#include "page.h"
#include "dbmanager.h"


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
    printf("page is full -> %d\n", is_page_full(page));

    DB_Manager_t* manager = new_dbmanager(5, 10);
    print_dbmanager(manager);
}
