#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMARGS 7 // Número de argumentos

int verificaArgs(int argc, char *argv[], char **file, int *d, char **cp, int *t);
void imprimeErro(int erro, char *arq);
char * carregaCfg(char *file);
int verificaCfg(char *fileCfg, char *file);

int
main(int argc, char *argv[])
{
	int erro = 0; // erro
	int d = 0; // posição ordinal do registro
	int t = 0; // tag para mostrar todos os registros
	char *file = NULL; // nome do arquivo com os registros
	char *cp = NULL; // chave de pesquisa
	char *fileCfg = NULL; // nome do arquivo .cfg

	if((erro = verificaArgs(argc, argv, &file, &d, &cp, &t)) != 0){
		imprimeErro(erro, file);
	} // if

	fileCfg = (char *) malloc(sizeof(char));
	fileCfg = carregaCfg(file);

	if((erro = verificaCfg(fileCfg, file)) != 0){
		imprimeErro(erro, fileCfg);
	} // if

	return 0;
} // main

int 
verificaArgs(int argc, char *argv[], char **file, int *d, char **cp, int *t)
{
	int i = 0;

	if (argc < NUMARGS){
		return 10;
	} // if
		
	for (i = 1; i < argc; i++){
		if (strcmp(argv[i], "-f") == 0){
			*file = (char *) malloc(sizeof(char));
			strcpy(*file, argv[i+1]);
		} else if (strcmp(argv[i], "-d")== 0){
			*d = atoi(argv[i+1]);
		} else if (strcmp(argv[i], "-cp") == 0){
			*cp = (char *) malloc(sizeof(char));
			strcpy(*cp, argv[i+1]);
		} else if (strcmp(argv[i], "-t") == 0){
			*t = 1;
		} // else
	} // for

	if (*file == NULL || *d == 0 || *cp == NULL){
		return 20;
	}

	return 0;
} //verificaArgs

void
imprimeErro(int erro, char *arq)
{
	switch(erro){
		case 10:
			fprintf(stderr, "Argumentos insuficientes.\n");
			break;
		case 20:
			fprintf(stderr, "Argumentos das tags não reconhecidos.\n");
			break;
		case 30:
			fprintf(stderr, "Erro ao abrir o arquivo %s.\n", arq);
			break;
		case 31:
			fprintf(stderr, "Erro ao ler conteúdo do arquivo %s.\n", arq);
			break;
		default:
			fprintf(stderr, "Resultado indefinido.\n");
			break;
	}

	return;
} //imprimeErro

char *
carregaCfg(char *file)
{
	int i = 0; // contador
	char *arq; // variável auxiliar 

	arq = (char *) malloc(sizeof(char));
	strcpy(arq, file);

	for (i = 0;;i++){
		if (arq[i] == '.'){
			arq[i+1] = 'c';
			arq[i+2] = 'f';
			arq[i+3] = 'g';
			break;
		}
	}

	return arq;
} //carregaCfg

int
verificaCfg(char *fileCfg, char *file)
{
	FILE *fp = NULL; 
	
	char *arq; //
	int q; // quantidade de registros
	int rt; // tamanho dos registros

	fp = fopen(fileCfg, "r");
	if (fp == NULL){
		return 30;
	}

	arq = (char *) malloc(sizeof(char));
	fscanf(fp, "%s", arq);

	if (strcmp(file, arq) != 0){
		free(arq);
		return 31;
	}

	fclose(fp);

	return 0;
} //verificaCfg
