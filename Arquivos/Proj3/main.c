#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
#include "escreverTela2.h"
#include "merge_sort.h"

//Daniel Sá Barretto Prado Garcia
//nº 10374344
int main(int argc, char const *argv[]){
    
    int op;
    scanf("%d", &op);
    char *fileName, *nomeSaida, *file2Name;
    FILE *fEntrada,*fEntrada2, *fSaida;
    Pagina* temp;
    int n;
    int totalEntrada = 0, totalEntrada2 = 0;
    switch (op){
        case 1:
        //Funcionalidade 1
            fileName = malloc(sizeof(char)*40);
            fscanf(stdin, "%s", fileName);
            Pagina* p = criaPagina();
            if ((fEntrada = fopen(fileName, "r")) == NULL){
                printf("Falha no carregamento do arquivo.\n");
                free(p->conteudo);
                free(p);
                free(fileName);
                exit(0);
            }
            if(checkStatus(fEntrada)==0){
                free(fileName);
                fclose(fEntrada);
                free(p);
                exit(0);
            }
            fSaida = escreveBin(fEntrada, p);
            changeStatus(fEntrada, '0');
            if(fSaida){
                changeStatus(fSaida, '1');
                fclose(fSaida);
                printf("arquivoTrab1.bin");
            }
            if(fEntrada){
                changeStatus(fEntrada, '1');
                fclose(fEntrada);
            }
            destroiPag(p);
            free(fileName);
            break;
        case 2:
        //Funcionalidade 2
            fileName = calloc(40, sizeof(char));
            fscanf(stdin, "%s", fileName);
            if((fEntrada = fopen(fileName, "rb"))==NULL){
                printf("Falha no processamento do arquivo.\n");
                free(fileName);
                exit(0);
            }
            if(checkStatus(fEntrada)==0){
                free(fileName);
                fclose(fEntrada);
                exit(0);
            }
            changeStatus(fEntrada, '0');
            printRegs(fEntrada);
            changeStatus(fEntrada,'1');
            fclose(fEntrada);
            free(fileName);
            break;
        case 3:
        //Funcionalidade 3
            fileName = calloc(40, sizeof(char));
            char campo[40];
            char* val = calloc(100, sizeof(char));
            scanf("%s %s %[^\n]",fileName, campo, val);
            //Remove caracter \r
            for(int i=0; i<strlen(val) + 1; i++){
                if(val[i]=='\r'){
                    val[i] = '\0';
                }
            }
            if ((fEntrada = fopen(fileName, "rb")) == NULL) {
                printf("Falha no processamento do arquivo.\n");
                free(val);
                free(fileName);
                exit(0);
            }
            if(checkStatus(fEntrada)==0){
                free(fileName);
                free(val);
                fclose(fEntrada);
                exit(0);
            }
            changeStatus(fEntrada, '0');
            searchRegs(fEntrada, campo, val);
            changeStatus(fEntrada, '1');
            free(fileName);
            free(val);
            fclose(fEntrada);
            break;

            case 4:
            //Funcionalidade 
                fileName = calloc(40, sizeof(char));
                scanf("%s %d",fileName, &n);
                if ((fEntrada = fopen(fileName, "r+b")) == NULL) {
                    printf("Falha no processamento do arquivo.\n");
                    free(fileName);
                    exit(0);
                }
                //checa status do arquivo
                if(checkStatus(fEntrada)==0){
                    free(fileName);
                    fclose(fEntrada);
                    exit(0);
                }
                changeStatus(fEntrada, '0');
                char nomeCampo[40];
                char* valCampo = calloc(100, sizeof(char*));
                char tagCampo='a';
                Lista *l3 = criaLista();
                readFirstNode(fEntrada, l3);
                for(int i=0; i<n; i++){
                    scanf("%s", nomeCampo);
                    tagCampo = nomeCampo[0];
                    scan_quote_string(valCampo);
                    findRegToRemove(fEntrada, tagCampo, valCampo, l3);
                }
                //Remoção dos registros dados pela lista
                writeRemovedIntoFile(fEntrada, l3);
                changeStatus(fEntrada, '1');
                binarioNaTela1(fEntrada);
                fclose(fEntrada);
                destroiLista(l3);
                free(valCampo);
                free(fileName);
            break;

            case 5:
            //funcionalidade 5
                fileName = calloc(40, sizeof(char));
                scanf("%s %d",fileName, &n);
                if ((fEntrada = fopen(fileName, "r+b")) == NULL) {
                    printf("Falha no processamento do arquivo.\n");
                    free(fileName);
                    exit(0);
                }
                if(checkStatus(fEntrada)==0){
                    free(fileName);
                    fclose(fEntrada);
                    exit(0);
                }
                changeStatus(fEntrada, '0');
                Dados *dadosLidos = calloc(n, sizeof(Dados));
                char *salario = calloc(10, sizeof(char));
                //leitura de todos os novos registros
                for(int i=0; i<n; i++){
                    dadosLidos[i].cargoServidor = calloc(50, sizeof(char));
                    dadosLidos[i].nomeServidor = calloc(50, sizeof(char));
                    scanf("%d", &(dadosLidos[i].idServidor));
                    scanf("%s", salario);
                    if(strcmp(salario, "NULO")==0){
                        dadosLidos[i].salarioServidor = -1;
                    }else{
                        dadosLidos[i].salarioServidor = atof(salario);
                    }
                    scan_quote_string(dadosLidos[i].telefoneServidor);
                    scan_quote_string(dadosLidos[i].nomeServidor);
                    scan_quote_string(dadosLidos[i].cargoServidor);
                }
                
                //inserção
                insertOnRemoved(fEntrada, dadosLidos, n);
                for(int i=0;i<n;i++){
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
            //funcionalidade 6
                fileName = calloc(40, sizeof(char));
                scanf("%s %d",fileName, &n);
                if ((fEntrada = fopen(fileName, "r+b")) == NULL) {
                    printf("Falha no processamento do arquivo.\n");
                    free(fileName);
                    exit(0);
                }
                if(checkStatus(fEntrada)==0){
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
                Lista *l6 = criaLista();
                readFirstNode(fEntrada, l6);
                for(int i=0; i<n; i++){
                    valsAtualiza = calloc(200, sizeof(char));
                    valsBusca = calloc(200, sizeof(char));
                    scanf("%ms", &camposBusca);
                    tagsCampoBusca[i] = camposBusca[0];
                    scan_quote_string(valsBusca);
                    scanf("%ms", &camposAtualiza);
                    tagsCampoAtualiza[i] = camposAtualiza[0];
                    scan_quote_string(valsAtualiza);
                    findRegToUpdate(fEntrada, l6, tagsCampoBusca[i], valsBusca, tagsCampoAtualiza[i], valsAtualiza);
                    free(camposAtualiza);
                    free(camposBusca);
                    free(valsAtualiza);
                    free(valsBusca);
                }
                //Atualização do encadeamento no arquivo
                updateEncadeamento(fEntrada, l6);
                destroiLista(l6);
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
              if((fEntrada = fopen(fileName, "rb"))==NULL){
                free(fileName);
                printf("Falha no carregamento do arquivo.\n");
                exit(0);
              }
              if(checkStatus(fEntrada)==0){
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
              int total=0;
              Dados *res = getAllReg(fEntrada, &total);
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
              for(int i=0; i<total; i++){
                  if(res[i].nomeServidor) free(res[i].nomeServidor);
                  if(res[i].cargoServidor) free(res[i].cargoServidor);
              }
              free(res);
              free(nomeSaida);

              break;
            case 8:
                fileName = calloc(40, sizeof(char));
                char *file2Name = calloc(40, sizeof(char));
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
                
                if(checkStatus(fEntrada)==0 || checkStatus(fEntrada2)==0){
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
                if(fEntrada)
                    fclose(fEntrada);
                if(fEntrada2)
                    fclose(fEntrada2);
                if(fSaida)
                    fclose(fSaida);

                binarioNaTela2(nomeSaida);
                
                free(file2Name);
                free(fileName);
                free(nomeSaida);
                break;
            case 9:
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


    }

    return 0;
}
