#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verificaArgumentos(int argc, char *argv[], char *arqE, char *arqD){

	if (argc < 5){
		return 10;
	} else if (strcmp(argv[1], "-l") == 0 && strcmp(argv[3], "-o") == 0){
		strcpy(arqE, argv[2]);
		strcpy(arqD, argv[4]);
	} else if (strcmp(argv[1], "-o") == 0 && strcmp(argv[3], "-l") == 0){
		strcpy(arqE, argv[4]);
		strcpy(arqD, argv[2]);
	} else {
		return 20;
	} // else

	return 0;
} // verificaArgumentos

void imprimeErro(int erro, char *arqC){

	switch(erro){
		case 10:
			fprintf(stderr, "Argumentos insuficientes\n");
			break;
		case 20:
			fprintf(stderr, "Argumentos não reconhecidos\n");
			break;
		case 31:
			fprintf(stderr, "Erro ao abrir o arquivo %s.\n", arqC);
			break;
		case 32:
			fprintf(stderr, "Arquivo %s não existe!\n", arqC);
			break;
		case 33:
			fprintf(stderr, "Erro ao abrir o arquivo %s.\n", arqC);
			break;
		default:
			fprintf(stderr, "Resultado não definido\n");
			break;
	} // switch

	return;
} // imprimeErro

int copiaArquivos(char *arqE, char *arqD, char *arqC){

	char c;
	char arqF[100];

	FILE *f1;
	FILE *f2;
	FILE *fc;

	f1 = fopen(arqE, "r");
	if (f1 == NULL){
        strcpy(arqC,arqE);
        return 31;
    }

	f2 = fopen(arqD, "w");
	if (f2 == NULL){
        strcpy(arqC,arqD);
        return 32;
    }

    while (fscanf(f1, "%s", arqF) != EOF){
    	fc = fopen(arqF, "r");
    	if (fc == NULL){
        	strcpy(arqC,arqF);
        	return 33;
    	} else{
			c = '\b';
			fprintf(f2, "%c", c);
			while (fscanf(fc, "%c", &c) != EOF){
				fprintf(f2, "%c", c);
    		}
    	}
    	fclose(fc);
    }
	
    fclose(f1);
    fclose(f2);

	return 0;
} // copiaArquivos

int main(int argc, char * argv[]){
	
	int erro = 0; // variável para a mensagem de erro
	char arqE[100]; // variável para o arquivo a ser copiado
	char arqD[100]; // variável para o arquivo de destino
	char arqC[100];

	if ((erro = verificaArgumentos(argc, argv, arqE, arqD)) != 0){
		imprimeErro(erro, arqC);
	} else {
		erro = copiaArquivos(arqE, arqD, arqC);
		if (erro != 0){
			imprimeErro(erro, arqC);
		}
	}
	return 0;
}
