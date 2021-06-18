#include <stdio.h>
#include <stdlib.h>
#include "src/record.h"
#include "src/ext_hash.h"
#include "src/utils.h"


int main(int argc, char** argv) {

    if(argc < 4) {
        printf("Usage: <txt_file> <global_depth> <n_records>\n");
        return -1;
    }

    char python_cmd[256];
    sprintf(python_cmd, "python src/converter.py %s", argv[1]);
    system(python_cmd);
    
    FILE* bin_file = fopen("ops.bin", "rb");
    BYTE op;
    __uint64_t number;

    Ext_Hash_t* hash = new_ext_hash(atoi(argv[2]), atoi(argv[3]));
    Record_t* record = new_record(0);

    while((char) (op = fgetc(bin_file)) != EOF) {
        fread(&record->data, sizeof(__int64_t), 1, bin_file);
        printf("0x%02X -> ", op);
        switch(op) {
            case '\x00': {
                remove_record(hash, record);
                break;
            }
            case '\x01': {
                add_record(hash, record);
                break;
            }
            case '\x02': {
                search_record(hash, record);
                break;
            }
        }
    }

    return 0;
}