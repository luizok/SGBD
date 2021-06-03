#include "dbmanager.h"


DB_Manager_t* new_dbmanager(__uint32_t n_pages, __uint32_t records_per_page) {

    DB_Manager_t* manager = (DB_Manager_t*) malloc(MANAGER_SIZE);
    manager->all_pages = (Page_t**) malloc(n_pages * sizeof(Page_t*));
    manager->bitmaps = (__uint32_t**) malloc(n_pages * sizeof(__uint32_t*));
    char filename[256];

    for(__uint32_t i=0; i < n_pages; i++) {
        sprintf(filename, "page_id_%02d.dbpage", i);
        manager->all_pages[i] = new_page(records_per_page, filename, i); // passar i como parametro
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

    printf("Paginas vazias: ");
    while(root) {
        print_page(root);
        printf(" -> ");
        root = root->next_page;
    }

    printf("\n");

    root = manager->used_pages;

    printf("Paginas usadas: ");
    while(root) {
        print_page(root);
        printf(" -> ");
        root = root->next_page;
    }

    printf("\n");
}

void insert_record(DB_Manager_t* manager, Record_t* record) {

    Page_t* last_non_null_page = NULL;
    Page_t* curr_page = manager->used_pages;

    while(curr_page) {
        if(!is_page_full(curr_page)) {
            insert_record_in_page(curr_page, record);
            return;
        }

        last_non_null_page = curr_page;
        curr_page = curr_page->next_page;
    }

    Page_t* empty_page = manager->empty_pages;

    if(empty_page == NULL) { // Não há mais páginas vazias para utilizar
        printf("ERRO: Nao ha mais espaco disponivel\n");
        return;
    }

    if((curr_page == NULL) && (last_non_null_page == NULL)) { // Lista de usadas está vazia
        manager->empty_pages = empty_page->next_page;
        manager->empty_pages->prev_page = NULL;
        empty_page->next_page = NULL;
        manager->used_pages = empty_page;

    } else if((curr_page == NULL) && (last_non_null_page != NULL)) { // Todas as páginas usadas estão cheias
        manager->empty_pages = empty_page->next_page;
        if(empty_page->next_page)
            empty_page->next_page->prev_page = NULL;
        empty_page->next_page = last_non_null_page->next_page;
        last_non_null_page->next_page = empty_page;
    }

    insert_record_in_page(empty_page, record);
}

Record_t* search_record(DB_Manager_t* manager, Record_t* record) {

}

Record_t* remove_record(DB_Manager_t* manager, Record_t* record) {

}

void commit() {

}
