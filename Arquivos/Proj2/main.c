#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
//Daniel Sá Barretto Prado Garcia
//nº 10374344
int main(int argc, char const *argv[]){
	
	int op;
	scanf("%d", &op);
	char* fileName;
	FILE* fEntrada;
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
			FILE *fSaida = escreveBin(fEntrada, p);

			if(fSaida){
				fclose(fSaida);
				printf("arquivoTrab1.bin");
			}
			if(fEntrada)
				fclose(fEntrada);
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
			printRegs(fEntrada);
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
			searchRegs(fEntrada, campo, val);
			free(fileName);
			free(val);
			fclose(fEntrada);
			break;
			case 4:
				break;   
			case 5:

				break;
			case 6:

				break; 
	}

	return 0;
}
