#include "page.h"


Page_t* new_page(__uint32_t max_records, char* page_filename, __uint32_t page_index) {

    Page_t* page = (Page_t*) malloc(PAGE_SIZE);
    page->prev_page = NULL;
    page->next_page = NULL;
    page->max_records = max_records;
    page->bitmap = ~0;
    page->records_file = NULL;
    page->page_index = page_index;

    // page->records_file = fopen(page_filename, 'ab+');

    return page;
}

__uint32_t total_filled_slot(Page_t* page) {

    __uint32_t total = 0;
    for(__uint32_t i=0; i < page->max_records; i++)
        if(((page->bitmap >> i) & 0x1) == FILLED_SLOT)
            total++;

    return total;
}

__int32_t last_filled_slot(Page_t* page) {

    __int32_t index = -1;
    for(__uint32_t i=0; i < page->max_records; i++)
        if(((page->bitmap >> i) & 0x1) == FILLED_SLOT)
            index = i;

    return index; 
}

__int32_t next_empty_slot(Page_t* page) {

    for(__int32_t i=0; i < page->max_records; i++)
        if(((page->bitmap >> i) & 0x1) == EMPTY_SLOT)
            return i;

    return -1;
}

void reorder_page(Page_t* page) {
    // mover último registro da página para slot desocupapdo
}


void print_page(Page_t* page) {
    // loop em todos os registros da pagina
    if(page == NULL)
        printf("X");
    else {
        printf("| ");
        for(__uint32_t i=0; i < page->max_records; i++)
            printf("%d", (page->bitmap >> i) & 0x1);
        printf(" |");
    }
}

void insert_record_in_page(Page_t* page, Record_t* record) {
    // inserir registro no arquivo da pagina
}

void search_record_in_page(Page_t* page, Record_t* record) {
    // buscar registro no arquivo da pagina
}

void remove_record_in_page(Page_t* page, Record_t* record) {
    // remover registro no arquivo da pagina
}

BOOL is_page_full(Page_t* page) {

    for(__uint32_t i=0; i < page->max_records; i++)
        if(((page->bitmap >> i) & 0x1) == EMPTY_SLOT)
            return FALSE;

    return TRUE;
}
