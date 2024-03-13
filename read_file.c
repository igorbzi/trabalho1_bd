#include <stdio.h>
#include <string.h>

typedef struct {
    int cod;
    char logico[20];
    char fisico[20];
} Tabela;

typedef struct {
    int id;
    char nome[20];
    char tipo;
    char op;
    int tam;
} Atributo;


int encontra_tabela(Tabela *tabela, char *consulta){
    FILE *ft = fopen("table.dic", "rb");
    while(getc(ft) != EOF){
        fseek(ft, -1, SEEK_CUR);
        fread(tabela, sizeof(Tabela), 1, ft);
        if(strcmp(tabela->logico, consulta) == 0){
            fclose(ft);
            return 0;
        }
    }
    return 1;
};

int encontra_atributos(Tabela tabela, Atributo atributo){
    FILE *fe = fopen("att.dic", "rb");
    while(getc(fe) != EOF){
        fseek(fe, -1, SEEK_CUR);
        fread(&atributo, sizeof(Atributo), 1, fe);
        if(atributo.id == tabela.cod){
            printf("id: %d\nnome: %s\ntipo: %c\nopcional: %d\ntamanho: %d\n\n", atributo.id, atributo.nome, atributo.tipo, atributo.op, atributo.tam);
        }
    }
    return 0;
}



int main(){
    long int num;
    int retorno_tab, retorno_att;
    char consulta[20];
    Tabela tabela;
    Atributo atributo;

    scanf("%s", consulta);

    retorno_tab = encontra_tabela(&tabela, consulta);

    if(retorno_tab){
        printf("Tabela nao encontrada!\n");
        
    } else {
        printf("\n****TABELA****\n\n");
        printf("id: %d\ntabela: %s\narquivo: %s\n\n\n", tabela.cod, tabela.logico, tabela.fisico);
        retorno_att = encontra_atributos(tabela, atributo);
    }
    return 0;
}