#include <stdlib.h>
#include <stdio.h>

#include "src/record.h"
#include "src/page.h"
#include "src/dbmanager.h"
#include "src/rid.h"

int main(int argc, char** argv) {

    if(argc < 3) {
        printf("Usage: %s <n_pages> <n_records>\n", argv[0]);
        return -1;
    }

    int n_pages = atoi(argv[1]);
    int n_records = atoi(argv[2]);
    DB_Manager_t* manager = new_dbmanager(n_pages, n_records);

    printf("Estadozin inicial: \n");
    print_dbmanager(manager);
    printf("\n");
    int escolha=1;
    while (escolha != 6)
    {

        printf("\n\n ----------------------- ");

        printf("\n    MENU - DB MANAGER ");
        printf("\n ----------------------- ");
        printf("\n Digite 1 para Insercao ");
        printf("\n Digite 2 para Exclusao ");
        printf("\n Digite 3 para Busca ");
        printf("\n Digite 4 para Scan ");
        printf("\n Digite 5 para ver status do DB Manager ");
        printf("\n Digite 6 para Fechar Programa ");
        printf("\n\n Escolha uma opcao: ");
        scanf("%d", &escolha);
        switch (escolha) {

            case 1:
            {
                
                BYTE data = 0;
                printf("\n\n Opcao escolhida: 1 \n");
                printf("Insercaozinha top: \n");
                printf("Digite o byte que deseja inserir: \n");
                scanf("%hhd", &data);
                Record_t* record = new_record(data);
                Rid_t* rid = insert_record(manager, record);
                if(!rid)
                    printf(" NOT INSERTED\n");

                else{
                    printf(" INSERTED ");
                    print_rid(rid);
                    printf("\n");      
                }
                print_dbmanager(manager);
                break;
            }

            case 2:
            {

                printf("\n\n Opcao escolhida: 2 ");
                BYTE data = 0;
                printf("\n\n Opcao escolhida: 1 \n");
                printf("Deleçãozinha top: \n");
                printf("Digite o byte que deseja remover: \n");
                scanf("%hhd", &data);
                Record_t* record = new_record(data);
                record = remove_record(manager, record);
                print_record(record);
                if(!record)
                    printf(" NOT DELETED\n");

                else{
                    printf(" DELETED ");
                    print_record(record);
                    printf("\n");      
                }
                printf("\n\n");
                print_dbmanager(manager);
                break;
            }

            case 3:
            {
                
                printf("\n\n Opcao escolhida: 3 \n");
                BYTE data = 0;
                printf("Buscazinha top: \n");
                printf("Digite o byte que deseja buscar: \n");
                scanf("%hhd", &data);
                Record_t* record = new_record(data);
                Rid_t* rid = search_record(manager, record);
                if(!rid)
                    printf(" NOT FOUND\n");

                else{
                    printf(" FOUND ");
                    print_rid(rid);
                    printf("\n");      
                }
                print_dbmanager(manager);
                printf("\n");    
                break;
            }
            
            case 4:
            {
                
                printf("\n\n Opcao escolhida: 4 \n");
                printf("Scanzin top: \n");
                Record_t*** records = get_all_records(manager);
                Record_t*** curr_page = records;

                for(curr_page; *curr_page != NULL; curr_page++)
                    for(Record_t** curr_record = *curr_page; *curr_record != NULL; curr_record++)
                        print_record(*curr_record);
                            printf("\n");    
                break;
            }

            case 5:
            {
                
                printf("\n\n Opcao escolhida: 5 \n");
                print_dbmanager(manager);
                printf("\n");    
                break;
            }

            // opção padrão
            default:
            {

                // continue pula o while  
                if(escolha == 6)
                {   
                    continue;
                }
                printf("\n\n Opcao invalida! ");
                break;
            }

        }

    }
    if(escolha == 6)
        printf("\n\n Programa finalizado ;D\n");


    printf("\n");

    return 0;
}
