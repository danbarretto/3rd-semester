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

typedef struct no{
    struct no* prox;
    int tamanhoReg;
    long offset;

}No;

typedef struct _lista
{
    No *ini, *fim;
    int tam;
}Lista;

Lista* criaLista();
void insereLista(Lista* l, No* novo);
No* criaNo(int tamanhoReg, long offset);
void destroiLista(Lista* l);
void printLista(Lista* l);

FILE *escreveBin(FILE *fEntrada, Pagina *p);
Cabecalho escreveCabecalho(Pagina* p, FILE* entrada, FILE* saida, int arqEhBinario);
Pagina* criaPagina();
void destroiPag(Pagina* p);
void printRegs(FILE* entrada);
int searchRegs(FILE* entrada, char* campo, char* val, int printNow);
void findRegToRemove(FILE* entrada, char campo, char* val, Lista *l);
void insertOnRemoved(FILE* entrada, Dados *dadosLidos, int n);
void readFirstNode(FILE* entrada, Lista* l);
void writeRemovedIntoFile(FILE* entrada, Lista* l);
int checkStatus(FILE* entrada);
void findRegToUpdate(FILE* entrada, Lista* l,char campoBusca, char* valBusca, char campoAtualiza, char* valAtualiza);
void updateReg(FILE* entrada,Lista* l, Dados* d, char* valAtualiza, char campoAtualiza, long offset);
void updateEncadeamento(FILE* entrada, Lista *l);
void changeStatus(FILE* entrada, char status);
Dados* getAllReg(FILE* entrada, int* totalREgs);
int compareIds(const void *A, const void* B);
void writeAllRegs(FILE* entrada, Dados* allRegs, int total);
void merging(FILE* entrada, FILE* entrada2, FILE* saida);
void matching(FILE* entrada, FILE* entrada2, FILE* saida);
Dados* getReg(FILE* entrada, Dados* d, int* nPags, int* nRegs, long* nBytes, char* tag1, char* tag2, int isPrinting);