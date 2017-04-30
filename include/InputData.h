#include <stdio.h>
#include <stdlib.h>
#include "funcoesMemory.h"
#include <stdint.h>
#include <string.h>
#include <strings.h>

/*DEfine os enderecos de inicio da organizacao da memoria tanto da parte text como da parte data*/
#define sizeText 0x00000000
#define sizeData 0x00002000

/*Carrega a parte text.bin para a memoria do simulador. Pegando palavra por palavra e colocando nos enderecos de palavra com auxilio da funcao fread*/
void LoadPtext(char*);

/*Carrega a parte data.bin para a memoria do simulador. Pegando palavra por palavra e colocando nos enderecos de palavra com auxilio da funcao fread*/
void LoadPdata(char*);