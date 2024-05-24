#include <stdio.h>
#include <stdlib.h>

//[linha][coluna], matriz // string termina com \0, então tem que ler o \0
char mapa[5][10+1]; 
int linhas;
int colunas;

int main(int argc, char const *argv[]){

	//mapa[0][0] = '|';
	//mapa[4][9] = '|';

	//printf("%c %c\n", mapa[0][0], mapa[4][9]);

	FILE* arq;
	arq = fopen("mapa.txt", "r");

	if(arq == NULL){
		printf("Erro na leitura do arquivo\n");
		exit(1);
	}

	fscanf(arq, "%d %d", &linhas, &colunas);
	printf("linhas %d colunas %d\n", linhas, colunas);

	///////////
	/*
	char* c = malloc(1); //1 byte
	int* v = malloc(4); // memory allocation, 4 bytes inteiro
	*v = 10;
	printf("Int alloc %d\n", *v);
	free(v); //desaloca
	*/
	//////////////

	int i;
	for(i = 0; i < 5; i++){ //1 dimensao da matriz devolve um array
		fscanf(arq, "%s", mapa[i]); // ler a primeira dimensao so a linha
	}

	for(i = 0; i < 5; i++){
		printf("%s\n", mapa[i]); // ler a primeira dimensao so a linha
	}


	fclose(arq);

	return 0;
}