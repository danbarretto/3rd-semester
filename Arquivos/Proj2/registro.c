#include "registro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Função criaCabecalho: Preenche os dados de cabeçalho de acordo com os aquivos lidos
    Parâmetros:
    Cabecalho* cab -> estrutura que guarda os dados de cabeçalho
    FILE* entrada -> Arquivo a ser lido
    int arqEhBinario -> operando que decide qual método de leitura será utilizado, sendo 1 para arquivo binário
    e 0 para arquivo de texto
*/
void criaCabecalho(Cabecalho *cab, FILE *entrada, int arqEhBinario) {
    //leitura de arquivo de texto
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
        //leitura até \r
        fscanf(entrada, ",%[^\r\n]", cab->campos[4]);
    } else {
        fread(&cab->status, sizeof(char), 1, entrada);
        fread(&cab->topoLista, sizeof(long), 1, entrada);
        for (int i = 0; i < 5; i++) {
            fread(&cab->tags[i], sizeof(char), 1, entrada);
            fread(cab->campos[i], sizeof(char) * 40, 1, entrada);
        }
    }

    //completa as descrições do campo com @
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
void destroiDados(Dados *d){
    if (d->nomeServidor) free(d->nomeServidor);
    if (d->cargoServidor) free(d->cargoServidor);
    if (d) free(d);
}

/*
    Função escreveCabecalho: Preenche uma página de disco com os dados de cabeçalho e depois a completa com '@'
    Parâmetros:
    Pagina *p-> estrutura de dados que guarda vetor de 32000 bytes, que representa conteúdo da página de disco, e o número de páginas
    FILE* entrada-> arquivo a ser lido
    FILE* saida-> Arquivo com os dados escritos
    Retorno:
    Cabecalho cab -> dados de cabeçalho lidos do arquivo de entrada
*/
Cabecalho escreveCabecalho(Pagina *p, FILE *entrada, FILE *saida) {
    /*Para reduzir o número de acessos à disco, copia-se todos os dados de cabeçalho lidos para um vetor 32000 bytes,
     completa as posições restantes com '@' e grava esse vetor no arquivo de saida
     */
    Cabecalho cab;
    criaCabecalho(&cab, entrada, 0);
    //byteOffset = posição atual do ponteiro
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
    //completa o restante da paágina de disco com '@'
    for (int i = byteOffset; i < 32000; i++) {
        p->conteudo[i] = '@';
    }
    //Escrita do conteúdo no arquivo
    fwrite(p->conteudo, sizeof(char), 32000, saida);
    p->nPags++;
    free(p->conteudo);
    //realocação de memória para os próximos registros
    p->conteudo = calloc(32000, sizeof(char));
    return cab;
}

/*
    Função criaPagina: aloca memória para estrutura Pagina
    Retorno: Ponteiro sobre a memória alocada
*/
Pagina *criaPagina() {
    Pagina *p = calloc(1, sizeof(Pagina));
    p->nPags = 0;
    p->conteudo = calloc(32000, sizeof(char));
    return p;
}
/*
    Função destroiPag: libera memória da estrutura Pagina
    Parâmetro:
    Pagina *p: endereço da memória a ser liberada
*/
void destroiPag(Pagina *p) {
    free(p->conteudo);
    free(p);
}
/*
    Função escreveBin: Lê todos os registros de um arquivo csv e os passa para um arquivo binário
    Parâmetros:
    FILE *fEntrada -> arquivo de entrada a ser lido
    Pagina *p -> estrutura que guarda dados lidos do arquivo
    Retorno:
    FILE *saida -> arquivo com os dados escritos
*/
FILE *escreveBin(FILE *fEntrada, Pagina *p) {
    FILE *saida;
    if ((saida = fopen("arquivoTrab1.bin", "wb")) == NULL) {
        printf("Falha no carregamento do arquivo\n");
        return saida;
    }
    //Escreve a primeira página de disco com o cabeçalho
    Cabecalho c = escreveCabecalho(p, fEntrada, saida);

    int byteOffset = 0;

    //posição do campo tamanhoRegistro do último registro lido
    int lastTamOffset = 0;

    while (1) {
        //Estrutura Dados guarda todos os campos que um registro contém
        Dados *d = calloc(1, sizeof(Dados));
        int nomeOk = 1, cargoOk = 1;
        d->cargoServidor = calloc(1000, sizeof(char));
        d->nomeServidor = calloc(1000, sizeof(char));
        //Caso a leitura do primeiro byte seja EOF, a memoria alocada por Dados *d é liberada
        if (fscanf(fEntrada, "%d,", &(d->idServidor)) == EOF) {
            destroiDados(d);
            break;
        }
        
        if (fscanf(fEntrada, "%lf,", &(d->salarioServidor)) == 0) {
            //Tratamento de dado nulo
            d->salarioServidor = -1;
        }
        if (fscanf(fEntrada, "%[^,]", d->telefoneServidor) == 0) {
            //Tratamento de dado nulo
            d->telefoneServidor[0] = '\0';
            for (int i = 1; i < 14; i++) d->telefoneServidor[i] = '@';
        }
        if (fscanf(fEntrada, ",%[^,]", d->nomeServidor) == 0) {
            //Flag de nome nulo
            nomeOk = 0;
        }
        if (fscanf(fEntrada, ",%[^\r\n]", d->cargoServidor) == 0) {
            //Flag de cargo nulo
            cargoOk = 0;
        }
        //Nos tamanhos dos campos cargoServidor e nomeServido são contabilizados as tags 'n' e 'c' e os caracteres \0
        d->tamCargoServidor = strlen(d->cargoServidor) + 2;
        d->tamNomeServidor = strlen(d->nomeServidor) + 2;
        d->removido = '-';
        d->encadeamentoLista = -1;
        //tamanho de registro calculado (caso nome ou cargo sejam nulos, não serão contabilizados os campos de tamanho, tag e valor)
        d->tamanhoRegistro = sizeof(d->encadeamentoLista) +
                             sizeof(d->idServidor) +
                             sizeof(d->salarioServidor) + sizeof(char) * 14 +
                             nomeOk * (sizeof(d->tamNomeServidor) +
                                       sizeof(char) * d->tamNomeServidor) +
                             cargoOk * (sizeof(d->tamCargoServidor) +
                                        sizeof(char) * d->tamCargoServidor);

        //caso o registro lido não caiba na página de disco, a página atual é completada com '@' e uma nova página é criada
        if (d->tamanhoRegistro + 5 > 32000 - byteOffset) {
            int nArrobas = 0;
            for (int i = byteOffset; i < 32000; i++) {
                p->conteudo[i] = '@';
                nArrobas++;
            }
            int tamFix = 0;
            //tamanho do último registro é copiado
            memcpy(&tamFix, &p->conteudo[lastTamOffset], sizeof(int));
            //tamanho é incrementado com o número de @ inseridos
            tamFix += nArrobas;
            memcpy(p->conteudo + lastTamOffset, &tamFix, sizeof(int));
            //página de disco é gravada no arquivo
            fwrite(p->conteudo, sizeof(char), 32000, saida);
            p->nPags++;
            free(p->conteudo);
            //nova página de disco é criada
            p->conteudo = calloc(32000, sizeof(char));
            byteOffset = 0;
        }
        //---------------Cópia dos dados lidos para o vetor de bytes---------------------------------------------------------
        memcpy(p->conteudo + byteOffset, &d->removido, sizeof(char));
        byteOffset += sizeof(char);

        lastTamOffset = byteOffset;
        memcpy(p->conteudo + byteOffset, &d->tamanhoRegistro, sizeof(int));
        byteOffset += sizeof(int);

        memcpy(p->conteudo + byteOffset, &d->encadeamentoLista,
               sizeof(long int));
        byteOffset += sizeof(long int);

        memcpy(p->conteudo + byteOffset, &d->idServidor, sizeof(int));
        byteOffset += sizeof(int);

        memcpy(p->conteudo + byteOffset, &d->salarioServidor, sizeof(double));
        byteOffset += sizeof(double);

        memcpy(p->conteudo + byteOffset, d->telefoneServidor,
               sizeof(char) * 14);
        byteOffset += sizeof(char) * 14;

        //Dados referentes ao nome são escritos apenas se este não for nulo
        if (nomeOk) {
            memcpy(p->conteudo + byteOffset, &d->tamNomeServidor, sizeof(int));
            byteOffset += sizeof(int);

            memcpy(p->conteudo + byteOffset, &(c.tags[3]), sizeof(char));
            byteOffset += sizeof(char);

            memcpy(p->conteudo + byteOffset, d->nomeServidor,
                   sizeof(char) * d->tamNomeServidor - 1);
            byteOffset += sizeof(char) * d->tamNomeServidor - 1;
        }
        //Dados referentes ao cargo são escritos apenas se este não for nulo
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
void readAts(FILE *entrada) {
    char arroba;
    fread(&arroba, sizeof(char), 1, entrada);
    while (arroba == '@') {
        fread(&arroba, sizeof(char), 1, entrada);
    }
    fseek(entrada, -1, SEEK_CUR);
}

/*
    Função getReg: Lê registros de arquivo binário e os retorna com seus respectivos tratamento de valores nulos
    Parâmetros:
    FILE *entrada -> arquivo lido
    Dados *d -> Estrutura que guarda os dados de todos os campos do registro
    int *nPags -> Endereço no número de páginas de disco acessadas
    int *nRegs -> Endereço do número de registros encontrados
    int *nBytes -> Endereço do número de bytes lidos
    char *tag1 -> Endereço da primeira tag lida
    char *tag2 -> Endereço da segunda tag lida
    int isPrinting -> Determina se o registro encontrado será impresso
*/
Dados *getReg(FILE *entrada, Dados *d, int *nPags, int *nRegs, int *nBytes,
              char *tag1, char *tag2, int isPrinting) {
    if (ferror(entrada)) {
        printf("Falha no carregamento do arquivo.\n");
        return NULL;
    }
    int endOfPage = 0;
    char *salario = calloc(sizeof(double), sizeof(char));
    d = calloc(1, sizeof(Dados));
    fread(&d->removido, sizeof(char), 1, entrada);
    //Caso primeiro campo do registro seja nulo, retorna nulo simbolizando o fim do arquivo
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
        //incrementa o número de bytes lidos com o tamanho do registro + tamanho do byte de removido + o tamanho do int de tamanho de registro
        *nBytes += d->tamanhoRegistro + 5;
    }
    //Página de disco lida por completo
    if (*nBytes == 32000) {
        *nBytes = 0;
        (*nPags)++;
        endOfPage = 1;
    }

    fread(&d->encadeamentoLista, sizeof(long), 1, entrada);
    fread(&d->idServidor, sizeof(int), 1, entrada);
    fread(&d->salarioServidor, sizeof(double), 1, entrada);

    //Copia o valor do salário para uma string para facilitar tratamento de nulo
    sprintf(salario, "%.2lf", d->salarioServidor);
    if (d->salarioServidor == -1) strcpy(salario, "        ");

    fread(d->telefoneServidor, sizeof(char) * 14, 1, entrada);
    //Tratamento de nulo
    if (strcmp(d->telefoneServidor, "") == 0)
        strcpy(d->telefoneServidor, "              ");

    fread(&d->tamNomeServidor, sizeof(int), 1, entrada);
    fread(tag1, sizeof(char), 1, entrada);
    if (d->tamNomeServidor && *tag1 == 'n') {
    //Caso o nome seja não nulo
        d->nomeServidor = calloc(d->tamNomeServidor, sizeof(char));
        fread(d->nomeServidor, sizeof(char) * d->tamNomeServidor - 1, 1,
              entrada);
    } else if (d->tamNomeServidor && *tag1 == 'c') {
    //Caso nome seja nulo e cargo seja não nulo
        d->cargoServidor = calloc(d->tamNomeServidor, sizeof(char));
        fread(d->cargoServidor, sizeof(char) * d->tamNomeServidor - 1, 1,
              entrada);
        if (isPrinting)
            printf("%d %s %s %d %s\n", d->idServidor, salario,
                   d->telefoneServidor, d->tamNomeServidor - 2,
                   d->cargoServidor);
        free(salario);
        if (endOfPage) {
            //Posiciona arquivo no último @
            readAts(entrada);
        }
        //retorna Dados com nome nulo
        return d;
    } else {
    //Caso nome e cargo sejam nulos
        //retorna ponteiro para antes da tag e do indicador de tamanho
        fseek(entrada, -5, SEEK_CUR);
        if (endOfPage) {
            readAts(entrada);
        }
        fread(&d->tamCargoServidor, sizeof(int), 1, entrada);
        fread(&tag2, sizeof(char), 1, entrada);
        if (*tag2 != 'c') {
            fseek(entrada, -5, SEEK_CUR);
            if (isPrinting)
                printf("%d %s %s\n", d->idServidor, salario,
                       d->telefoneServidor);
        }
        free(salario);
        //Retorna Dados com nome e cargo nulos
        return d;
    }

    fread(&d->tamCargoServidor, sizeof(int), 1, entrada);
    fread(tag2, sizeof(char), 1, entrada);
    if (*tag2 == 'c') {
        //Caso nome e cargo sejam não nulos
        d->cargoServidor = calloc(d->tamCargoServidor, sizeof(char));
        fread(d->cargoServidor, sizeof(char) * d->tamCargoServidor - 1, 1,
              entrada);
        if (isPrinting)
            printf("%d %s %s %d %s %d %s\n", d->idServidor, salario,
                   d->telefoneServidor, d->tamNomeServidor - 2, d->nomeServidor,
                   d->tamCargoServidor - 2, d->cargoServidor);
        free(salario);
        if (endOfPage) {
            readAts(entrada);
        }
        //Retorna Dados com cargo e nome não nulos
        return d;
    } else {
        //Caso nome seja não nulo e cargo seja nulo
        if (isPrinting)
            printf("%d %s %s %d %s\n", d->idServidor, salario,
                   d->telefoneServidor, d->tamNomeServidor - 2,
                   d->nomeServidor);
        //retorna ponteiro para posição antes da ultima tag e indicador de tamanho
        fseek(entrada, -5, SEEK_CUR);
        free(salario);
        if (endOfPage) {
            readAts(entrada);
        }
        //Retorna Dados com nome não nulo e cargo nulo
        return d;
    }
}
/*
    Função printRegs: imprime todos os registros de um arquivo binário dado
    Parâmetros:
    FILE *entrada -> arquivo lido
*/
void printRegs(FILE *entrada) {
    char status;
    fread(&status, sizeof(char), 1, entrada);
    //Caso status do arquivo seja 0, programa é terminado com mensagem de erro
    if(status=='0'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    //Posiciona ponteiro após paǵina de disco dedicada ao cabeçalho
    fseek(entrada, 32000, SEEK_SET);
    char tag1 = 0, tag2 = 0;
    int nRegs = 0, nBytes = 0, nPags = 1;
    //-------------------Leitura e impressão dos registros---------------------------
    Dados *d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 1);
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
    Função searchRegs: Procura registro em um arquivo binário e o imprime de acordo com campo passado e valor do campo
    Parâmetros:
    FILE *entrada -> arquivo lido
    char *campo -> qual campo será usado para a busca
    char *val -> valor a ser buscado
*/
void searchRegs(FILE *entrada, char *campo, char *val) {
    Cabecalho cab;
    //Recupera as informações de cabeçalho
    criaCabecalho(&cab, entrada, 1);
    if(cab.status=='0'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    
    //posiciona ponteiro no após primeira página de disco
    readAts(entrada);
    int nRegs = 0, nBytes = 0, nPags = 1, regsFound = 0;
    char tag1, tag2;

    if (strcmp(campo, "idServidor") == 0) {
        //Caso campo seja o id do servidor
        int id = atoi(val);
        //Leitura do primeiro registro
        Dados *d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
        while (d) {
            if (d->idServidor == id) {
                regsFound++;
                //----------Impressão dos dados com seus tratamentos para valores nulos----------
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
                //Como id é único, basta achar a primeira ocorrência
                break;
                //---------------------------------------------------------------------------------
            }
            destroiDados(d);
            //lê o próximo registro
            d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
        }
        if (!regsFound) {
            printf("Registro inexistente.\n");
        }
    } else if (strcmp(campo, "salarioServidor") == 0) {
        //Caso o campo seja o salário do servidor
        double salario = atof(val);
        Dados *d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
        while (d) {
            if (d->salarioServidor == salario) {
                regsFound++;
                //----------Impressão dos dados com seus tratamentos para valores nulos----------
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
        //Caso o campo seja o telefone do servidor
        char tel[14];
        strcpy(tel, val);
        Dados *d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
        while (d) {
            if (strcmp(d->telefoneServidor, tel) == 0) {
                regsFound++;
                //----------Impressão dos dados com seus tratamentos para valores nulos----------
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
        //Caso o campo seja nome do servidor
        char nome[500];
        strcpy(nome, val);
        Dados *d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
        while (d) {
            if (d->nomeServidor) {
                if (strcmp(d->nomeServidor, nome) == 0) {
                    regsFound++;
                    //----------Impressão dos dados com seus tratamentos para valores nulos----------
                    printf("%s: %d\n", cab.campos[0], d->idServidor);
                    if (d->salarioServidor == -1)
                        printf("%s: valor nao declarado\n", cab.campos[1]);
                    else
                        printf("%s: %.2lf\n", cab.campos[1],
                               d->salarioServidor);
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
        //Caso o campo seja o cargo do servidor
        char cargo[500];
        strcpy(cargo, val);
        Dados *d = getReg(entrada, d, &nPags, &nRegs, &nBytes, &tag1, &tag2, 0);
        while (d) {
            if (d->cargoServidor) {
                if (strcmp(d->cargoServidor, cargo) == 0) {
                    regsFound++;
                    //----------Impressão dos dados com seus tratamentos para valores nulos----------
                    printf("%s: %d\n", cab.campos[0], d->idServidor);
                    if (d->salarioServidor == -1)
                        printf("%s: valor nao declarado\n", cab.campos[1]);
                    else
                        printf("%s: %.2lf\n", cab.campos[1],
                               d->salarioServidor);
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
        //Caso campo seja outro valor
        printf("Registro inexistente.\n");
    }
    if (nPags && regsFound) {
        //Última página de disco acessada
        nPags++;
        printf("Número de páginas de disco acessadas: %d\n", nPags);
    }
}