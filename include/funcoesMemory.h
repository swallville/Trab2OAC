/*Biblioteca de Funcoes */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>

/*Declaracao das variaveis globais usadas em todo o programa: a memoria e os registradores*/
#define MEM_SIZE 4096
/*Utilizamos duas celulas de memoria para ficar mais facil a visualizacao e manipulacao
dos enderecos e dados nas regioes de memoria*/
int32_t memory[MEM_SIZE][2];
int32_t hi,lo;
extern int32_t registers[32];
/*Macros para cada registrador do banco de registradores*/
#define zero registers[0]
#define at registers[1]
#define v0 registers[2]
#define v1 registers[3]
#define a0 registers[4]
#define a1 registers[5]
#define a2 registers[6]
#define a3 registers[7]
#define t0 registers[8]
#define t1 registers[9]
#define t2 registers[10]
#define t3 registers[11]
#define t4 registers[12]
#define t5 registers[13]
#define t6 registers[14]
#define t7 registers[15]
#define s0 registers[16]
#define s1 registers[17]
#define s2 registers[18]
#define s3 registers[19]
#define s4 registers[20]
#define s5 registers[21]
#define s6 registers[22]
#define s7 registers[23]
#define t8 registers[24]
#define t9 registers[25]
#define k0 registers[26]
#define k1 registers[27]
#define gp registers[28]
#define sp registers[29]
#define fp registers[30]
#define ra registers[31]


/*Funcao load word, le uma palavra da memoria e retorna em um registrador*/
int32_t lw(uint32_t , uint16_t );

/*Funcao load byte, le um byte de um endereco de memoria e retorna para um registrador*/
int8_t  lb(uint32_t, uint16_t);

/*Funcao load half-word, le metada de uma palavra(32bits) e retorna para um registrador*/
int16_t lh(uint32_t , uint16_t);

/*Funcao que grava/guarda na memoria uma palavra de 32bits*/
void sw(uint32_t, uint16_t, int32_t);

/*Funcao que grava/salva um byte em um endereco de memoria*/
void sb(uint32_t , uint16_t , int8_t );

/*Funcao que grava/salva metade de uma palavra na memoria*/
void sh(uint32_t, uint16_t, int16_t);

/*Funcao que zera */
void zerarMemory();

/*Cria um endereco em cada celula da memoria, apenas para a visualizacao*/
void adressMemory();

/*Imprimi a memoria em mem.txt*/
void printMemory();

/*Imprimi os registradores em reg.txt*/
void printReg();

/*imprime uma determinada faixa da memoria e em um determinado formato*/
void dump_mem(int,int,char);

/*Imprimo os registradores em um determinado formato*/
void dump_reg(char);

/*Procura o endereco da palavra na memoria*/
int FindAdressData(uint32_t);

/*Procurar o byte na memoria*/
int FindAdressByte(uint32_t );
