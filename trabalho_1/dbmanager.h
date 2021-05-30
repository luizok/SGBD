#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <stdio.h>
#include <stdlib.h>

#include "page.h"
#include "utils.h"


typedef struct DB_Manager {
    __uint32_t n_pages;
    __uint32_t records_per_page;
    __uint32_t** bitmaps;
    Page_t** all_pages;
    Page_t* empty_pages;
    Page_t* used_pages;
} DB_Manager_t;

#define MANAGER_SIZE sizeof(DB_Manager_t)

DB_Manager_t* new_dbmanager(__uint32_t n_pages, __uint32_t records_per_page);
void print_dbmanager(DB_Manager_t* manager);
void insert_record(Record_t* record);
Record_t* search_record(Record_t* record);
Record_t* remove_record(Record_t* record);
void commit();

#endif