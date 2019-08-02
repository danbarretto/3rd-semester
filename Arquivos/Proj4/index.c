#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "merge_sort.h"

void removeRegFromIndex(Index* indexes,int pos, int total);
void addRegToList(FILE* fileDados, Index* indexes, int pos, Lista* l);
/*
    Função escreveCabecalhoIndex: escreve a página de disco de cabeçalho no arquivo de índice
    Parâmetros:
    FILE* file -> Arquivo a ser alterado
    int totalRegs -> Número de registros
*/ 
void escreveCabecalhoIndex(FILE* file, int totalRegs){
    char at='@';
    char status = '0';
    int totalRegistros = totalRegs;
    fwrite(&status, sizeof(char), 1, file);
    fwrite(&totalRegistros, sizeof(int), 1, file);
    //Completa a página com @
    for(int i=0; i<32000-5; i++)
        fwrite(&at, sizeof(char), 1, file);
}

/*
    Função compareIndex: compara 2 índices retornando a diferença entre byteOffset quando as chaves são iguais
    ou o resultado de strcmp entre as 2 chaves de busca
    Parâmetros:
    const void* A -> Endereço do primeiro índice
    const void* B -> Endereço do segundo índice
*/
int compareIndex(const void* A, const void* B){
    Index* iA = (Index *)A;
    Index* iB = (Index *)B;
    if(strcmp(iB->chaveBusca, iA->chaveBusca)==0){
        return iB->byteOffset-iA->byteOffset;
    }else{
        return strcmp(iB->chaveBusca, iA->chaveBusca);
    }
}

/*
    Função createAllIndex: Cria um vetor de índices com todos os índices de registros que possuem
    nomes não nulos
    Parâmetros:
    Dados* allRegs -> Vetor contendo todos os registros lidos
    int* total -> Endereço do número total de registros lidos
    Retorno:
    Index* indexes -> Vetor com todos índices criados
*/
Index* createAllIndex(Dados *allRegs, int *total){
    Index* indexes = calloc(1, sizeof(Index));
    int j=0, totalInd=1;
    for(int i=0; i<*total; i++){
        if(allRegs[i].tamNomeServidor){
            strcpy(indexes[j].chaveBusca, allRegs[i].nomeServidor);
            //Completa string de chave com @
            memset(indexes[j].chaveBusca+strlen(allRegs[i].nomeServidor)+1, '@', 120-strlen(allRegs[i].nomeServidor));
            //Encadeamento lista previamente usado para guardar offset
            indexes[j].byteOffset = allRegs[i].encadeamentoLista;
            j++;
            totalInd++;
            indexes = realloc(indexes, sizeof(Index)*(totalInd));
        }
    }
    //Ordena vetor após todas inserções
    MS_sort(indexes, totalInd-1, sizeof(Index), compareIndex);
    *total = totalInd-1;
    return indexes;
}

/*
    Função writeIndex: escreve todos os índices do vetor passado no arquivo de índice
    Parâmetros:
    FILE* saida -> arquivo a ser alterado
    Index* indexes -> vetor com todos os índices
    int total -> número total de índices
*/
void writeIndex(FILE* saida, Index* indexes, int total){
    escreveCabecalhoIndex(saida, total);
    //Página de disco de cabeçalho pulada
    fseek(saida, 32000, SEEK_SET);
    for(int i=0; i<total; i++){
        fwrite(indexes[i].chaveBusca, sizeof(char)*120, 1, saida);
        fwrite(&indexes[i].byteOffset, sizeof(long), 1, saida);
    }
}

/*
    Função searchIndex: realiza uma busca binária no vetor de índices e realiza a operação passada
    Parâmetros:
    FILE* fileDados -> arquivo de dados
    Lista* l ->lista de registros removidos
    char* nomeBusca -> chave a ser buscada
    Index* indexes -> vetor de índices
    int* totalRegs -> endereço para o número total de registros no índice
    int* nPagsDados -> endereço do número total de páginas de disco do arquivo de dados lidas
    int operation -> operação a ser realizada (1 para impressão/2 para remoção)
    Retorno:
    int regsFound -> Número de registros encontrados
*/
int searchIndex(FILE* fileDados,Lista* l, char* nomeBusca, Index* indexes, int* totalRegs, int* nPagsDados, int operation){
    int lastPage=0, nPages=1, ini=0, meio, topo=*totalRegs-3, regsFound=0;
    //vetor de índices copiado para um vetor temporário para permitir alterações no índice
    Index* temp = calloc(*totalRegs, sizeof(Index));
    memcpy(temp, indexes, *totalRegs*sizeof(Index));
    while(ini<=topo){
        meio = (topo+ini)/2;
        //Caso índice seja encontrado e não foi modificado
        if(strcmp(temp[meio].chaveBusca, nomeBusca)==0 && temp[meio].chaveBusca[0]!='*'){
            //Checa se índice encontrado está na mesma página de disco que o índice previamente encontrado
            if(lastPage != (int) temp[meio].byteOffset/32000){
                nPages++;
                lastPage = (int) temp[meio].byteOffset/32000;
            }
            //Impressão
            if(operation==1)
                printRegFromDataFile(fileDados, temp[meio].byteOffset);
            else if(operation==2){ //Remoção
                addRegToList(fileDados, indexes, meio, l);
                removeRegFromIndex(indexes, meio, *totalRegs);
                //Número de registros do índice alterado
                *totalRegs = *totalRegs-1;   
            }
            //Índice marcado com * para indicar que já foi alterado
            temp[meio].chaveBusca[0]='*';
            regsFound++;
            //ínicio modificado para permitir a continuação da busca binária
            ini++;
        }else if(strcmp(temp[meio].chaveBusca, nomeBusca) > 0){
            topo = meio - 1;
        }else{
            ini = meio + 1;
        }    
    }
    free(temp);
    *nPagsDados = nPages;
    return regsFound;
}

/*
    Função printRegFromDataFile: Imprime todas informações de um registro no arquivo de Dados de acordo com offset passado
    Parâmetros:
    FILE* file -> arquivo de dados
    long offset -> offset do registro a ser impresso
*/
void printRegFromDataFile(FILE* file, long offset){
    char tag1='a', tag2='b';
    int nomeOk=0, cargoOk=0;
    Dados temp;
    //Posiciona arquivo a partir do idServidor
    fseek(file, offset+13, SEEK_SET);
    //Leitura dos dados
    fread(&temp.idServidor, sizeof(int), 1, file);
    fread(&temp.salarioServidor, sizeof(double), 1, file);
    fread(temp.telefoneServidor, sizeof(char)*14, 1, file);
    temp.telefoneServidor[14]='\0';
    fread(&temp.tamNomeServidor, sizeof(int), 1, file);
    fread(&tag1, sizeof(char), 1, file);
    if(tag1=='n'){ //Caso nome não nulo
        nomeOk=1;
        temp.nomeServidor = calloc(1, temp.tamNomeServidor-1);
        fread(temp.nomeServidor, sizeof(char)*temp.tamNomeServidor-1, 1, file);
    }
    else if(tag1=='c'){ //Caso nome nulo e cargo não nulo
        cargoOk=1;
        //Corrige campos de tamanho
        temp.tamCargoServidor = temp.tamNomeServidor;
        temp.tamNomeServidor = 0;
        temp.cargoServidor = calloc(1, temp.tamCargoServidor-1);
        fread(temp.cargoServidor, sizeof(char)*temp.tamCargoServidor-1, 1, file);
    }

    if(tag1=='n'){
        fread(&temp.tamCargoServidor, sizeof(int), 1, file);
        fread(&tag2, sizeof(char), 1, file);
        if(tag2=='c'){//Caso nome e cargo não nulos    
            cargoOk=1;
            temp.cargoServidor = calloc(1, temp.tamCargoServidor-1);
            fread(temp.cargoServidor, sizeof(char)*temp.tamCargoServidor-1, 1, file);
        }
    }
    //Impressão dos dados lidos com tratamento para valores nulos

    //----------------------idServidor-----------------------------------
    printf("numero de identificacao do servidor: %d\n", temp.idServidor);
    //-------------------------------------------------------------------

    //----------------------salarioServidor------------------------------
    if(temp.salarioServidor!=-1 && temp.salarioServidor!=0)
        printf("salario do servidor: %.2lf\n", temp.salarioServidor);
    else
        printf("salario do servidor: valor nao declarado\n");
    //-------------------------------------------------------------------

    //----------------------telefoneServidor-----------------------------
    if(strcmp(temp.telefoneServidor, "")==0)
        printf("telefone celular do servidor: valor nao declarado\n");
    else
        printf("telefone celular do servidor: %s\n", temp.telefoneServidor);
    //--------------------------------------------------------------------

    //----------------------nomeServidor----------------------------------
    if(nomeOk){
        printf("nome do servidor: %s\n", temp.nomeServidor);
        free(temp.nomeServidor);
    }else
        printf("nome do servidor: valor nao declarado\n");
    //---------------------------------------------------------------------
    //----------------------cargoServidor----------------------------------        
    if(cargoOk){
        printf("cargo do servidor: %s\n\n", temp.cargoServidor);
        free(temp.cargoServidor);
    }else
        printf("cargo do servidor: valor nao declarado\n\n");
    //---------------------------------------------------------------------
}

/*
    Função readIndexFromFile: Lê todos os índices de um arquivo de índices e retorna um vetor contendo
    todos os registros lidos
    Parâmetros:
    FILE* file -> arquivo de índices
    int* totalRegs -> Endereço do número total de registros lidos
    int* nPagsIndex -> Número de páginas de disco do arquivo de índice lidas
    Retorno:
    Index* indexes -> vetor contendo todos os índices
*/
Index* readIndexFromFile(FILE* file, int* totalRegs, int* nPagsIndex){
    int nRegs=0;
    fseek(file, 1, SEEK_SET);
    //Leitura do número de registros
    fread(&nRegs, sizeof(int), 1, file);
    //página de cabeçalho pulada
    fseek(file, 32000, SEEK_SET);
    Index* indexes = calloc(nRegs, sizeof(Index));
    long offset=32000;
    for(int i=0; i<nRegs; i++){
        fread(indexes[i].chaveBusca, sizeof(char)*120, 1, file);
        fread(&indexes[i].byteOffset, sizeof(long), 1, file);
        offset+=128;
    }
    *nPagsIndex = (int) offset/32000 +1;
    *totalRegs = nRegs;
    return indexes;
}

/*
    Função removeRegFromIndex: remove um índice do vetor de índices de acordo com a posição e realiza um shift
    para esquerda com os índices subsequentes
    Parâmetros:
    Index* indexes -> vetor de índices
    int pos -> posição no vetor do índice a ser removido
    int total -> número total de índices no vetor
*/
void removeRegFromIndex(Index* indexes,int pos, int total){
    for(int i=pos; i<total-1; i++){
        memcpy(indexes[i].chaveBusca, indexes[i+1].chaveBusca, 120);
        indexes[i].byteOffset = indexes[i+1].byteOffset;
    }

}

/*
    Função addRegToList: adiciona registro encontrado por busca no índice na lista encadeada
    de registros a serem removidos
    Parâmetros:
    FILE* fileDados ->arquivo de dados
    Index* indexes -> vetor de índices
    int pos -> posição do registro a ser removido
    Lista* l -> lista de registros removidos
*/
void addRegToList(FILE* fileDados, Index* indexes, int pos, Lista* l){
    fseek(fileDados, indexes[pos].byteOffset+1, SEEK_SET);
    int tamReg=0;
    fread(&tamReg, sizeof(int), 1, fileDados);
    insereLista(l, criaNo(tamReg, indexes[pos].byteOffset));
}

/*
    Função insertRegIntoIndex: insere um novo índice no vetor de índices no final do vetor
    Parâmetros:
    Index* indexes -> vetor de índices
    int* total -> endereço do número total de índices
    long offset -> byteOffset do novo índice
    char* nomeServidor -> chave de busca do novo índices
*/
void insertRegIntoIndex(Index* indexes, int *total, long offset, char* nomeServidor){
    *total = *total +1;
    indexes = realloc(indexes,sizeof(Index)* (*total));
    indexes[*total-1].byteOffset = offset;
    strcpy(indexes[*total-1].chaveBusca, nomeServidor);
    //Chave busca completada com @ até o último caracter
    memset(indexes[*total - 1].chaveBusca+strlen(nomeServidor)+1, '@', 119-strlen(nomeServidor));

}