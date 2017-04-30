#include <stdio.h>
#include <stdlib.h>
#include "funcoesMemory.h"
#include <stdint.h>
#include <string.h>
#include <strings.h>

int8_t opcode, rs, rt, rd, shamt, funct;
uint32_t pc;
uint32_t ri,kte26;
uint16_t kte16;
int32_t registers[32]; 
int flag;

/*Codigo das funcao possiveis para opcode*/
enum OPCODES {  
       EXT=0x00,	LW=0x23,	LB=0x20,	LBU=0x24,
       LH=0x21,		LHU=0x25,	LUI=0x0F,	SW=0x2B,
       SB=0x28,		SH=0x29,	BEQ=0x04,	BNE=0x05,
       BLEZ=0x06,	BGTZ=0x07,	ADDI=0x08,	SLTI=0x0A,
       SLTIU=0x0B,	ANDI=0x0C,	ORI=0x0D,	XORI=0x0E,
       J=0x02,		JAL=0x03,     ADDIU=0x09
};   
/*Sabendo que as funcoes com opcode 00 obdecem as funcoes R e algumas de salto, enumera-se tambem e as opcoes de instrucoes que utilizam o FUNCT*/ 		
enum FUNCT {
       ADD=0x20,	SUB=0x22,	MULT=0x18,	DIV=0x1A,	AND=0x24,
       OR=0x25,		XOR=0x26,	NOR=0x27,	SLT=0x2A,	JR=0x08,
       SLL=0x00,	SRL=0x02,	SRA=0x03,	SYSCALL=0x0c,	MFHI=0x10, MFLO=0x12 
};

/*Funcao run - Roda o programa enquanto nao ha nenhum syscall(10) e nem ter chegado ate o final da memoria de programa */
void run();

/*Funcao runStep - Mesma funcionalidade porem o usuario pode executar o programa passo a passo*/
void runStep();

/*Funcao Step- A partir do pc =0x0 executa as instrucoes chamando as funcoes fetch->decode->execute */
void step();

/*Chama as funcoes fetch->decode->execute como a funcao step, porem imprime o conteudo dos registradores e do programa passo a passo*/
void stepStep();

/*Fetch recebe o endereco de pc(contador de programa) incrementa-o com 4(proxima instrucao) e coloca o codigo da instrucao no registrador Ri*/
void fetch(uint32_t*);

/*Decodifica a instrucao selecionando os campos que ela possa conter, sendo esse: opcode,kte16,kte26,func, rs,rt,rd,shamt entre outros*/
void decode();

/*A funcao execute, pega o opcode identificado na funcao decode e seleciona que funcao aquele opcode representa, sendo esse 00 vai para o verificacao 
das instrucoes do tipo R */
void execute();

/*Instrucoes selecionaveis do tipo R*/
void tipoR();


