#include "registro.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Função destroiLista: desaloca toda a memória utilizada pela lista e seus nós
  Parâmetros:
  Lista *l -> endereço da Lista a ser desalocada
*/
No* criaNo(int tamanhoReg, long offset) {
  No* n = calloc(1, sizeof(No));
  n->offset = offset;
  n->tamanhoReg = tamanhoReg;
}

/*
  Função criaLista: alloca memória para estrutura e inicializa os valores das
  componentes l -> endereço da estrutura nova criada
*/
Lista* criaLista() {
  Lista* l = calloc(1, sizeof(Lista));
  l->ini = NULL;
  l->fim = NULL;
  l->tam = 0;
}

/*
  Função destroiLista: desaloca toda a memória utilizada pela lista e seus nós
  Parâmetros:
  Lista *l -> endereço da Lista a ser desalocada
*/
void destroiLista(Lista* l) {
  No* aux = l->ini;
  No* temp;
  while (aux) {
    temp = aux;
    aux = aux->prox;
    free(temp);
  }
}

/*
  Função removeNode: remove nó da fila e corrige encadeamento
  Parâmetros:
  Lista *l -> Lista a ser modificada
  No* n -> nó a ser removido
*/
void removeNode(Lista* l, No* n) {
  No* temp = l->ini;
  // Caso o nó esteja no início
  if (temp != NULL && temp->tamanhoReg == n->tamanhoReg) {
    l->ini = temp->prox;
    free(temp);
    return;
  }
  No* ant;
  // busca o nó
  while (temp && temp->tamanhoReg != n->tamanhoReg) {
    ant = temp;
    temp = temp->prox;
  }
  ant->prox = temp->prox;
  free(temp);
}
/*
  Função insereListaEnd: insere nó no final da lista, atualizando o encadeamento
  Parâmetros:
  Lista* l -> lista a ser alterada
  No* novo -> nó a ser inserido
*/
void insereListaEnd(Lista* l, No* novo) {
  if (novo == NULL) return;
  // atualiza encadeamento
  if (l->tam == 0) {
    l->ini = novo;
  } else
    l->fim->prox = novo;
  l->fim = novo;
  l->tam++;
}
/*
  Função changeStatus: Troca primeiro byte do arquivo para o status desejado para então manejar eventuais
  erros de processamento do arquivo
  Parâmetros:
  FILE* entrada -> arquivo a ser alterado
  char status -> valor a ser escrito '0' para status de falha e '1' para status de sucesso
*/
void changeStatus(FILE* entrada, char status){
  fseek(entrada, 0, SEEK_SET);
  fwrite(&status, sizeof(char), 1 , entrada);
  fseek(entrada, -1, SEEK_CUR);
}
/*
  Função insereLista: insere nó ordenadamente de acordo com o tamanho do
  registro Parâmetros: Lista* l -> lista a ser alterada No* novo -> nó a ser
  inserido
*/
void insereLista(Lista* l, No* novo) {
  // Caso nó seja menor que o início
  if (l->ini == NULL || l->ini->tamanhoReg >= novo->tamanhoReg) {
    novo->prox = l->ini;
    l->ini = novo;
  } else {
    No* aux = l->ini;
    // Busca pelo lugar correto no encadeamento
    while (aux->prox && aux->prox->tamanhoReg < novo->tamanhoReg) {
      aux = aux->prox;
    }
    novo->prox = aux->prox;
    aux->prox = novo;
  }
  l->tam++;
}

/*
    Função criaCabecalho: Preenche os dados de cabeçalho de acordo com os
   aquivos lidos 
   Parâmetros: 
   Cabecalho* cab -> estrutura que guarda os dados de
   cabeçalho FILE* entrada -> Arquivo a ser lido int arqEhBinario -> operando
   que decide qual método de leitura será utilizado, sendo 1 para arquivo
   binário e 0 para arquivo de texto
*/
void criaCabecalho(Cabecalho* cab, FILE* entrada, int arqEhBinario) {
  // leitura de arquivo de texto
  if (!arqEhBinario) {
    cab->topoLista = -1;
    cab->tags[0] = 'i';
    cab->tags[1] = 's';
    cab->tags[2] = 't';
    cab->tags[3] = 'n';
    cab->tags[4] = 'c';
    /*formato de cada linha do arquivo:
      campo[0],campo[1],campo[2],campo[3],campo[4]
    */
    fscanf(entrada, "%[^,]", cab->campos[0]);
    for (int i = 1; i < 4; i++) {
      fscanf(entrada, ",%[^,]", cab->campos[i]);
    }
    // leitura até \r
    fscanf(entrada, ",%[^\r\n]", cab->campos[4]);
  } else {
    fseek(entrada, 1, SEEK_SET);
    fread(&cab->topoLista, sizeof(long), 1, entrada);
    for (int i = 0; i < 5; i++) {
      fread(&cab->tags[i], sizeof(char), 1, entrada);
      fread(cab->campos[i], sizeof(char) * 40, 1, entrada);
    }
  }

  // completa as descrições do campo com @
  for (int i = 0; i < 5; i++) {
    for (int k = strlen(cab->campos[i]) + 1; k < 40; k++) {
      cab->campos[i][k] = '@';
    }
  }
}
/*
    Função destroiDados: Libera memória alocada para estrutura Dados
    Parâmetros:
    Dados *d -> Endereço a ser liberado
*/
void destroiDados(Dados* d) {
  if (d->nomeServidor) free(d->nomeServidor);
  if (d->cargoServidor) free(d->cargoServidor);
  if (d) free(d);
}

/*
    Função escreveCabecalho: Preenche uma página de disco com os dados de
   cabeçalho e depois a completa com '@' Parâmetros: Pagina *p-> estrutura de
   dados que guarda vetor de 32000 bytes, que representa conteúdo da página de
   disco, e o número de páginas FILE* entrada-> arquivo a ser lido FILE* saida->
   Arquivo com os dados escritos Retorno: Cabecalho cab -> dados de cabeçalho
   lidos do arquivo de entrada
*/
Cabecalho escreveCabecalho(Pagina* p, FILE* entrada, FILE* saida) {
  /*Para reduzir o número de acessos à disco, copia-se todos os dados de
   cabeçalho lidos para um vetor 32000 bytes, completa as posições restantes com
   '@' e grava esse vetor no arquivo de saida
   */
  Cabecalho cab;
  criaCabecalho(&cab, entrada, 0);
  // byteOffset = posição atual do ponteiro
  int byteOffset = 0;
  memcpy(p->conteudo, &cab.status, sizeof(char));
  byteOffset += sizeof(char);
  memcpy(p->conteudo + byteOffset, &cab.topoLista, sizeof(long));
  byteOffset += sizeof(long);
  for (int i = 0; i < 5; i++) {
    memcpy(p->conteudo + byteOffset, &cab.tags[i], sizeof(char));
    byteOffset += sizeof(char);
    memcpy(p->conteudo + byteOffset, cab.campos[i], sizeof(char) * 40);
    byteOffset += sizeof(char) * 40;
  }
  // completa o restante da paágina de disco com '@'
  for (int i = byteOffset; i < 32000; i++) {
    p->conteudo[i] = '@';
  }
  // Escrita do conteúdo no arquivo
  fwrite(p->conteudo, sizeof(char), 32000, saida);
  p->nPags++;
  free(p->conteudo);
  // realocação de memória para os próximos registros
  p->conteudo = calloc(32000, sizeof(char));
  return cab;
}

/*
    Função checkStatus: lê o primeiro byte do arquivo, caso seja 0, retorna
   mensagem de erro e termina o programa Parâmetro: FILE* entrada: arquivo a ser
   checado
*/
int checkStatus(FILE* entrada) {
  char status;
  fread(&status, sizeof(char), 1, entrada);
  if (status == '0') {
    printf("Falha no processamento do arquivo.\n");
    return 0;
  }
  return 1;
}

/*
    Função criaPagina: aloca memória para estrutura Pagina
    Retorno: Ponteiro sobre a memória alocada
*/
Pagina* criaPagina() {
  Pagina* p = calloc(1, sizeof(Pagina));
  p->nPags = 0;
  p->conteudo = calloc(32000, sizeof(char));
  return p;
}
/*
    Função destroiPag: libera memória da estrutura Pagina
    Parâmetro:
    Pagina *p: endereço da memória a ser liberada
*/
void destroiPag(Pagina* p) {
  free(p->conteudo);
  free(p);
}
/*
    Função escreveBin: Lê todos os registros de um arquivo csv e os passa para
   um arquivo binário Parâmetros: FILE *fEntrada -> arquivo de entrada a ser
   lido Pagina *p -> estrutura que guarda dados lidos do arquivo Retorno: FILE
   *saida -> arquivo com os dados escritos
*/
FILE* escreveBin(FILE* fEntrada, Pagina* p) {
  FILE* saida;
  if ((saida = fopen("arquivoTrab1.bin", "wb")) == NULL) {
    printf("Falha no carregamento do arquivo\n");
    return saida;
  }

  changeStatus(saida, '0');
  // Escreve a primeira página de disco com o cabeçalho
  Cabecalho c = escreveCabecalho(p, fEntrada, saida);

  int byteOffset = 0;

  // posição do campo tamanhoRegistro do último registro lido
  int lastTamOffset = 0;

  while (1) {
    // Estrutura Dados guarda todos os campos que um registro contém
    Dados* d = calloc(1, sizeof(Dados));
    int nomeOk = 1, cargoOk = 1;
    d->cargoServidor = calloc(1000, sizeof(char));
    d->nomeServidor = calloc(1000, sizeof(char));
    // Caso a leitura do primeiro byte seja EOF, a memoria alocada por Dados *d
    // é liberada
    if (fscanf(fEntrada, "%d,", &(d->idServidor)) == EOF) {
      destroiDados(d);
      break;
    }

    if (fscanf(fEntrada, "%lf,", &(d->salarioServidor)) == 0) {
      // Tratamento de dado nulo
      d->salarioServidor = -1;
    }
    if (fscanf(fEntrada, "%[^,]", d->telefoneServidor) == 0) {
      // Tratamento de dado nulo
      d->telefoneServidor[0] = '\0';
      for (int i = 1; i < 14; i++) d->telefoneServidor[i] = '@';
    }
    if (fscanf(fEntrada, ",%[^,]", d->nomeServidor) == 0) {
      // Flag de nome nulo
      nomeOk = 0;
    }
    if (fscanf(fEntrada, ",%[^\r\n]", d->cargoServidor) == 0) {
      // Flag de cargo nulo
      cargoOk = 0;
    }
    // Nos tamanhos dos campos cargoServidor e nomeServido são contabilizados as
    // tags 'n' e 'c' e os caracteres \0
    d->tamCargoServidor = strlen(d->cargoServidor) + 2;
    d->tamNomeServidor = strlen(d->nomeServidor) + 2;
    d->removido = '-';
    d->encadeamentoLista = -1;
    // tamanho de registro calculado (caso nome ou cargo sejam nulos, não serão
    // contabilizados os campos de tamanho, tag e valor)
    d->tamanhoRegistro =
        sizeof(d->encadeamentoLista) + sizeof(d->idServidor) +
        sizeof(d->salarioServidor) + sizeof(char) * 14 +
        nomeOk *
            (sizeof(d->tamNomeServidor) + sizeof(char) * d->tamNomeServidor) +
        cargoOk *
            (sizeof(d->tamCargoServidor) + sizeof(char) * d->tamCargoServidor);

    // caso o registro lido não caiba na página de disco, a página atual é
    // completada com '@' e uma nova página é criada
    if (d->tamanhoRegistro + 5 > 32000 - byteOffset) {
      int nArrobas = 0;
      for (int i = byteOffset; i < 32000; i++) {
        p->conteudo[i] = '@';
        nArrobas++;
      }
      int tamFix = 0;
      // tamanho do último registro é copiado
      memcpy(&tamFix, &p->conteudo[lastTamOffset], sizeof(int));
      // tamanho é incrementado com o número de @ inseridos
      tamFix += nArrobas;
      memcpy(p->conteudo + lastTamOffset, &tamFix, sizeof(int));
      // página de disco é gravada no arquivo
      fwrite(p->conteudo, sizeof(char), 32000, saida);
      p->nPags++;
      free(p->conteudo);
      // nova página de disco é criada
      p->conteudo = calloc(32000, sizeof(char));
      byteOffset = 0;
    }
    //---------------Cópia dos dados lidos para o vetor de
    // bytes---------------------------------------------------------
    memcpy(p->conteudo + byteOffset, &d->removido, sizeof(char));
    byteOffset += sizeof(char);

    lastTamOffset = byteOffset;
    memcpy(p->conteudo + byteOffset, &d->tamanhoRegistro, sizeof(int));
    byteOffset += sizeof(int);

    memcpy(p->conteudo + byteOffset, &d->encadeamentoLista, sizeof(long int));
    byteOffset += sizeof(long int);

    memcpy(p->conteudo + byteOffset, &d->idServidor, sizeof(int));
    byteOffset += sizeof(int);

    memcpy(p->conteudo + byteOffset, &d->salarioServidor, sizeof(double));
    byteOffset += sizeof(double);

    memcpy(p->conteudo + byteOffset, d->telefoneServidor, sizeof(char) * 14);
    byteOffset += sizeof(char) * 14;

    // Dados referentes ao nome são escritos apenas se este não for nulo
    if (nomeOk) {
      memcpy(p->conteudo + byteOffset, &d->tamNomeServidor, sizeof(int));
      byteOffset += sizeof(int);

      memcpy(p->conteudo + byteOffset, &(c.tags[3]), sizeof(char));
      byteOffset += sizeof(char);

      memcpy(p->conteudo + byteOffset, d->nomeServidor,
             sizeof(char) * d->tamNomeServidor - 1);
      byteOffset += sizeof(char) * d->tamNomeServidor - 1;
    }
    // Dados referentes ao cargo são escritos apenas se este não for nulo
    if (cargoOk) {
      memcpy(p->conteudo + byteOffset, &d->tamCargoServidor, sizeof(int));
      byteOffset += sizeof(int);
      memcpy(p->conteudo + byteOffset, &(c.tags[4]), sizeof(char));
      byteOffset += sizeof(char);

      memcpy(p->conteudo + byteOffset, d->cargoServidor,
             sizeof(char) * d->tamCargoServidor - 1);
      byteOffset += sizeof(char) * d->tamCargoServidor - 1;
    }
    //------------------------------------------------------------------------------------------------------------------------------
    if (d->nomeServidor != NULL) free(d->nomeServidor);
    if (d->cargoServidor != NULL) free(d->cargoServidor);
    if (d != NULL) free(d);
  }
  //Última página de disco é gravada no arquivo
  if (byteOffset) {
    fwrite(p->conteudo, sizeof(char), byteOffset, saida);
  }

  return saida;
}
/*
    Função readAts: Posiciona ponteiro do arquivo no útlimo '@' lido
    Parâmetros:
    FILE *entrada -> arquivo lido
*/
void readAts(FILE* entrada) {
  char arroba;
  fread(&arroba, sizeof(char), 1, entrada);
  while (arroba == '@') {
    fread(&arroba, sizeof(char), 1, entrada);
  }
  fseek(entrada, -1, SEEK_CUR);
}

/*
    Função getReg: Lê registros de arquivo binário e os retorna com seus
   respectivos tratamento de valores nulos Parâmetros: FILE *entrada -> arquivo
   lido Dados *d -> Estrutura que guarda os dados de todos os campos do registro
    int *nPags -> Endereço no número de páginas de disco acessadas
    int *nRegs -> Endereço do número de registros encontrados
    long *nBytes -> Endereço do número de bytes lidos
    char *tag1 -> Endereço da primeira tag lida
    char *tag2 -> Endereço da segunda tag lida
    int isPrinting -> Determina se o registro encontrado será impresso
*/
Dados* getReg(FILE* entrada, Dados* d, int* nPags, int* nRegs, long* nBytes,
              char* tag1, char* tag2, int isPrinting) {
  int endOfPage = 0;
  char* salario = calloc(20, sizeof(char));
  d = calloc(1, sizeof(Dados));
  fread(&d->removido, sizeof(char), 1, entrada);
  // Caso primeiro campo do registro seja nulo, retorna nulo simbolizando o fim
  // do arquivo
  if (!d->removido) {
    free(salario);
    if (d->nomeServidor) free(d->nomeServidor);
    if (d->cargoServidor) free(d->cargoServidor);
    if (d) free(d);
    return NULL;
  }
  fread(&d->tamanhoRegistro, sizeof(int), 1, entrada);

  if (d->tamanhoRegistro) {
    (*nRegs)++;
    // incrementa o número de bytes lidos com o tamanho do registro + tamanho do
    // byte de removido + o tamanho do int de tamanho de registro
    *nBytes += d->tamanhoRegistro + 5;
  }
  // Página de disco lida por completo
  if (*nBytes == 32000) {
    *nBytes = 0;
    (*nPags)++;
    endOfPage = 1;
  }
  if (d->removido == '*') {
    fseek(entrada, d->tamanhoRegistro, SEEK_CUR);
    return d;
  }

  fread(&d->encadeamentoLista, sizeof(long), 1, entrada);
  fread(&d->idServidor, sizeof(int), 1, entrada);
  fread(&d->salarioServidor, sizeof(double), 1, entrada);

  // Copia o valor dsalarioo salário para uma string para facilitar tratamento
  // de nulo
  sprintf(salario, "%.2lf", d->salarioServidor);
  if (d->salarioServidor == -1 && isPrinting) strcpy(salario, "        ");

  fread(d->telefoneServidor, sizeof(char) * 14, 1, entrada);
  // Tratamento de nulo
  if (strcmp(d->telefoneServidor, "") == 0)
    strcpy(d->telefoneServidor, "              ");

  fread(&d->tamNomeServidor, sizeof(int), 1, entrada);
  fread(tag1, sizeof(char), 1, entrada);
  if (d->tamNomeServidor && *tag1 == 'n') {
    // Caso o nome seja não nulo
    d->nomeServidor = calloc(d->tamNomeServidor, sizeof(char));
    fread(d->nomeServidor, sizeof(char) * d->tamNomeServidor - 1, 1, entrada);
  } else if (d->tamNomeServidor && *tag1 == 'c') {
    // Caso nome seja nulo e cargo seja não nulo
    d->cargoServidor = calloc(d->tamNomeServidor, sizeof(char));
    fread(d->cargoServidor, sizeof(char) * d->tamNomeServidor - 1, 1, entrada);
    if (isPrinting && d->removido == '-')
      printf("%d %s %s %d %s\n", d->idServidor, salario, d->telefoneServidor,
             d->tamNomeServidor - 2, d->cargoServidor);
    free(salario);
    if (endOfPage) {
      // Posiciona arquivo no último @
      readAts(entrada);
    }
    // retorna Dados com nome nulo
    return d;
  } else {
    // Caso nome e cargo sejam nulos
    // retorna ponteiro para antes da tag e do indicador de tamanho
    fseek(entrada, -5, SEEK_CUR);
    if (endOfPage) {
      readAts(entrada);
    }
    fread(&d->tamCargoServidor, sizeof(int), 1, entrada);
    fread(&tag2, sizeof(char), 1, entrada); 
    if (*tag2 != 'c') {
      fseek(entrada, -5, SEEK_CUR);
      if (isPrinting && d->removido == '-')
        printf("%d %s %s\n", d->idServidor, salario, d->telefoneServidor);
    }
    free(salario);
    // Retorna Dados com nome e cargo nulos
    return d;
  }

  fread(&d->tamCargoServidor, sizeof(int), 1, entrada);
  fread(tag2, sizeof(char), 1, entrada);
  if (*tag2 == 'c') {
    // Caso nome e cargo sejam não nulos
    d->cargoServidor = calloc(d->tamCargoServidor, sizeof(char));
    fread(d->cargoServidor, sizeof(char) * d->tamCargoServidor - 1, 1, entrada);
    if (isPrinting && d->removido == '-')
      printf("%d %s %s %d %s %d %s\n", d->idServidor, salario,
             d->telefoneServidor, d->tamNomeServidor - 2, d->nomeServidor,
             d->tamCargoServidor - 2, d->cargoServidor);
    free(salario);
    if (endOfPage) {
      readAts(entrada);
    }
    // Retorna Dados com cargo e nome não nulos
    return d;
  } else {
    // Caso nome seja não nulo e cargo seja nulo
    if (isPrinting && d->removido == '-')
      printf("%d %s %s %d %s\n", d->idServidor, salario, d->telefoneServidor,
             d->tamNomeServidor - 2, d->nomeServidor);
    // retorna ponteiro para posição antes da ultima tag e indicador de tamanho
    fseek(entrada, -5, SEEK_CUR);
    free(salario);
    if (endOfPage) {
      readAts(entrada);
    }
    // Retorna Dados com nome não nulo e cargo nulo
    return d;
  }
}
/*
    Função printRegs: imprime todos os registros de um arquivo binário dado
    Parâmetros:
    FILE *entrada -> arquivo lido
*/
void printRegs(FILE* entrada) {
  // Posiciona ponteiro após paǵina de disco dedicada ao cabeçalho
  fseek(entrada, 32000, SEEK_SET);
  char tag1 = 0, tag2 = 0;
  int nRegs = 0, nPags = 1;
  long nBytes = 0;
  //-------------------Leitura e impressão dos
  // registros---------------------------
  Dados* d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 1);
  while (d) {
    destroiDados(d);

    d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 1);
  }
  //-------------------------------------------------------------------------------
  //Última página de disco não é acessada até o final
  nPags++;
  if (!nRegs) {
    printf("Registro inexistente.\n");
    return;
  }
  printf("Número de páginas de disco acessadas: %d\n", nPags);
}

/*
    Função searchRegs: Procura registro em um arquivo binário e o imprime de
   acordo com campo passado e valor do campo Parâmetros: FILE *entrada ->
   arquivo lido char *campo -> qual campo será usado para a busca char *val ->
   valor a ser buscado
*/
void searchRegs(FILE* entrada, char* campo, char* val) {
  Cabecalho cab;
  // Recupera as informações de cabeçalho
  criaCabecalho(&cab, entrada, 1);

  // posiciona ponteiro no após primeira página de disco
  readAts(entrada);
  int nRegs = 0, nPags = 1, regsFound = 0;
  char tag1, tag2;
  long nBytes = 0;

  if (strcmp(campo, "idServidor") == 0) {
    // Caso campo seja o id do servidor
    int id = atoi(val);
    // Leitura do primeiro registro
    Dados* d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (d->idServidor == id && d->removido == '-') {
        regsFound++;
        //----------Impressão dos dados com seus tratamentos para valores
        // nulos----------
        printf("%s: %d\n", cab.campos[0], d->idServidor);
        if (d->salarioServidor == -1)
          printf("%s: valor nao declarado\n", cab.campos[1]);
        else
          printf("%s: %.2lf\n", cab.campos[1], d->salarioServidor);
        if (strcmp(d->telefoneServidor, "              ") == 0)
          printf("%s: valor nao declarado\n", cab.campos[2]);
        else
          printf("%s: %s\n", cab.campos[2], d->telefoneServidor);
        if (!d->nomeServidor)
          printf("%s: valor nao declarado\n", cab.campos[3]);
        else
          printf("%s: %s\n", cab.campos[3], d->nomeServidor);
        if (!d->cargoServidor)
          printf("%s: valor nao declarado\n\n", cab.campos[4]);
        else
          printf("%s: %s\n\n", cab.campos[4], d->cargoServidor);
        if (d->nomeServidor) free(d->nomeServidor);
        if (d->cargoServidor) free(d->cargoServidor);
        if (d) free(d);
        // Como id é único, basta achar a primeira ocorrência
        break;
        //---------------------------------------------------------------------------------
      }
      destroiDados(d);
      // lê o próximo registro
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    if (!regsFound) {
      printf("Registro inexistente.\n");
    }
  } else if (strcmp(campo, "salarioServidor") == 0) {
    // Caso o campo seja o salário do servidor
    double salario = atof(val);
    Dados* d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (d->salarioServidor == salario && d->removido == '-') {
        regsFound++;
        //----------Impressão dos dados com seus tratamentos para valores
        // nulos----------
        printf("%s: %d\n", cab.campos[0], d->idServidor);
        if (d->salarioServidor == -1)
          printf("%s: valor nao declarado\n", cab.campos[1]);
        else
          printf("%s: %.2lf\n", cab.campos[1], d->salarioServidor);
        if (strcmp(d->telefoneServidor, "              ") == 0)
          printf("%s: valor nao declarado\n", cab.campos[2]);
        else
          printf("%s: %s\n", cab.campos[2], d->telefoneServidor);
        if (!d->nomeServidor)
          printf("%s: valor nao declarado\n", cab.campos[3]);
        else
          printf("%s: %s\n", cab.campos[3], d->nomeServidor);
        if (!d->cargoServidor)
          printf("%s: valor nao declarado\n\n", cab.campos[4]);
        else
          printf("%s: %s\n\n", cab.campos[4], d->cargoServidor);
        //-----------------------------------------------------------------------------------
      }
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    if (!regsFound) {
      printf("Registro inexistente.\n");
    }
  } else if (strcmp(campo, "telefoneServidor") == 0) {
    // Caso o campo seja o telefone do servidor
    char tel[14];
    strcpy(tel, val);
    Dados* d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (strcmp(d->telefoneServidor, tel) == 0 && d->removido == '-') {
        regsFound++;
        //----------Impressão dos dados com seus tratamentos para valores
        // nulos----------
        printf("%s: %d\n", cab.campos[0], d->idServidor);
        if (d->salarioServidor == -1)
          printf("%s: valor nao declarado\n", cab.campos[1]);
        else
          printf("%s: %.2lf\n", cab.campos[1], d->salarioServidor);
        if (strcmp(d->telefoneServidor, "              ") == 0)
          printf("%s: valor nao declarado\n", cab.campos[2]);
        else
          printf("%s: %s\n", cab.campos[2], d->telefoneServidor);
        if (!d->nomeServidor)
          printf("%s: valor nao declarado\n", cab.campos[3]);
        else
          printf("%s: %s\n", cab.campos[3], d->nomeServidor);
        if (!d->cargoServidor)
          printf("%s: valor nao declarado\n\n", cab.campos[4]);
        else
          printf("%s: %s\n\n", cab.campos[4], d->cargoServidor);
        //-----------------------------------------------------------------------------------
      }
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    if (!regsFound) {
      printf("Registro inexistente.\n");
    }
  } else if (strcmp(campo, "nomeServidor") == 0) {
    // Caso o campo seja nome do servidor
    char nome[500];
    strcpy(nome, val);
    Dados* d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (d->nomeServidor) {
        if (strcmp(d->nomeServidor, nome) == 0 && d->removido == '-') {
          regsFound++;
          //----------Impressão dos dados com seus tratamentos para valores
          // nulos----------
          printf("%s: %d\n", cab.campos[0], d->idServidor);
          if (d->salarioServidor == -1)
            printf("%s: valor nao declarado\n", cab.campos[1]);
          else
            printf("%s: %.2lf\n", cab.campos[1], d->salarioServidor);
          if (strcmp(d->telefoneServidor, "              ") == 0)
            printf("%s: valor nao declarado\n", cab.campos[2]);
          else
            printf("%s: %s\n", cab.campos[2], d->telefoneServidor);
          if (!d->nomeServidor)
            printf("%s: valor nao declarado\n", cab.campos[3]);
          else
            printf("%s: %s\n", cab.campos[3], d->nomeServidor);
          if (!d->cargoServidor)
            printf("%s: valor nao declarado\n\n", cab.campos[4]);
          else
            printf("%s: %s\n\n", cab.campos[4], d->cargoServidor);
          //------------------------------------------------------------------------------------
        }
      }
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    if (!regsFound) {
      printf("Registro inexistente.\n");
    }
  } else if (strcmp(campo, "cargoServidor") == 0) {
    // Caso o campo seja o cargo do servidor
    char cargo[500];
    strcpy(cargo, val);
    Dados* d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (d->cargoServidor) {
        if (strcmp(d->cargoServidor, cargo) == 0 && d->removido == '-') {
          regsFound++;
          //----------Impressão dos dados com seus tratamentos para valores
          // nulos----------
          printf("%s: %d\n", cab.campos[0], d->idServidor);
          if (d->salarioServidor == -1)
            printf("%s: valor nao declarado\n", cab.campos[1]);
          else
            printf("%s: %.2lf\n", cab.campos[1], d->salarioServidor);
          if (strcmp(d->telefoneServidor, "              ") == 0)
            printf("%s: valor nao declarado\n", cab.campos[2]);
          else
            printf("%s: %s\n", cab.campos[2], d->telefoneServidor);

          if (!d->nomeServidor)
            printf("%s: valor nao declarado\n", cab.campos[3]);
          else
            printf("%s: %s\n", cab.campos[3], d->nomeServidor);
          if (!d->cargoServidor)
            printf("%s: valor nao declarado\n\n", cab.campos[4]);
          else
            printf("%s: %s\n\n", cab.campos[4], d->cargoServidor);
          //-------------------------------------------------------------------------------
        }
      }
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    if (!regsFound) {
      printf("Registro inexistente.\n");
    }
  } else {
    // Caso campo seja outro valor
    printf("Registro inexistente.\n");
  }
  if (nPags && regsFound) {
    //Última página de disco acessada
    nPags++;
    printf("Número de páginas de disco acessadas: %d\n", nPags);
  }
}
/*
  Função readFirstNode: lê o campo de topo lista no cabeçalho do arquivo e
  percorre o mesmo, montado a lista de encadeamento dos registros removidos
  Parâmetros:
  FILE* entrada -> ponteiro para arquivo a ser lido
  Lista* l -> endereço da lista a ser alterada
*/
void readFirstNode(FILE* entrada, Lista* l) {
  long firstOff;
  int firstTam;
  fseek(entrada, 1, SEEK_SET);
  fread(&firstOff, sizeof(long), 1, entrada);
  char remRead;
  if (firstOff != -1) {
    fseek(entrada, firstOff, SEEK_SET);
    fread(&remRead, sizeof(char), 1, entrada);
    fread(&firstTam, sizeof(int), 1, entrada);
    // percorre o arquivo até encontrar o offset -1
    do {
      if (remRead == '*') insereListaEnd(l, criaNo(firstTam, firstOff));
      fread(&firstOff, sizeof(long), 1, entrada);
      fseek(entrada, firstOff + 1, SEEK_SET);
      fread(&firstTam, sizeof(int), 1, entrada);
    } while (firstOff != -1);
  }
}

/*
  Função markRegAsRemoved: marca o primeiro byte de um registro com o caracter
  de removido (*) Parâmetros: FILE* entrada -> arquivo a ser alterado long
  offset -> posição inicial do registro no arquivo
*/
void markRegAsRemoved(FILE* entrada, long offset) {
  char removido = '*';
  // guarda-se a posição antiga no arquivo para evitar erro de leitura
  long oldOff = ftell(entrada);
  fseek(entrada, offset, SEEK_SET);
  fwrite(&removido, sizeof(char), 1, entrada);
  fseek(entrada, oldOff, SEEK_SET);
}

/*
  Função findRegToRemove: Busca registro de acordo com o campo e valor de busca
  passados para então adicionar-lo na lista encadeada para futura remoção
  Parâmetros:
  FILE* entrada -> arquivo a ser alterado
  char campo -> campo cuja busca será feita
  char* val -> valor a ser procurado
  Lista * -> lista a ser alterada
*/
void findRegToRemove(FILE* entrada, char campo, char* val, Lista* l) {
  Dados* d;
  int nPags = 1, nRegs = 0;
  long nBytes = 0, offset;
  char tag1, tag2;
  // Pula a página de cabeçalho
  fseek(entrada, 32000, SEEK_SET);
  offset = 32000;
  //--------------------------BUSCA DE PELO
  // IDSERVIDOR-----------------------------------------
  if (campo == 'i') {
    d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (d->idServidor == atoi(val) && d->removido == '-') {
        No* noReg = criaNo(d->tamanhoRegistro, offset);
        insereLista(l, noReg);
      }
      // atualização do offset
      offset += d->tamanhoRegistro + 5;
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    //-------------------------BUSCA PELO
    // NOMESERVIDOR--------------------------------------------
  } else if (campo == 'n') {
    d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (d->nomeServidor) {
        if (strcmp(d->nomeServidor, val) == 0 && d->removido == '-') {
          No* noReg = criaNo(d->tamanhoRegistro, offset);
          insereLista(l, noReg);
          // Alteração do caracter já é feita para evitar uma nova remoção
          markRegAsRemoved(entrada, offset);
        }
        // Caso seja buscado um valor nulo
      } else {
        if (strcmp(val, "") == 0 && d->removido == '-') {
          No* noReg = criaNo(d->tamanhoRegistro, offset);
          insereLista(l, noReg);
          markRegAsRemoved(entrada, offset);
        }
      }
      offset += d->tamanhoRegistro + 5;
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    //-----------------------BUSCA PELO
    // CARGOSERVIDOR------------------------------------------
  } else if (campo == 'c') {
    d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (d->cargoServidor) {
        if (strcmp(d->cargoServidor, val) == 0 && d->removido == '-') {
          No* noReg = criaNo(d->tamanhoRegistro, offset);
          insereLista(l, noReg);
          markRegAsRemoved(entrada, offset);
        }
      } else {
        if (strcmp(val, "") == 0 && d->removido == '-') {
          No* noReg = criaNo(d->tamanhoRegistro, offset);
          insereLista(l, noReg);
          markRegAsRemoved(entrada, offset);
        }
      }
      offset += d->tamanhoRegistro + 5;
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    //----------------------BUSCA PELO
    // TELEFONESERVIDOR-------------------------------------
  } else if (campo == 't') {
    d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (strcmp(d->telefoneServidor, val) == 0 && d->removido == '-') {
        No* noReg = criaNo(d->tamanhoRegistro, offset);
        insereLista(l, noReg);
        markRegAsRemoved(entrada, offset);
      } else if (strcmp(d->telefoneServidor, "              ") == 0 &&
                 strcmp(val, "") == 0 && d->removido == '-') {
        No* noReg = criaNo(d->tamanhoRegistro, offset);
        insereLista(l, noReg);
        markRegAsRemoved(entrada, offset);
      }
      offset += d->tamanhoRegistro + 5;
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    //-------------------------BUSCA PELO SALÁRIO
    // SERVIDOR--------------------------------------
  } else if (campo == 's') {
    d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (d->salarioServidor == atof(val) && d->removido == '-') {
        No* noReg = criaNo(d->tamanhoRegistro, offset);
        insereLista(l, noReg);
        markRegAsRemoved(entrada, offset);
      } else if ((d->salarioServidor == -1 || d->salarioServidor == 0) &&
                 strcmp(val, "") == 0 && d->removido == '-') {
        No* noReg = criaNo(d->tamanhoRegistro, offset);
        insereLista(l, noReg);
        markRegAsRemoved(entrada, offset);
      }
      offset += d->tamanhoRegistro + 5;
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
  }
}
/*
  Função printLista: imprime todos os nós de uma lista
  Parâmetros:
  Lista* l-> lista a ser impressa
*/
void printLista(Lista* l) {
  No* aux = l->ini;
  aux = l->ini;
  while (aux) {
    printf("%d %ld\n", aux->tamanhoReg, aux->offset);
    aux = aux->prox;
  }
}

/*
  Função writeRemovedIntoFile: Remove registros do arquivo seguindo o
  encadeamento dado pela Lista Parâmetros: FILE* entrada -> arquivo a ser
  alterado Lista* l -> lista de encadeamento dos registros
*/
void writeRemovedIntoFile(FILE* entrada, Lista* l) {
  No* aux = l->ini;
  char arr = '@', rem = '*';
  long last = -1;
  fseek(entrada, 1, SEEK_SET);
  // altera topo lista do cabeçalho do arquivo
  fwrite(&l->ini->offset, sizeof(long), 1, entrada);
  while (aux) {
    fseek(entrada, aux->offset, SEEK_SET);
    fwrite(&rem, sizeof(char), 1, entrada);
    fseek(entrada, 4, SEEK_CUR);
    if (aux->prox)
      fwrite(&(aux->prox->offset), sizeof(long), 1, entrada);
    else
      fwrite(&last, sizeof(long), 1, entrada);

    for (int i = 0; i < aux->tamanhoReg - 8; i++) {
      fwrite(&arr, sizeof(char), 1, entrada);
    }
    aux = aux->prox;
  }
}
/*
  Função writeRemovedNodeIntoFile: Remove um registro específico do arquivo
  Parâmetros:
  FILE* entrada -> arquivo a ser alterado
  No* n -> nó com informações do registro a ser removido
*/
void writeRemvoedNodeIntoFile(FILE* entrada, No* n) {
  char arr = '@', rem = '*';
  long last = -1;
  fseek(entrada, n->offset, SEEK_SET);
  fwrite(&rem, sizeof(char), 1, entrada);
  fseek(entrada, 4, SEEK_CUR);
  if (n->prox)
    fwrite(&(n->prox->offset), sizeof(long), 1, entrada);
  else
    fwrite(&last, sizeof(long), 1, entrada);

  for (int i = 0; i < n->tamanhoReg - 8; i++) {
    fwrite(&arr, sizeof(char), 1, entrada);
  }
}

/*
  Função writeReg: Escreve um registro no arquivo com os tratamentos necessários
  para valores nulos Parâmetros: FILE* entrada -> arquivo a ser alterado Dados
  dadoLido -> Dados do registro a serem escritos no arquivo int isAtEnd ->
  Indica se registro será escrito no registro no final(1) ou não(0)
*/
void writeReg(FILE* entrada, Dados dadoLido, int isAtEnd) {
  char removido = '-', remRead, tag1 = 'n', tag2 = 'c';
  long noOff = -1;
  fseek(entrada, -1, SEEK_CUR);
  fwrite(&removido, sizeof(char), 1, entrada);
  if (isAtEnd)
    fwrite(&dadoLido.tamanhoRegistro, sizeof(int), 1, entrada);
  else
    fseek(entrada, 4, SEEK_CUR);  // tamanho do registro não é alterado caso ele
                                  // não esteja no fim do arquivo
  fwrite(&noOff, sizeof(long), 1, entrada);
  fwrite(&dadoLido.idServidor, sizeof(int), 1, entrada);
  fwrite(&dadoLido.salarioServidor, sizeof(long), 1, entrada);

  // tratamento de telefone nulo
  if (strcmp(dadoLido.telefoneServidor, "") == 0 ||
      strcmp(dadoLido.telefoneServidor, "              ") == 0) {
    char telNul[14] = "\0@@@@@@@@@@@@@";
    fwrite(telNul, sizeof(char) * 14, 1, entrada);
  } else {
    fwrite(dadoLido.telefoneServidor, sizeof(char) * 14, 1, entrada);
  }
  // Nome e cargo só são escritos caso forem não nulos
  if (dadoLido.tamNomeServidor) {
    fwrite(&dadoLido.tamNomeServidor, sizeof(int), 1, entrada);
    fwrite(&tag1, sizeof(char), 1, entrada);
    fwrite(dadoLido.nomeServidor, sizeof(char) * dadoLido.tamNomeServidor - 1,
           1, entrada);
  }
  if (dadoLido.tamCargoServidor) {
    fwrite(&dadoLido.tamCargoServidor, sizeof(int), 1, entrada);
    fwrite(&tag2, sizeof(char), 1, entrada);
    fwrite(dadoLido.cargoServidor, sizeof(char) * dadoLido.tamCargoServidor - 1,
           1, entrada);
  }
}

/*
  Função updateEncadeamento: Atualiza os campos de encadeamento lista dos
  registros removidos Parâmetros: FILE* entrada -> arquivo a ser alterado Lista*
  l -> lista dos registros removidos
*/
void updateEncadeamento(FILE* entrada, Lista* l) {
  long noOff = -1;
  if (l->ini) {
    No* aux = l->ini;
    while (aux->prox) {
      fseek(entrada, aux->offset + 5, SEEK_SET);
      fwrite(&aux->prox->offset, sizeof(long), 1, entrada);
      aux = aux->prox;
    }
    // atualiza o último registro com -1 para offset
    fseek(entrada, aux->offset + 5, SEEK_SET);
    fwrite(&noOff, sizeof(long), 1, entrada);
  }
  fseek(entrada, 1, SEEK_SET);
  fwrite(&l->ini->offset, sizeof(long), 1, entrada);
}

/*
  Função insertOnRemoved: Insere os registros passados em registros que já foram
  removidos Parâmetros: FILE* entrada -> arquivo a ser alterado Dados*
  dadosLidos -> vetor com todos os registros lidos int n -> número de registros
  no vetor
*/
void insertOnRemoved(FILE* entrada, Dados* dadosLidos, int n) {
  Lista* l = criaLista();
  readFirstNode(entrada, l);
  No* aux = l->ini;
  int size;
  char removido = '-', remRead, tag1 = 'n', tag2 = 'c';
  long noOff = -1;
  double nulSal = -1;
  int hasFound = 0;
  //----------------Cálculo do registro passado----------------------------------------
  for (int i = 0; i < n; i++) {
    dadosLidos[i].tamanhoRegistro = 34;
    if (strcmp(dadosLidos[i].nomeServidor, "") != 0) {
      dadosLidos[i].tamNomeServidor = strlen(dadosLidos[i].nomeServidor) + 2;
      dadosLidos[i].tamanhoRegistro += dadosLidos[i].tamNomeServidor + 4;
    } else {
      dadosLidos[i].tamNomeServidor = 0;
    }

    if (strcmp(dadosLidos[i].cargoServidor, "") != 0) {
      dadosLidos[i].tamCargoServidor = strlen(dadosLidos[i].cargoServidor) + 2;
      dadosLidos[i].tamanhoRegistro += dadosLidos[i].tamCargoServidor + 4;
    } else {
      dadosLidos[i].tamCargoServidor = 0;
    }
  }
  //---------------------------------------------------------------------------------------
  int i = 0;
  if (l->tam) {
    long biggestSize;
    while (aux) {
      biggestSize = aux->tamanhoReg;
      aux = aux->prox;
    }
    aux = l->ini;
    while (aux && i < n) {
      hasFound = 0;
      // Caso o registro seja maior que o maior registro removido, ele deve ser
      // inserido no final do arquivo
      if (dadosLidos[i].tamanhoRegistro > biggestSize) {
        fseek(entrada, 1, SEEK_END);
        writeReg(entrada, dadosLidos[i], 1);
      } else {
        fseek(entrada, aux->offset, SEEK_SET);
        fread(&remRead, sizeof(char), 1, entrada);
        // Inserção só será feita se o registro está de fato removido e se o
        // tamanho for suficiente
        if (remRead == '*' &&
            dadosLidos[i].tamanhoRegistro + 5 <= aux->tamanhoReg + 5) {
          writeReg(entrada, dadosLidos[i], 0);
          removeNode(l, aux);
          aux = l->ini;
          hasFound = 1;
          i++;
        }
      }
      if (!hasFound) aux = aux->prox;
    }
  } else {  // Caso não haja lista de encadeamento, todos os registros serão inseridos no final do arquivo
    for (i = 0; i < n; i++) {
      fseek(entrada, 1, SEEK_END);
      writeReg(entrada, dadosLidos[i], 1);
    }
  }
  fseek(entrada, 1, SEEK_SET);
  if (l->ini)
    fwrite(&l->ini->offset, sizeof(long), 1, entrada);
  else
    fwrite(&noOff, sizeof(long), 1, entrada);
  // atualização do encadeamento lista
  if (l->ini) {
    aux = l->ini;
    while (aux->prox) {
      aux = aux->prox;
    }
    fseek(entrada, aux->offset + 5, SEEK_SET);
    fwrite(&noOff, sizeof(long), 1, entrada);
  }

  destroiLista(l);
}

/*
  Função updateReg: Atualiza, insere em removido ou insere no final do arquivo
  um registro de acordo com o campo Parâmetros: FILE* entrada -> arquivo a ser
  alterado Lista* l-> Lista de registros removidos Dados *d -> Registro a ser
  alterado char* valAtualiza -> Novo valor do campo char campoAtualiza ->
  indicador de qual campo atualizar long offset -> byte offset do registro
  encontrado
*/
void updateReg(FILE* entrada, Lista* l, Dados* d, char* valAtualiza,
               char campoAtualiza, long offset) {
  // Offset antigo é guardado para evitar erro de leitura de futuros registros
  long oldOffset = ftell(entrada);
  int newTam = d->tamanhoRegistro, oldTam = d->tamanhoRegistro;
  char tagN = 'n', tagC = 'c', arr = '@';
  
  if (d->nomeServidor == NULL) d->tamNomeServidor = 0;
  if (d->cargoServidor == NULL) d->tamCargoServidor = 0;
  int biggestSize;
  No* aux = l->ini;
  // Busca do maior tamanho da lista
  while (aux) {
    biggestSize = aux->tamanhoReg;
    aux = aux->prox;
  }
  switch (campoAtualiza) {
    case 'i':  // Atualização do registro
      d->idServidor = atoi(valAtualiza);
      fseek(entrada, offset + 1, SEEK_SET);
      writeReg(entrada, *d, 0);
      break;
    case 's':  // Atualização do salário
      d->salarioServidor = atof(valAtualiza);
      fseek(entrada, offset + 1, SEEK_SET);
      writeReg(entrada, *d, 0);
      break;
    case 't':  // Atualização do telefone
      strcpy(d->telefoneServidor, valAtualiza);
      fseek(entrada, offset + 1, SEEK_SET);
      writeReg(entrada, *d, 0);
      break;
    case 'n':  // Atualização do nome
      // Calculo do tamanho do novo possível registro
      newTam -= d->tamNomeServidor;
      newTam += strlen(valAtualiza) + 2;
      if (d->tamNomeServidor == 0) {
        newTam += 4;
      } else {
        free(d->nomeServidor);
      }
      // Caso o novo valor caiba no campo antigo
      if (strlen(valAtualiza) + 2 <= d->tamNomeServidor) {
        d->nomeServidor = calloc(strlen(valAtualiza), sizeof(char));
        strcpy(d->nomeServidor, valAtualiza);
        fseek(entrada, offset + 1, SEEK_SET);
        // Registro inteiro é completado com @ para tratamento de lixo
        for (int i = 0; i < d->tamanhoRegistro; i++) {
          fwrite(&arr, sizeof(char), 1, entrada);
        }
        fseek(entrada, offset + 1, SEEK_SET);
        writeReg(entrada, *d, 0);
      } else {
        // Caso novo valor não caiba, o registro será removido
        No* temp = criaNo(oldTam, offset);
        // registro é apagado
        writeRemvoedNodeIntoFile(entrada, temp);
        // inserção na lista para então corrigir encadeamento
        insereLista(l, temp);
        // atualização de valores
        d->nomeServidor = calloc(strlen(valAtualiza), sizeof(char));
        strcpy(d->nomeServidor, valAtualiza);
        d->tamNomeServidor = strlen(valAtualiza) + 2;
        if (newTam > biggestSize) {  // caso o registro seja maior que o maior
                                     // registro removido
          d->tamanhoRegistro = newTam;
          fseek(entrada, 1, SEEK_END);
          // inserção no final do arquivo
          writeReg(entrada, *d, 1);
          // tamanho do registro é corrigido com valor antigo para previnir
          // erros no cálculo do offset
          d->tamanhoRegistro = oldTam;
        } else {
          // Busca pel nó que abrigará o novo registro
          aux = l->ini;
          while (aux && newTam > aux->tamanhoReg) {
            aux = aux->prox;
          }
          fseek(entrada, aux->offset + 1, SEEK_SET);
          removeNode(l, aux);
          writeReg(entrada, *d, 0);
        }
      }
      break;
    case 'c':  // Atualização do cargo
      // A mesma lógica de alteração do nome é aplicada para o cargo já que
      // ambos são registros de tamanho variável
      newTam = 34 + strlen(valAtualiza)+2 + d->tamNomeServidor;
      if (d->tamCargoServidor == 0) {
        newTam += 4;
      } else {
        free(d->cargoServidor);
      }
      if(d->tamNomeServidor && d->tamCargoServidor)
        newTam+=8;
      else if(d->tamNomeServidor)
        newTam+=4;
      
      // caso campo caiba no campo do registo
      if (strlen(valAtualiza) + 2 <= d->tamCargoServidor) {
        d->cargoServidor = calloc(strlen(valAtualiza), sizeof(char));
        strcpy(d->cargoServidor, valAtualiza);
        fseek(entrada, offset + 1, SEEK_SET);
        for (int i = 0; i < d->tamanhoRegistro; i++) {
          fwrite(&arr, sizeof(char), 1, entrada);
        }
        fseek(entrada, offset + 1, SEEK_SET);
        writeReg(entrada, *d, 0);
      } else {
        No* temp = criaNo(oldTam, offset);
        writeRemvoedNodeIntoFile(entrada, temp);
        insereLista(l, temp);
        d->cargoServidor = calloc(strlen(valAtualiza), sizeof(char));
        strcpy(d->cargoServidor, valAtualiza);
        d->tamCargoServidor = strlen(valAtualiza) + 2;
        if (newTam > biggestSize) {  // Caso registro seja inserido no final do arquivo
          d->tamanhoRegistro = newTam;
          fseek(entrada, 1, SEEK_END);
          writeReg(entrada, *d, 1);
          d->tamanhoRegistro = oldTam;
        } else {
          // Caso registro seja inserido em um registro removido
          aux = l->ini;
          while (aux && newTam > aux->tamanhoReg) {
            aux = aux->prox;
          }
          fseek(entrada, aux->offset + 1, SEEK_SET);
          removeNode(l, aux);
          writeReg(entrada, *d, 0);
        }
      }
      break;
  }
  // Retorno do ponteiro para o início do próximo registro
  fseek(entrada, oldOffset, SEEK_SET);
}

/*
  Função findRegToUpdate: Busca registro de acordo com o campo de busca e valor
  de busca para então alterar o valor do campo desejado de acordo com o campo de
  atualização e valor de atualização Parâmetros: FILE* entrada -> arquivo a ser
  alterado char campoBusca -> o campo utilizado para busca char* valBusca -> o
  valor a ser buscado char campoAtualiza -> campo que será atualizado char*
  valAtualiza -> valor que será utilizado na atualização
*/
void findRegToUpdate(FILE* entrada, Lista* l, char campoBusca, char* valBusca,
                     char campoAtualiza, char* valAtualiza) {
  Dados* d;
  int nPags = 1, nRegs = 0;
  long nBytes = 0, offset;
  char tag1='n', tag2='c';
  // Id do último servidor atualizado, usado para evitar duplas atualizações
  int lastIdWritten;
  // Pula a página de disco de cabeçalho
  fseek(entrada, 32000, SEEK_SET);
  offset = 32000;
  //----------------------------BUSCA PELO
  // IDSERVIDOR--------------------------------------
  if (campoBusca == 'i') {
    d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (d->idServidor == atoi(valBusca) && d->removido == '-' &&
          lastIdWritten != d->idServidor) {
        updateReg(entrada, l, d, valAtualiza, campoAtualiza, offset);
        lastIdWritten = d->idServidor;
        break;
      }
      // offset atualizado com tamanho + 5 bytes (sizeof(char removido) +
      // sizeof(int tamanho registro))
      offset += d->tamanhoRegistro + 5;
      // correção do ponteiro do aqruivo
      if (ftell(entrada) != offset) fseek(entrada, offset, SEEK_SET);
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    //---------------------------BUSCA PELO
    // NOMESERVIDOR------------------------------------------
  } else if (campoBusca == 'n') {
    d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (d->nomeServidor) {
        if (strcmp(d->nomeServidor, valBusca) == 0 && d->removido == '-' &&
            lastIdWritten != d->idServidor) {
          updateReg(entrada, l, d, valAtualiza, campoAtualiza, offset);
          lastIdWritten = d->idServidor;
        }
      } else {
        // busca pelo valor nulo
        if (strcmp(valBusca, "") == 0 && d->removido == '-' &&
            lastIdWritten != d->idServidor) {
          updateReg(entrada, l, d, valAtualiza, campoAtualiza, offset);
          lastIdWritten = d->idServidor;
        }
      }
      offset += d->tamanhoRegistro + 5;
      if (ftell(entrada) != offset) fseek(entrada, offset, SEEK_SET);
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    //----------------------------BUSCA PELO
    // CARGOSERVIDOR--------------------------------------------
  } else if (campoBusca == 'c') {
    d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (d->cargoServidor) {
        if (strcmp(d->cargoServidor, valBusca) == 0 && d->removido == '-' &&
            lastIdWritten != d->idServidor) {
          updateReg(entrada, l, d, valAtualiza, campoAtualiza, offset);
          lastIdWritten = d->idServidor;
        }
      } else {  // busca por valor nulo
        if (strcmp(valBusca, "") == 0 && d->removido == '-' &&
            lastIdWritten != d->idServidor) {
          updateReg(entrada, l, d, valAtualiza, campoAtualiza, offset);
          lastIdWritten = d->idServidor;
        }
      }
      offset += d->tamanhoRegistro + 5;
      if (ftell(entrada) != offset) fseek(entrada, offset, SEEK_SET);
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    //-------------------------------BUSCA PELO
    // TELEFONESERVIDOR-----------------------------------------------
  } else if (campoBusca == 't') {
    d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (strcmp(d->telefoneServidor, valBusca) == 0 && d->removido == '-' &&
          lastIdWritten != d->idServidor) {
        updateReg(entrada, l, d, valAtualiza, campoAtualiza, offset);
        lastIdWritten = d->idServidor;

      } else if (strcmp(d->telefoneServidor, "              ") == 0 &&
                 strcmp(valBusca, "") == 0 && d->removido == '-' &&
                 lastIdWritten != d->idServidor) {  // busca por valor nulo
        updateReg(entrada, l, d, valAtualiza, campoAtualiza, offset);
        lastIdWritten = d->idServidor;
      }
      offset += d->tamanhoRegistro + 5;
      if (ftell(entrada) != offset) fseek(entrada, offset, SEEK_SET);
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    //------------------------------BUSCA PELO
    // SALARIOSERVIDOR------------------------------------------------------
  } else if (campoBusca == 's') {
    d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    while (d) {
      if (d->salarioServidor == atof(valBusca) && d->removido == '-' &&
          lastIdWritten != d->idServidor) {
        updateReg(entrada, l, d, valAtualiza, campoAtualiza, offset);
        lastIdWritten = d->idServidor;

      } else if ((d->salarioServidor == -1 || d->salarioServidor == 0) &&
                 strcmp(valBusca, "") == 0 && d->removido == '-' &&
                 lastIdWritten != d->idServidor) {  // busca por valor nulo
        updateReg(entrada, l, d, valAtualiza, campoAtualiza, offset);
        lastIdWritten = d->idServidor;
      }
      offset += d->tamanhoRegistro + 5;
      if (ftell(entrada) != offset) fseek(entrada, offset, SEEK_SET);
      destroiDados(d);
      d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
  }
}

Dados* getAllReg(FILE* entrada, int* totalREgs){
    int nPags=1, nRegs=0;
    long nBytes=0;
    char tag1='n', tag2='c';
    fseek(entrada, 32000, SEEK_SET);
    Dados *res = calloc(1, sizeof(Dados));
    Dados* d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    int i=0;
    while(d){
        if(d->removido=='-'){
            res[i] = *d;
            i++;
            res = realloc(res, i*sizeof(Dados));
        }
        destroiDados(d);    
        d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
    }
    *totalREgs = nRegs;
    return res;    
}