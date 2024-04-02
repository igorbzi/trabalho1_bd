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

int encontra_tabela(Tabela *tabela, char *consulta);
int encontra_atributos(Tabela tabela, Atributo *atributos);
void imprime_dados(char *arquivo, Atributo *lista_att, int qtd_att);
void imprime_cabecalho(Atributo *atributos, int qtd_att);
int read_file(char consulta[20]);
