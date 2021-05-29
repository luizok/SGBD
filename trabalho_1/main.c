#include <stdlib.h>
#include <stdio.h>

#include "record.h"
#include "page.h"


int main() {

    Record_t* record = new_record(32);
    print_record(record);

    Page_t* page = new_page(5, "records.txt");

    page->bitmap = 0b1111111001;
    print_page(page);
    printf(" ");
    printf("page is full -> %d\n", is_page_full(page));

    page->bitmap = 0b11111;
    print_page(page);
    printf(" ");
    printf("page is full -> %d\n", is_page_full(page));
}
