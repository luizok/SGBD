#ifndef PAGE_H
#define PAGE_H

#include <stdio.h>
#include <stdlib.h>

#include "record.h"

#include "utils.h"


typedef struct Page {
    struct Page* prev_page;
    struct Page* next_page;
    __uint32_t max_records;
    FILE* records_file;
    __uint32_t bitmap;
} Page_t;

#define PAGE_SIZE sizeof(Page_t)

Page_t* new_page(__uint32_t n_records, char* page_filename);
void print_page(Page_t* page);
void insert_record_in_page(Page_t* page, Record_t* record);
void search_record_in_page(Page_t* page, Record_t* record);
void remove_record_in_page(Page_t* page, Record_t* record);
BOOL is_page_full(Page_t* page);


#endif