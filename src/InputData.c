#include <stdio.h>
#include <stdlib.h>
#include "funcoesMemory.h"
#include <stdint.h>
#include "InputData.h"
#include <string.h>
#include <strings.h>

extern int32_t registers[32];

/*Abre o aquivo, verifica se foi aberto com sucesso e em seguida ler ate
o fim do arquivo, uma word por vez com a funcao fread e coloca na memoria
a partir do endereco inical do .text (0x00000000)*/
void LoadPtext(char *nomeArq){
	FILE * txt = fopen(nomeArq,"r");
	int32_t buffer;
	int adress = sizeText;
		if (txt == NULL){
			printf("O Arquivo nao abriu\n");
		}else{
			while(!feof(txt)){
				fread(&buffer, sizeof(int32_t),1, txt);
				memory[adress][0] = buffer;
			adress++;
			}
			printf("Arquivo .text Carregado com Sucesso...\n");
		}
	fclose(txt);
}

/*Abre o arquivo e o verifca, le o arquivo ate o final e com auxilio da funcao
fread le uma word por vez do arquivo e guarda a parti do endereco
determinado para o .data*/
void LoadPdata(char *nomeArq){
	int32_t buffer;
	FILE * txt = fopen(nomeArq,"r");
		if (txt == NULL){
			printf("O Arquivo nao abriu\n");
		}else{
			int adress = sizeData/4;
			while(!feof(txt)){
				fread(&buffer, sizeof(int32_t),1, txt);
				memory[adress][0] = buffer;
				adress++;
			}
			printf("Arquivo .data Carregado com Sucesso...\n\n");
		}
	fclose(txt);
}
