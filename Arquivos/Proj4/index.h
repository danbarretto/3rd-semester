#include <stdlib.h>
#include <stdio.h>
#include "registro.h"
typedef struct index{
    char chaveBusca[120];
    long byteOffset;
}Index;

Index* createAllIndex(Dados *allRegs, int *total);
void writeIndex(FILE* entrada, Index* indexes, int total);
int searchIndex(FILE* fileDados,Lista* l, char* nomeBusca, Index* indexes, int* totalRegs, int* nPagsDados, int operation);
void printRegFromDataFile(FILE* file, long offset);
Index* readIndexFromFile(FILE* file, int* totalRegs, int* nPagsIndex);
void insertRegIntoIndex(Index* indexes, int *total, long offset, char* nomeServidor);
int compareIndex(const void* A, const void* B);