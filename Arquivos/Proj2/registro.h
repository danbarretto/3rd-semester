#include <stdio.h>
#include <stdlib.h>

typedef struct cab{
    char status;
    long topoLista;
    char campos[5][40];
    char tags[5];
}Cabecalho;

typedef struct dados{
    char removido;
    int tamanhoRegistro;
    long int encadeamentoLista;
    int idServidor;
    double salarioServidor;
    char telefoneServidor[14];
    int tamNomeServidor;
    char* nomeServidor;
    int tamCargoServidor;
    char* cargoServidor;
} Dados;


typedef struct pag
{
    int nPags;
    char *conteudo;
}Pagina;

FILE *escreveBin(FILE *fEntrada, Pagina *p);
Pagina* criaPagina();
void destroiPag(Pagina* p);
void printRegs(FILE* entrada);
void searchRegs(FILE* entrada, char* campo, char* val);