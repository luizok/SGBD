#include "page.h"


void open_page_file(Page_t* page);

Page_t* new_page(__uint32_t max_records, char* page_filename, __uint32_t page_index) {

    Page_t* page = (Page_t*) malloc(PAGE_SIZE);
    page->prev_page = NULL;
    page->next_page = NULL;
    page->max_records = max_records;
    page->bitmap = 0;
    strcpy(page->filename, page_filename);
    page->records_file = NULL;
    page->page_index = page_index;

    // open_page_file(page);

    return page;
}

void open_page_file(Page_t* page) {

    __uint32_t page_size_in_bytes = page->max_records * RECORD_SIZE;
    page->records_file = fopen(page->filename, "rb+");
    BYTE* buffer = (BYTE*) calloc(1, page_size_in_bytes);

    if(page->records_file == NULL) { // Se arquivo de página ainda não foi
        page->records_file = fopen(page->filename, "wb+");
        fwrite(buffer, page_size_in_bytes, 1, page->records_file);
    }

    rewind(page->records_file);
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
        printf("{%02d: ", page->page_index);
        for(__uint32_t i=0; i < page->max_records; i++)
            printf("%d", (page->bitmap >> i) & 0x1);
        printf(" }");
    }
}

Rid_t* insert_record_in_page(Page_t* page, Record_t* record) {

    __int32_t empty_slot = next_empty_slot(page);

    if(empty_slot < 0) {
        printf("ERRO: Nao ha slots disponiveis nessa pagina\n");
        return NULL;
    }

    Rid_t* rid = new_rid();
    rid->slot = empty_slot;

    open_page_file(page);
    fseek(page->records_file, empty_slot * RECORD_SIZE, SEEK_SET);
    fwrite(record, RECORD_SIZE, 1, page->records_file);
    fclose(page->records_file);

    page->bitmap |= (0x1 << empty_slot);

    return rid;
}

Record_t** get_records_in_page(Page_t* page){
    __uint32_t records_in_page = total_filled_slot(page);
    BYTE* page_buffer = (BYTE*) malloc(records_in_page * RECORD_SIZE);//copiando bytes dos arquivos
    Record_t** record_vector = (Record_t**) malloc(sizeof(Record_t*) * (records_in_page + 1)); // + 1 significa slot extra no final apontando para NULL

    open_page_file(page);
    fread(page_buffer, RECORD_SIZE, records_in_page, page->records_file);

    for(__uint32_t i=0; i < records_in_page; i++){
        record_vector[i] = (Record_t*) &page_buffer[i*RECORD_SIZE]; 
    }

    record_vector[records_in_page] = NULL;

    fclose(page->records_file);
    return record_vector;
}

Rid_t* search_record_in_page(Page_t* page, Record_t* record) {

    BYTE* page_buffer = (BYTE*) malloc(page->max_records * RECORD_SIZE);
    Rid_t* rid = NULL;

    open_page_file(page);
    fread(page_buffer, RECORD_SIZE, page->max_records, page->records_file);

    // printf("AA\n");
    for(__uint32_t i=0; i < page->max_records; i++)
        if((memcmp(record, &page_buffer[i * RECORD_SIZE], RECORD_SIZE) == 0) && (((page->bitmap >> i) & 0x1) == FILLED_SLOT)) {
            rid = new_rid();
            rid->slot = i;
        }

    fclose(page->records_file);

    return rid;
}

void remove_record_in_page(Page_t* page, __uint32_t slot) {
    // remover registro no arquivo da pagina
    page->bitmap &= ~(0x1 << slot);

}

BOOL is_page_full(Page_t* page) {

    for(__uint32_t i=0; i < page->max_records; i++)
        if(((page->bitmap >> i) & 0x1) == EMPTY_SLOT)
            return FALSE;

    return TRUE;
}

BOOL is_page_empty(Page_t* page) {

    return page->bitmap == 0;
}
