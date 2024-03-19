#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Tabela{
    int cod;
    char logico[20];
    char fisico[20];
} Tabela;

typedef struct Atributo{
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

int encontra_atributos(Tabela tabela, Atributo *atributos){
    FILE *fe = fopen("att.dic", "rb");
    Atributo aux;
    int i = 0;
    while(getc(fe) != EOF){
        fseek(fe, -1, SEEK_CUR);
        fread(&aux, sizeof(Atributo), 1, fe);
        if(aux.id == tabela.cod){
            atributos[i] = aux;
            i++;
        }
    }
    return i;
}

int imprime_dados(char *arquivo, Atributo *lista_att, int qtd_att){
    
    char letra;
    char *string;
    int num_int;
    double num_double;
    FILE * fd = fopen(arquivo, "rb");

    while(getc(fd) != EOF){
        fseek(fd, -1, SEEK_CUR);
        for(int i=0;i<qtd_att; i++){
            switch(lista_att[i].tipo){
                case 'C':
                    fread(&letra, sizeof(char), 1, fd);
                    printf("%c ", letra);
                    break;
                case 'S':
                    string = malloc(lista_att[i].tam);
                    fread(string, lista_att[i].tam, 1, fd);
                    printf("%s ", string);
                    free(string); 
                    break;
                case 'I':
                    fread(&num_int, sizeof(int), 1, fd);
                    printf("%d ", num_int);
                    break;
                case 'D':
                    fread(&num_double, sizeof(double), 1, fd);
                    printf("%lf ", num_double);
                    break;
            }
        }
        printf("\n");
    }
    
    fclose(fd);
    return 0;
}

int main(){
    long int num;
    int retorno_tab, retorno_att;
    char consulta[20];
    Tabela tabela;
    Atributo atributos[100];

    scanf("%s", consulta);

    retorno_tab = encontra_tabela(&tabela, consulta);

    if(retorno_tab){
        printf("tabela nao encontrada!\n");
        
    } else {
        printf("\n****TABELA****\n\n");
        printf("id: %d\ntabela: %s\narquivo: %s\n\n\n", tabela.cod, tabela.logico, tabela.fisico);
        retorno_att = encontra_atributos(tabela, atributos);
        if(!retorno_att){
            printf("esquema nao encontrado!\n");
            return 0;
        }
        
        for(int i=0;i<retorno_att;i++){
            printf("id: %d\nnome: %s\ntipo: %c\nop: %d\ntamanho: %d\n\n", atributos[i].id, atributos[i].nome, atributos[i].tipo, atributos[i].op, atributos[i].tam);
        }

        imprime_dados(tabela.fisico, atributos, retorno_att);

    }
    return 0;
}