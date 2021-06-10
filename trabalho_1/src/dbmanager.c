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

Rid_t* insert_record(DB_Manager_t* manager, Record_t* record) {

    Page_t* last_non_null_page = NULL;
    Page_t* curr_page = manager->used_pages;
    __int32_t curr_page_index = -1;
    Rid_t* rid = NULL;
    BOOL has_inserted = FALSE;

    while(curr_page) {
        curr_page_index++;
        if(!is_page_full(curr_page)) {
            rid = insert_record_in_page(curr_page, record);
            has_inserted = TRUE;
            break;
        }

        last_non_null_page = curr_page;
        curr_page = curr_page->next_page;
    }

    if(!has_inserted) {
        Page_t* empty_page = manager->empty_pages;

        if(empty_page == NULL) { // Não há mais páginas vazias para utilizar
            printf("ERRO: Nao ha mais espaco disponivel\n");
            return NULL;
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
            empty_page->prev_page = last_non_null_page;
            empty_page->next_page = last_non_null_page->next_page;
            last_non_null_page->next_page = empty_page;
        }

        curr_page_index++;
        rid = insert_record_in_page(empty_page, record);
    }

    rid->page = curr_page_index;

    return rid;
}

Record_t*** get_all_records(DB_Manager_t* manager){
    Page_t* root = manager->used_pages;
    __uint32_t used_pages_number = 0;

    while(root) {
        used_pages_number++;
        root = root->next_page;
    }
    Record_t*** vector = (Record_t***) malloc((used_pages_number + 1) * sizeof(Record_t**));//qual seria o tamanho aqui ?
    root = manager->used_pages;
    for (__uint32_t i=0; i < used_pages_number; i++)
    {
        vector[i] = get_records_in_page(root);
        root = root->next_page;
    }

    vector[used_pages_number] = NULL;

    return vector;
}

Rid_t* search_record(DB_Manager_t* manager, Record_t* record) {

    Page_t* root = manager->used_pages;
    __int32_t  curr_page_index = -1;
    Rid_t* rid = NULL;

    while(root) {
        curr_page_index++;
        rid = search_record_in_page(root, record);
        if(rid != NULL) {
            rid->page = curr_page_index;
            break;
        }
        root = root->next_page;
    }

    return rid;
}

void move_page_to_empty_pages(DB_Manager_t* manager, Page_t* page) {

    if(page->prev_page) // se não for o primeiro elemento da used_pages
        page->prev_page->next_page = page->next_page;
    else
        manager->used_pages = page->next_page;

    if(page->next_page)
        page->next_page->prev_page = page->prev_page;

    page->prev_page = NULL;
    page->next_page = manager->empty_pages;

    if(manager->empty_pages)
        manager->empty_pages->prev_page = page;

    manager->empty_pages = page;
}

Page_t* get_last_used_page(DB_Manager_t* manager) {

    Page_t* curr_page = manager->used_pages;
    Page_t* last_page = NULL;

    while(curr_page) {
        last_page = curr_page;
        curr_page = curr_page->next_page;
    }

    return last_page;
}

Rid_t* get_last_record_rid(DB_Manager_t* manager) {

    Page_t* root = get_last_used_page(manager);
    Rid_t* rid = new_rid();
    rid->slot = last_filled_slot(root);

    return rid;
}

Record_t* get_last_record(DB_Manager_t* manager) {

    Record_t** records = NULL;
    Page_t* root = get_last_used_page(manager);

    records = get_records_in_page(root);
    Record_t** last_record;
    for(last_record = records; *(last_record+1) != NULL; last_record++)
        continue;

    return *last_record;
}

Record_t* remove_record(DB_Manager_t* manager, Record_t* record) {

    Page_t* root = manager->used_pages;
    Rid_t* rid = NULL;

    Page_t* last_used_page = NULL;
    Rid_t* last_rid = NULL;
    Record_t* last_record = NULL;

    __uint32_t page_index = -1;
    while(root) {
        rid = search_record_in_page(root, record);
        page_index++;
        if(rid) {
            rid->page = page_index;
            remove_record_in_page(root, rid->slot);

            printf("\nITERATION\n");
            print_dbmanager(manager);

            last_rid = get_last_record_rid(manager);
            last_used_page = get_last_used_page(manager);
            last_record = get_last_record(manager);

            printf("last page: ");
            print_page(last_used_page);
            printf("\nlast slot: %d\n", last_rid->slot);

            if(last_rid->slot >= 0) {
                remove_record_in_page(last_used_page, last_rid->slot);
                rid = insert_record(manager, last_record);
                printf("INSERT AT ");
                print_rid(rid);
                printf("\n");
            }

            if(is_page_empty(last_used_page))
                move_page_to_empty_pages(manager, last_used_page);

            if(is_page_empty(root))
                move_page_to_empty_pages(manager, root);

            return record;
        }

        root = root->next_page;
    }

    return NULL;
}

void commit() {

}
