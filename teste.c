#include <stdio.h>
#include <string.h>

typedef struct {
    int id[1];
    char nome[20];
    char tipo[1];
    char op[1];
    int tam[1];
} Atributo;

int encontra_tabela(FILE *ft, int *v, char*consulta, char *logico, char *fisico){
    while(feof(ft) == 0){
        fread(v, sizeof(int), 1, ft);
        fread(logico, sizeof(char), 20, ft);
        fread(fisico, sizeof(char), 20, ft);
        if(strcmp(logico, consulta) == 0){
            return 0;
        }
    }
    return 1;
};


int main(){
    long int num;
    int resultado, v[1];
    char consulta[20];
    char tabela_logico[20];
    char tabela_fisico[20];

    FILE *ft = fopen("table.dic", "rb");
    scanf("%s", consulta);

    resultado = encontra_tabela(ft, v, consulta, tabela_logico, tabela_fisico);
    if(resultado){
        printf("Tabela não encontrada!\n");
    } else {

        printf("\n****TABELA****\n\n");
        printf("id: %d\ntabela: %s\narquivo: %s\n\n\n", v[0], tabela_logico, tabela_fisico);

        FILE *fe = fopen("att.dic", "rb");
        Atributo atributo;
        while(feof(fe) == 0){
            fread(&atributo, sizeof(Atributo), 1, fe);
            printf("id: %d\nnome: %s\ntipo: %s\nopcional: %d\ntamanho: %d\n\n", atributo.id[0], atributo.nome, atributo.tipo , atributo.op[0], atributo.tam[0]);
            // if(atributo.id[0] == v[0]){
            //     break;
            // } 
        }
    }



    fclose(ft);

    return 0;
}