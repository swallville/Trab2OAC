/*Biblioteca da Interface do Programa*/
#include "Instrucoes.h"
#include "SimpleOperation.h"
#include "funcoesMemory.h"
#include "Instrucoes.h"
#include "InputData.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>

/*Define um clear para limpar a tela do terminal */
#ifdef _WIN32
	#define CLEAR "cls"
#else
	#define CLEAR "clear"
#endif


/*Exibi Menu de opcoes*/
int menu();

/*Trata a opcao digitada no terminal pelo usuario*/
void opcao(int);