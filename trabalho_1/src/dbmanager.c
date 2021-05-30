#include "dbmanager.h"


DB_Manager_t* new_dbmanager(__uint32_t n_pages, __uint32_t records_per_page) {

    DB_Manager_t* manager = (DB_Manager_t*) malloc(MANAGER_SIZE);
    manager->all_pages = (Page_t**) malloc(n_pages * sizeof(Page_t*));
    manager->bitmaps = (__uint32_t**) malloc(n_pages * sizeof(__uint32_t*));

    for(__uint32_t i=0; i < n_pages; i++) {
        manager->all_pages[i] = new_page(records_per_page, "FILENAME", i); // passar i como parametro
        manager->bitmaps[i] = &manager->all_pages[i]->bitmap;
    }

    for(__uint32_t i=0; i < n_pages; i++) {
        manager->all_pages[i]->prev_page = i > 0 ? manager->all_pages[i-1] : NULL;
        manager->all_pages[i]->next_page = i < n_pages-1 ? manager->all_pages[i+1] : NULL;
    }

    manager->empty_pages = manager->all_pages[0];
    manager->used_pages = NULL;
    manager->n_pages = n_pages;
    manager->records_per_page = records_per_page;

    return manager;
}

void print_dbmanager(DB_Manager_t* manager) {

    Page_t* root = manager->empty_pages;

    printf("Paginas vazias: \n");
    while(root) {
        print_page(root);
        printf(" -> ");
        root = root->next_page;
    }

    printf("\n");

    root = manager->used_pages;

    printf("Paginas usadas: \n");
    while(root) {
        print_page(root);
        printf(" -> ");
        root = root->next_page;
    }

    printf("\n");
}

void insert_record(DB_Manager_t* manager, Record_t* record) {

}

Record_t* search_record(DB_Manager_t* manager, Record_t* record) {

}

Record_t* remove_record(DB_Manager_t* manager, Record_t* record) {

}

void commit() {

}
