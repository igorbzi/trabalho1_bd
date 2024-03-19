#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20

typedef struct {
    int id;
    char logical_name[MAX_NAME_LENGTH];
    char physical_name[MAX_NAME_LENGTH];
} TableEntry;

int main() {

    char table_name[MAX_NAME_LENGTH];

    printf("Digite o nome da tabela: ");
    scanf("%s", table_name);

    FILE *table_file = fopen("table.dic", "rb");
    if (table_file == NULL) {
        printf("Erro ao abrir o arquivo table.dic.\n");
        return 1;
    }

    TableEntry entry;
    int found = 0;

    while (fread(&entry, sizeof(TableEntry), 1, table_file)) {
        if (strcmp(entry.logical_name, table_name) == 0) {
            found = 1;
            printf("ID do arquivo para a tabela %s: %d\n", table_name, entry.id);
            break;
        }
    }

    if (!found) {
        printf("Tabela %s não encontrada no arquivo table.dic.\n", table_name);
    }

    fclose(table_file);

}
