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
    long int num;
    while(getc(ft) != EOF){
        fseek(ft, -1, SEEK_CUR);
        fread(tabela, sizeof(Tabela), 1, ft);
        if(strcmp(tabela->logico, consulta) == 0){
            fclose(ft);
            return 0;
        }
    }
    num = ftell(ft);
    printf("Posicao: %d\n", num);
    return 1;
};

int encontra_atributos(){

}



int main(){
    long int num;
    int resultado;
    char consulta[20];
    Tabela tabela;

    scanf("%s", consulta);

    resultado = encontra_tabela(&tabela, consulta);

    if(resultado){
        printf("Tabela nao encontrada!\n");
        
    } else {

        printf("\n****TABELA****\n\n");
        printf("id: %d\ntabela: %s\narquivo: %s\n\n\n", tabela.cod, tabela.logico, tabela.fisico);

        FILE *fe = fopen("att.dic", "rb");
        Atributo atributo;
        while(feof(fe) == 0){
            fread(&atributo, sizeof(Atributo), 1, fe);
            printf("id: %d\nnome: %s\ntipo: %c\nopcional: %d\ntamanho: %d\n\n", atributo.id, atributo.nome, atributo.tipo, atributo.op, atributo.tam);
            if(atributo.id == tabela.cod){
                break;
            } 
        }
    }



    

    return 0;
}