#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct matriz
{
    int linhas,  colunas;
    double dado[MAX][MAX];    
}Matriz;

Matriz leia_matriz(){
    Matriz novaMAt;
    scanf("%d %d", &novaMAt.linhas, &novaMAt.colunas);
    for(int i=0; i<novaMAt.linhas; i++){
        for(int j=0;j<novaMAt.colunas; j++){
            scanf("%lf", &novaMAt.dado[i][j]);
        }
    }
    
    return novaMAt;
}

void escreva_matriz(Matriz mat){
    for(int i=0; i<mat.linhas; i++){
        for(int j=0;j<mat.colunas; j++){
            printf("%lf ", mat.dado[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[]){
    int inicio, fim;
    scanf("%d %d", &inicio, &fim);
    FILE *f = fopen("teste.txt", "r");
    char linha[100];
    for(int i=1; i<fim; i++){
        fgets(linha, sizeof linha, f);
        if(i>=inicio)
            printf("%s", linha);
    }
}
