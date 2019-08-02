#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escreverTela2.h"
#include "index.h"
#include "merge_sort.h"

/*
  Funcionalidade 3
  Parâmetros:
  FILE* fEntrada -> arquivo de entrada
  char* fileName -> nome do arquivo de entrada
  char* campo -> campo que será feita a busca
  char* val -> valor a ser buscado
  int printNow -> flag para decidir se a impressão será feita no momento (1) ou posteriormente pela funcionalidade 14 (0)
  Retorno:
  int nPags -> número de páginas de disco lidas do arquivo passado
*/
int func3(FILE* fEntrada, char* fileName, char* campo, char* val, int printNow){
  
  if ((fEntrada = fopen(fileName, "rb")) == NULL) {
    printf("Falha no processamento do arquivo.\n");
    free(val);
    free(fileName);
    exit(0);
    }
    if (checkStatus(fEntrada) == 0) {
      free(fileName);
      free(val);
      fclose(fEntrada);
      exit(0);
    }
    changeStatus(fEntrada, '0');
    int nPags = searchRegs(fEntrada, campo, val, printNow);
    changeStatus(fEntrada, '1');
    fclose(fEntrada);
    return nPags;
}

/*
  Funcionalidade 11
  Parâmetros:
  FILE* fEntrada -> arquivo de dados
  FILE* fEntrada2 -> arquivo de índice
  char* fileName -> nome do arquivo de dados
  char* file2Name -> nome do arquivo de índices
  char* nomeBusca -> nome a ser buscado
  int printNow -> flag para decidir se impressão será realizada no momento (1) ou posteriormente pela funcionalidade 14 (0) 
*/
void func11(FILE* fEntrada, FILE* fEntrada2, char* fileName, char* file2Name, char* nomeBusca, int printNow, int* nPagDados, int* nPagIndex){
  int totalEntrada2=0;
  if ((fEntrada = fopen(fileName, "rb")) == NULL) {
        free(fileName);
        free(file2Name);
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
      }
      if ((fEntrada2 = fopen(file2Name, "rb")) == NULL) {
        free(fileName);
        free(file2Name);
        fclose(fEntrada);
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
      }
      if(checkStatus(fEntrada)==0){
        fclose(fEntrada);
        fclose(fEntrada2);
        free(fileName);
        free(file2Name);
        exit(0);
      }
      if(checkStatus(fEntrada2)==0){
        fclose(fEntrada);
        fclose(fEntrada2);
        free(fileName);
        free(file2Name);
        exit(0);
      }
      changeStatus(fEntrada, '0');
      changeStatus(fEntrada2, '0');
      //Leitura do arquivo de índices
      
      Index* indexes = readIndexFromFile(fEntrada2, &totalEntrada2, nPagIndex);
      Lista* l = criaLista();
      readFirstNode(fEntrada, l);
      int nRegs = searchIndex(fEntrada,l, nomeBusca, indexes, &totalEntrada2, nPagDados, 1);
      if(nRegs && printNow){
        printf("Número de páginas de disco para carregar o arquivo de índice: %d\n", *nPagIndex);
        printf("Número de páginas de disco para acessar o arquivo de dados: %d\n", *nPagDados);
      }else if(!nRegs){
        printf("Registro inexistente.\n");
      }
      changeStatus(fEntrada, '1');
      changeStatus(fEntrada2, '1');
      if(fEntrada){
        free(fileName);
        fclose(fEntrada);
      }
      if(fEntrada2){
        free(file2Name);
        fclose(fEntrada2);
      }
      free(nomeBusca);
      destroiLista(l);
      if(indexes) free(indexes);
      
}

// Daniel Sá Barretto Prado Garcia
// nº 10374344
int main(int argc, char const* argv[]) {
  int op;
  scanf("%d", &op);
  char *fileName, *nomeSaida, *file2Name, *salario;
  char* valCampo;
  char nomeCampo[40];
  char tagCampo;
  FILE *fEntrada, *fEntrada2, *fSaida;
  Pagina* temp, *p;
  int n;
  long* offsets;
  Lista* l;
  Index* indexes;
  Dados* dadosLidos;
  int totalEntrada = 0, totalEntrada2 = 0, nPagsIndex=0, nPagsDados=0;
  switch (op) {
    case 1:
      // Funcionalidade 1
      p = criaPagina();
      if ((fEntrada = fopen(fileName, "r")) == NULL) {
        printf("Falha no carregamento do arquivo.\n");
        free(p->conteudo);
        free(p);
        free(fileName);
        exit(0);
      }
      if (checkStatus(fEntrada) == 0) {
        free(fileName);
        fclose(fEntrada);
        free(p);
        exit(0);
      }
      fSaida = escreveBin(fEntrada, p);
      changeStatus(fEntrada, '0');
      if (fSaida) {
        changeStatus(fSaida, '1');
        fclose(fSaida);
        printf("arquivoTrab1.bin");
      }
      if (fEntrada) {
        changeStatus(fEntrada, '1');
        fclose(fEntrada);
      }
      destroiPag(p);
      free(fileName);
      break;
    case 2:
      // Funcionalidade 2
      fileName = calloc(40, sizeof(char));
      fscanf(stdin, "%s", fileName);
      if ((fEntrada = fopen(fileName, "rb")) == NULL) {
        printf("Falha no processamento do arquivo.\n");
        free(fileName);
        exit(0);
      }
      if (checkStatus(fEntrada) == 0) {
        free(fileName);
        fclose(fEntrada);
        exit(0);
      }
      changeStatus(fEntrada, '0');
      printRegs(fEntrada);
      changeStatus(fEntrada, '1');
      fclose(fEntrada);
      free(fileName);
      break;
    case 3:
      // Funcionalidade 3
      fileName = calloc(40, sizeof(char));
      char campo[40];
      char* val = calloc(100, sizeof(char));
      scanf("%s %s %[^\n]", fileName, campo, val);
      // Remove caracter \r
      for (int i = 0; i < strlen(val) + 1; i++) {
        if (val[i] == '\r') {
          val[i] = '\0';
        }
      }
      func3(fEntrada, fileName, campo, val, 1);
      free(fileName);
      break;

    case 4:
      // Funcionalidade 4
      fileName = calloc(40, sizeof(char));
      scanf("%s %d", fileName, &n);
      if ((fEntrada = fopen(fileName, "r+b")) == NULL) {
        printf("Falha no processamento do arquivo.\n");
        free(fileName);
        exit(0);
      }
      // checa status do arquivo
      if (checkStatus(fEntrada) == 0) {
        free(fileName);
        fclose(fEntrada);
        exit(0);
      }
      changeStatus(fEntrada, '0');
      valCampo = calloc(100, sizeof(char*));
      tagCampo = 'a';
      l = criaLista();
      readFirstNode(fEntrada, l);
      for (int i = 0; i < n; i++) {
        scanf("%s", nomeCampo);
        tagCampo = nomeCampo[0];
        scan_quote_string(valCampo);
        findRegToRemove(fEntrada, tagCampo, valCampo, l);
      }
      // Remoção dos registros dados pela lista
      writeRemovedIntoFile(fEntrada, l);
      changeStatus(fEntrada, '1');
      binarioNaTela1(fEntrada);
      fclose(fEntrada);
      destroiLista(l);
      free(valCampo);
      free(fileName);
      break;

    case 5:
      // funcionalidade 5
      fileName = calloc(40, sizeof(char));
      scanf("%s %d", fileName, &n);
      if ((fEntrada = fopen(fileName, "r+b")) == NULL) {
        printf("Falha no processamento do arquivo.\n");
        free(fileName);
        exit(0);
      }
      if (checkStatus(fEntrada) == 0) {
        free(fileName);
        fclose(fEntrada);
        exit(0);
      }
      changeStatus(fEntrada, '0');
      dadosLidos = calloc(n, sizeof(Dados));
      salario = calloc(10, sizeof(char));
      // leitura de todos os novos registros
      for (int i = 0; i < n; i++) {
        dadosLidos[i].cargoServidor = calloc(50, sizeof(char));
        dadosLidos[i].nomeServidor = calloc(50, sizeof(char));
        scanf("%d", &(dadosLidos[i].idServidor));
        scanf("%s", salario);
        if (strcmp(salario, "NULO") == 0) {
          dadosLidos[i].salarioServidor = -1;
        } else {
          dadosLidos[i].salarioServidor = atof(salario);
        }
        scan_quote_string(dadosLidos[i].telefoneServidor);
        scan_quote_string(dadosLidos[i].nomeServidor);
        scan_quote_string(dadosLidos[i].cargoServidor);
      }

      // inserção
      insertOnRemoved(fEntrada, dadosLidos, n);
      for (int i = 0; i < n; i++) {
        free(dadosLidos[i].nomeServidor);
        free(dadosLidos[i].cargoServidor);
      }
      free(salario);
      free(dadosLidos);
      free(fileName);
      changeStatus(fEntrada, '1');
      binarioNaTela1(fEntrada);
      fclose(fEntrada);
      break;
    case 6:
      // funcionalidade 6
      fileName = calloc(40, sizeof(char));
      scanf("%s %d", fileName, &n);
      if ((fEntrada = fopen(fileName, "r+b")) == NULL) {
        printf("Falha no processamento do arquivo.\n");
        free(fileName);
        exit(0);
      }
      if (checkStatus(fEntrada) == 0) {
        free(fileName);
        fclose(fEntrada);
        exit(0);
      }
      changeStatus(fEntrada, '0');
      char* camposBusca = NULL;
      char* camposAtualiza = NULL;
      char* valsBusca = NULL;
      char* valsAtualiza = NULL;
      char* tagsCampoBusca = calloc(n, sizeof(char));
      char* tagsCampoAtualiza = calloc(n, sizeof(char));
      l = criaLista();
      readFirstNode(fEntrada, l);
      for (int i = 0; i < n; i++) {
        valsAtualiza = calloc(200, sizeof(char));
        valsBusca = calloc(200, sizeof(char));
        scanf("%ms", &camposBusca);
        tagsCampoBusca[i] = camposBusca[0];
        scan_quote_string(valsBusca);
        scanf("%ms", &camposAtualiza);
        tagsCampoAtualiza[i] = camposAtualiza[0];
        scan_quote_string(valsAtualiza);
        findRegToUpdate(fEntrada, l, tagsCampoBusca[i], valsBusca,
                        tagsCampoAtualiza[i], valsAtualiza);
        free(camposAtualiza);
        free(camposBusca);
        free(valsAtualiza);
        free(valsBusca);
      }
      // Atualização do encadeamento no arquivo
      updateEncadeamento(fEntrada, l);
      destroiLista(l);
      changeStatus(fEntrada, '1');
      binarioNaTela1(fEntrada);
      free(tagsCampoAtualiza);
      free(tagsCampoBusca);
      fclose(fEntrada);
      break;
    case 7:
      // Funcionalidade 7
      fileName = calloc(40, sizeof(char));
      scanf("%s", fileName);
      if ((fEntrada = fopen(fileName, "rb")) == NULL) {
        free(fileName);
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
      }
      if (checkStatus(fEntrada) == 0) {
        free(fileName);
        fclose(fEntrada);
        exit(0);
      }

      nomeSaida = calloc(40, sizeof(char));
      scanf("%s", nomeSaida);
      if ((fSaida = fopen(nomeSaida, "wb")) == NULL) {
        free(fileName);
        free(nomeSaida);
        fclose(fEntrada);
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
      }
      temp = criaPagina();
      escreveCabecalho(temp, fEntrada, fSaida, 1);
      destroiPag(temp);
      int total = 0;
      Dados* res = getAllReg(fEntrada, &total);
      MS_sort(res, total, sizeof(Dados), compareIds);
      writeAllRegs(fSaida, res, total);
      if (fSaida) {
        changeStatus(fSaida, '1');
        fclose(fSaida);
      }
      binarioNaTela2(nomeSaida);
      if (fEntrada) {
        changeStatus(fEntrada, '1');
        fclose(fEntrada);
      }
      free(fileName);
      for (int i = 0; i < total; i++) {
        if (res[i].nomeServidor) free(res[i].nomeServidor);
        if (res[i].cargoServidor) free(res[i].cargoServidor);
      }
      free(res);
      free(nomeSaida);

      break;
    case 8:
    //Funcionalidade 8
      fileName = calloc(40, sizeof(char));
      char* file2Name = calloc(40, sizeof(char));
      nomeSaida = calloc(40, sizeof(char));
      scanf("%s %s %s", fileName, file2Name, nomeSaida);
      if ((fEntrada = fopen(fileName, "rb")) == NULL) {
        free(fileName);
        free(file2Name);
        free(nomeSaida);
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
      }
      if ((fEntrada2 = fopen(file2Name, "rb")) == NULL) {
        free(fileName);
        free(file2Name);
        free(nomeSaida);
        fclose(fEntrada);
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
      }
      if ((fSaida = fopen(nomeSaida, "wb")) == NULL) {
        free(fileName);
        free(file2Name);
        free(nomeSaida);
        fclose(fEntrada2);
        fclose(fEntrada);
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
      }

      if (checkStatus(fEntrada) == 0 || checkStatus(fEntrada2) == 0) {
        free(fileName);
        free(file2Name);
        free(nomeSaida);
        fclose(fEntrada);
        fclose(fEntrada2);
        fclose(fSaida);
        exit(0);
      }
      changeStatus(fEntrada, '0');
      changeStatus(fEntrada2, '0');
      changeStatus(fSaida, '0');
      temp = criaPagina();
      escreveCabecalho(temp, fEntrada, fSaida, 1);
      destroiPag(temp);
      merging(fEntrada, fEntrada2, fSaida);
      changeStatus(fEntrada, '1');
      changeStatus(fEntrada2, '1');
      changeStatus(fSaida, '1');
      if (fEntrada) fclose(fEntrada);
      if (fEntrada2) fclose(fEntrada2);
      if (fSaida) fclose(fSaida);

      binarioNaTela2(nomeSaida);

      free(file2Name);
      free(fileName);
      free(nomeSaida);
      break;
    case 9:
    //Funcionalidade 9
      fileName = calloc(40, sizeof(char));
      file2Name = calloc(40, sizeof(char));
      nomeSaida = calloc(40, sizeof(char));
      scanf("%s %s %s", fileName, file2Name, nomeSaida);
      if ((fEntrada = fopen(fileName, "rb")) == NULL) {
        free(fileName);
        free(file2Name);
        free(nomeSaida);
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
      }
      if ((fEntrada2 = fopen(file2Name, "rb")) == NULL) {
        free(fileName);
        free(file2Name);
        free(nomeSaida);
        fclose(fEntrada);
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
      }
      if ((fSaida = fopen(nomeSaida, "wb")) == NULL) {
        free(fileName);
        free(file2Name);
        free(nomeSaida);
        fclose(fEntrada2);
        fclose(fEntrada);
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
      }

      if (checkStatus(fEntrada) == 0 || checkStatus(fEntrada2) == 0) {
        free(fileName);
        free(file2Name);
        free(nomeSaida);
        fclose(fEntrada);
        fclose(fEntrada2);
        fclose(fSaida);
        exit(0);
      }
      changeStatus(fEntrada, '0');
      changeStatus(fEntrada2, '0');
      changeStatus(fSaida, '0');
      temp = criaPagina();
      escreveCabecalho(temp, fEntrada, fSaida, 1);
      destroiPag(temp);
      matching(fEntrada, fEntrada2, fSaida);
      changeStatus(fEntrada, '1');
      changeStatus(fEntrada2, '1');
      changeStatus(fSaida, '1');
      if (fEntrada) fclose(fEntrada);
      if (fEntrada2) fclose(fEntrada2);
      if (fSaida) fclose(fSaida);

      binarioNaTela2(nomeSaida);

      free(file2Name);
      free(fileName);
      free(nomeSaida);
      break;
    case 10:
    //Funcionalidade 10
      fileName =  calloc(40, sizeof(char));
      nomeSaida = calloc(50, sizeof(char));
      scanf("%s %s", fileName, nomeSaida);
      if ((fEntrada = fopen(fileName, "rb")) == NULL) {
        free(fileName);
        free(nomeSaida);
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
      }
      if ((fSaida = fopen(nomeSaida, "wb")) == NULL) {
        free(fileName);
        free(nomeSaida);
        fclose(fEntrada);
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
      }
      if(checkStatus(fEntrada)==0){
        fclose(fEntrada);
        fclose(fSaida);
        free(fileName);
        free(nomeSaida);
        exit(0);
      }
      Dados* allRegs = getAllReg(fEntrada, &totalEntrada);
      int oldTotal=totalEntrada;
      indexes = createAllIndex(allRegs, &totalEntrada);
      writeIndex(fSaida, indexes, totalEntrada);
      for(int i=0; i<oldTotal; i++){
        if(allRegs[i].tamNomeServidor)
          free(allRegs[i].nomeServidor);
        if(allRegs[i].tamCargoServidor)
          free(allRegs[i].cargoServidor);
      }
      free(allRegs);
      free(indexes);

      changeStatus(fSaida, '1');
      if(fSaida){
        fclose(fSaida);
        binarioNaTela2(nomeSaida);
        free(nomeSaida);
      }
      if(fEntrada){
        changeStatus(fEntrada, '1');
        fclose(fEntrada);
        free(fileName);
      }
      break;
    case 11:
    //Funcionalidade 11
      fileName =  calloc(40, sizeof(char));
      file2Name = calloc(50, sizeof(char));
      char* nomeBusca = calloc(120, sizeof(char));
      char campoNome[12];
      scanf("%s %s %s %[^\n]", fileName, file2Name,campoNome, nomeBusca);
      func11(fEntrada, fEntrada2, fileName, file2Name, nomeBusca, 1, &nPagsDados, &nPagsIndex);
      break;
    case 12:
    //Funcionalidade 12
    //Reaproveitamento de código da funcionalidade 4 com adição de funções de tratamento de índices
      fileName = calloc(40, sizeof(char));
      file2Name = calloc(40, sizeof(char));
      scanf("%s %s %d", fileName,file2Name, &n);
      if ((fEntrada = fopen(fileName, "r+b")) == NULL) {
        printf("Falha no processamento do arquivo.\n");
        free(fileName);
        exit(0);
      }
      if ((fEntrada2 = fopen(file2Name, "rb")) == NULL) {
        printf("Falha no processamento do arquivo.\n");
        free(file2Name);
        free(fileName);
        fclose(fEntrada);
        exit(0);
      }
      // checa status do arquivo
      if (checkStatus(fEntrada) == 0) {
        free(fileName);
        fclose(fEntrada);
        exit(0);
      }if (checkStatus(fEntrada2) == 0) {
        free(file2Name);
        fclose(fEntrada2);
        fclose(fEntrada);
        free(fileName);
        exit(0);
      }
      changeStatus(fEntrada, '0');
      changeStatus(fEntrada2, '0');
      valCampo = calloc(100, sizeof(char*));
      tagCampo = 'a';

      indexes = readIndexFromFile(fEntrada2, &totalEntrada2, &nPagsIndex);
      //Reabre o arquivo para escrita para apagar os conteúdos antigos
      fclose(fEntrada2);
      if ((fEntrada2 = fopen(file2Name, "wb")) == NULL) {
        printf("Falha no processamento do arquivo.\n");
        free(file2Name);
        free(fileName);
        fclose(fEntrada);
        exit(0);
      }
      l = criaLista();
      readFirstNode(fEntrada, l);
      for (int i = 0; i < n; i++) {
        scanf("%s", nomeCampo);
        tagCampo = nomeCampo[0];
        scan_quote_string(valCampo);
        searchIndex(fEntrada, l, valCampo, indexes, &totalEntrada2, &nPagsIndex, 2);
      }
      // Remoção dos registros dados pela lista
      writeRemovedIntoFile(fEntrada, l);

      writeIndex(fEntrada2, indexes, totalEntrada2);
      changeStatus(fEntrada, '1');
      changeStatus(fEntrada2, '1');
      fclose(fEntrada);
      fclose(fEntrada2);
      binarioNaTela2(file2Name);
      destroiLista(l);
      free(valCampo);
      free(fileName);
      break;
    case 13:
      //Funcionalidade 13
      //Reaproveitamento de código da funcionalidade 5 com adição de funções de tratamento de índices
      fileName = calloc(40, sizeof(char));
      file2Name =  calloc(40, sizeof(char));
      scanf("%s %s %d", fileName,file2Name, &n);
      if ((fEntrada = fopen(fileName, "r+b")) == NULL) {
        printf("Falha no processamento do arquivo.\n");
        free(fileName);
        exit(0);
      }
      if ((fEntrada2 = fopen(file2Name, "rb")) == NULL) {
        printf("Falha no processamento do arquivo.\n");
        free(file2Name);
        free(fileName);
        fclose(fEntrada);
        exit(0);
      }
      // checa status do arquivo
      if (checkStatus(fEntrada) == 0) {
        free(fileName);
        fclose(fEntrada);
        exit(0);
      }if (checkStatus(fEntrada2) == 0) {
        free(file2Name);
        fclose(fEntrada2);
        fclose(fEntrada);
        free(fileName);
        exit(0);
      }
      
      changeStatus(fEntrada, '0');
      changeStatus(fEntrada2, '0');
      indexes = readIndexFromFile(fEntrada2, &totalEntrada2, &nPagsIndex);
      fclose(fEntrada2);
      //Reabertura do arquivo de índices como wb para apagar conteúdo antigo
      if ((fEntrada2 = fopen(file2Name, "wb")) == NULL) {
        printf("Falha no processamento do arquivo.\n");
        free(file2Name);
        free(fileName);
        fclose(fEntrada);
        exit(0);
      }
      dadosLidos = calloc(n, sizeof(Dados));
      salario = calloc(10, sizeof(char));
      // leitura de todos os novos registros
      for (int i = 0; i < n; i++) {
        dadosLidos[i].cargoServidor = calloc(50, sizeof(char));
        dadosLidos[i].nomeServidor = calloc(50, sizeof(char));
        scanf("%d", &(dadosLidos[i].idServidor));
        scanf("%s", salario);
        
        if (strcmp(salario, "NULO") == 0) {
          dadosLidos[i].salarioServidor = -1;
        } else {
          dadosLidos[i].salarioServidor = atof(salario);
        }
        scan_quote_string(dadosLidos[i].telefoneServidor);
        scan_quote_string(dadosLidos[i].nomeServidor);
        scan_quote_string(dadosLidos[i].cargoServidor);
      }
      
      // inserção
      insertOnRemoved(fEntrada, dadosLidos, n);
      for (int i = 0; i < n; i++) {
        if(strcmp(dadosLidos[i].nomeServidor, "")!=0){
          insertRegIntoIndex(indexes, &totalEntrada2, dadosLidos[i].encadeamentoLista, dadosLidos[i].nomeServidor);
        }
        free(dadosLidos[i].nomeServidor);
        free(dadosLidos[i].cargoServidor);
      }
      //Reordenação dos índices
      MS_sort(indexes, totalEntrada2, sizeof(Index), compareIndex);
      writeIndex(fEntrada2, indexes, totalEntrada2);
      free(salario);
      free(dadosLidos);
      free(fileName);
      changeStatus(fEntrada, '1');
      changeStatus(fEntrada2, '1');
      fclose(fEntrada);
      binarioNaTela2(file2Name);
      break;
    case 14:
    //Funcionalidade 14
      fileName =  calloc(40, sizeof(char));
      file2Name = calloc(50, sizeof(char));
      nomeBusca = calloc(120, sizeof(char));
      scanf("%s %s %s %[^\n]", fileName, file2Name,campoNome, nomeBusca);
      printf("*** Realizando a busca sem o auxílio de índice\n");
      int nPags= func3(fEntrada, fileName, campoNome, nomeBusca, 0);
      printf("Número de páginas de disco acessadas: %d\n", nPags);
      printf("*** Realizando a busca com o auxílio de um índice secundário fortemente ligado\n");
      func11(fEntrada, fEntrada2, fileName, file2Name, nomeBusca, 0, &nPagsDados, &nPagsIndex);
      printf("Número de páginas de disco para carregar o arquivo de índice: %d\n", nPagsIndex);
      printf("Número de páginas de disco para acessar o arquivo de dados: %d\n", nPagsDados);
      printf("\nA diferença no número de páginas de disco acessadas: %d\n", nPags - nPagsDados);
      break;
  }

  return 0;
}
