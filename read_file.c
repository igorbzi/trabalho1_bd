#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_file.h"

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
}

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

void imprime_dados(char *arquivo, Atributo *lista_att, int qtd_att){
    
    char *string;
    int num_int;
    double num_double;
    FILE * fd = fopen(arquivo, "rb");

    while(getc(fd) != EOF){
        fseek(fd, -1, SEEK_CUR);

        printf("|");

        for(int i = 0; i < qtd_att; i++){
            switch(lista_att[i].tipo){

                case 'S':
                    string = malloc(lista_att[i].tam);
                    fread(string, lista_att[i].tam, 1, fd);
                    if((int)strlen(lista_att[i].nome)>lista_att[i].tam){
                        printf(" %-*s ", (int)strlen(lista_att[i].nome), string);
                    } else {
                        printf(" %-*s ", lista_att[i].tam , string);
                    }
                    printf("|");
                    free(string); 
                    break;

                case 'I':
                    fread(&num_int, sizeof(int), 1, fd);
                    if((int)strlen(lista_att[i].nome)>10){
                        printf(" %*d ", (int)strlen(lista_att[i].nome), num_int);
                    } else {
                        printf(" %*d ", 10, num_int);
                    }
                    printf("|");
                    break;

                case 'D':
                    fread(&num_double, sizeof(double), 1, fd);
                    if((int)strlen(lista_att[i].nome)>10){
                        printf(" %*.2lf ", (int)strlen(lista_att[i].nome), num_double);
                    } else {
                        printf(" %*.2lf ", 10, num_double);
                    }
                    printf("|");
                    break;
            }
        }
        printf("\n");
    }
    
    fclose(fd);
    return;
}

void imprime_cabecalho(Atributo *atributos, int qtd_att){
    printf("|");

    for(int i = 0; i < qtd_att; i++){
        if(atributos[i].tipo == 'S'){
            if((int)strlen(atributos[i].nome)>atributos[i].tam){
                printf(" %-*s |", (int)strlen(atributos[i].nome), atributos[i].nome);
            } else {
                printf(" %-*s |", atributos[i].tam, atributos[i].nome);
            }
        } else {
            if((int)strlen(atributos[i].nome)>10){
                printf(" %*s |", (int)strlen(atributos[i].nome), atributos[i].nome);
            } else {
                printf(" %*s |", 10, atributos[i].nome);
            }
        }

    }
    printf("\n");
    return;
}

int read_file(char consulta[20]){
    int retorno_tab, retorno_att;
    Tabela tabela;
    Atributo atributos[25];

    retorno_tab = encontra_tabela(&tabela, consulta);

    if(retorno_tab){

        printf("TABLE NOT FOUND\n");
        return 0;
    }

    retorno_att = encontra_atributos(tabela, atributos);
    
    if(!retorno_att){
        printf("SCHEMA NOT FOUND\n");
        return 0;
    }

    imprime_cabecalho(atributos, retorno_att);
    imprime_dados(tabela.fisico, atributos, retorno_att);

    
    return 0;
}
