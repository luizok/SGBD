#ifndef PAGE_H
#define PAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record.h"
#include "rid.h"
#include "utils.h"


typedef struct Page {
    struct Page* prev_page;
    struct Page* next_page;
    __uint32_t max_records;
    char filename[256];
    FILE* records_file;
    __uint32_t bitmap;
    __uint32_t page_index;
} Page_t;

#define PAGE_SIZE sizeof(Page_t)

Page_t* new_page(__uint32_t n_records, char* page_filename, __uint32_t page_index);
void print_page(Page_t* page);
Rid_t* insert_record_in_page(Page_t* page, Record_t* record);
Rid_t* search_record_in_page(Page_t* page, Record_t* record);
void remove_record_in_page(Page_t* page, __uint32_t slot);
BOOL is_page_full(Page_t* page);
BOOL is_page_empty(Page_t* page);
Record_t** get_records_in_page(Page_t* page);


#endif
