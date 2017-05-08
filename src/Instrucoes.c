#include "Instrucoes.h"
#include <stdio.h>
#include <stdlib.h>
#include "funcoesMemory.h"
#include <stdint.h>
#include "SimpleOperation.h"
#include <string.h>
#include <strings.h>

/*Pula para o endereco contido no registrador rs 
*@param uint32_t *pc - PC atual
*		uint32_t reg1 - registrador rs*/
void jr(uint32_t *pc,uint32_t reg1){
	*pc = reg1;
}
/*Salva o atual PC no registrador $ra e salta para o endereco da constante
*@param uint32_t kte - endereco do jump
*		uint32_t *pc - PC atual
*@return void*/
void jal(uint32_t kte,uint32_t* pc){
	ra = *pc;
	*pc = kte<<2;
}
/*Pula para o endereco contido na constante
*@param uint32_t *pc - PC atual
*		uint32_t kte - endereco do jump
*@return void*/
void j(uint32_t *pc,uint32_t kte){
	kte= kte<<2;
	*pc = kte;
}
/*Realiza a soma de um registrdor com a constante
*@param int32_t reg - registrador rt
*		int16_t kte - imediato a ser somado (levando em conta o sinal)
*@return int32_t buffer - buffer onde sera salvo o valor do resultado da soma*/
int32_t addi(int32_t reg,int16_t kte){
	int32_t buffer;
	buffer = reg + kte;
	return buffer;
}
/*Realiza a soma aritmetica sem overflow
*@param int32_t reg - registrador rt
*		int16_t kte - imediato a ser somado (sem levar em conta o sinal)
*@return uint32_t buffer - buffer onde sera salvo o valor do resultad da soma
*/
uint32_t addiu(int32_t reg,int16_t kte){
	uint32_t buffer;
	buffer = reg + kte;
	return buffer;
}
/*Compara se dois numeros sao diferente, se sim salta para o novo endereco contido na constante
*@param uint32_t reg1 - registrador rt
*		uint32_t reg2 - registrador rd
*		uint16_t kte - valor da posicao do label
*		uint32_t *pc - PC atual
*@return uint32_t *pc - PC para jump apos realizado a funcao*/
uint32_t bne(uint32_t reg1,uint32_t reg2,uint16_t kte,uint32_t*pc){
	if(reg1 != reg2){
		kte = kte<<2;
		*pc = *pc + kte;
		return *pc;
	}else{
		return *pc;
	}
}
/*Compara se dois numeros sao iguais, se sim salta para o novo endereco contido na constante
*@param uint32_t reg1 - registrador rt
*		uint32_t reg2 - registrador rd
*		uint16_t kte - valor da posicao do label
*		uint32_t *pc - PC atual
*@return uint32_t *pc - PC para jump apos realizado a funcao*/
uint32_t beq(uint32_t reg1,uint32_t reg2,uint16_t kte,uint32_t*pc){
	int32_t ktebuffer;
		if (reg1 == reg2){
			ktebuffer = kte<<2;
			*pc = *pc + ktebuffer;
			return *pc;
		}else{
			return *pc;
		}
}
/*Compara se o registrador eh maior que zero, se sim salta para o novo endereco contido na constante
*@param	uint32_t reg1 - registrador rt
*		uint16_t kte - valor da posicao do label
*		uint32_t *pc - PC atual
*@return uint32_t *pc - PC para jump apos realizado a funcao*/
uint32_t bgez(int32_t reg1 ,int16_t kte,uint32_t*pc){
	int32_t ktebuffer;
		if (reg1 >= 0){
			ktebuffer = kte<<2;
			*pc = *pc + ktebuffer;
			return *pc;
		}else{
			return *pc;
		}
}
/*Compara se o registrador eh menor que zero, se sim salta para o novo endereco contido na constante
*@param uint32_t reg2 - registrador rt
*		uint16_t kte - valor da posicao do label
*		uint32_t *pc - PC atual
*@return uint32_t *pc - PC para jump apos realizado a funcao*/
uint32_t blez(int32_t reg1 ,int16_t kte,uint32_t*pc){
	int32_t ktebuffer;
		if (reg1 <= 0){
			ktebuffer = kte<<2;
			*pc = *pc + ktebuffer;
			return *pc;
		}else{
			return *pc;
		}
}
/*Soma
*@param int32_t reg1 - registrador rs
*		int32_t reg2 - registrador rt
*@return int32_t - soma dos registradores*/
int32_t add(int32_t reg1,int32_t reg2){
	return (reg1+reg2);
}
/*Subtracao
*@param int32_t reg1 - registrador rs
*		int32_t reg2 - registrador rt
*@return int32_t - subtracao dos registradores*/
int32_t sub(int32_t reg1,int32_t reg2){
	return (reg1-reg2);
}
/*OU
*@param int32_t reg1 - registrador rs
*		int32_t reg2 - registrador rt
*@return int32_t - resultado OU logico dos registradores*/
int32_t or(int32_t reg1,int32_t reg2){
	return (reg1 | reg2);
}
/*OR imediate
*@param int32_t reg1 - registrador rt
*		int16_t kte - imediato
*@return int32_t - resultado OU logico dos registradores*/
int32_t ori(int32_t reg1,uint16_t kte){
	return (reg1 | kte);
}
/*AND
*@param int32_t reg1 - registrador rs
*		int32_t reg2 - registrador rt
*@return int32_t - resultado AND logico dos registradores*/
int32_t and(int32_t reg1,int32_t reg2){
	return (reg1 & reg2);
}
/*AND imadiate
*@param int32_t reg1 - registrador rt
*		int16_t kte - imediato
*@return int32_t - resultado AND logico dos registradores*/
int32_t andi(int32_t reg1,uint16_t kte){
	return (reg1 & kte);
}
/*XOR
*@param int32_t reg1 - registrador rs
*		int32_t reg2 - registrador rt
*@return int32_t - resultado XOR logico dos registradores*/
int32_t xor(int32_t reg1,int32_t reg2){
	return (reg1 ^ reg2);
}
/*XOR imediate
*@param int32_t reg1 - registrador rt
*		int16_t kte - imediato
*@return int32_t - resultado XOR logico dos registradores*/
int32_t xori(int32_t reg1,uint16_t kte){
	return (reg1 ^ kte);
}
/*NOR
*@param int32_t reg1 - registrador rs
*		int32_t reg2 - registrador rt
*@return int32_t - resultado NOR logico dos registradores*/
int32_t nor(int32_t reg1,int32_t reg2){
	return (~(reg1|reg2));
}
/*Deslocamento a esquerda
*@param int32_t reg1 - registrador rt
*		int8_t desloc - quantidade de deslocamento
*@return int32_t -  valor deslocado do registrador*/
int32_t sll(int32_t reg1,uint8_t desloc){
	return (reg1<<desloc);
}
/*Deslocamento a direita aritmetica
*@param int32_t reg1 - registrador rs
*		int8_t desloc - quantidade a ser deslocado
*@return int32_t - valor deslocado do registrador*/
int32_t sra(int32_t reg1,uint8_t desloc){
	return (reg1>>desloc);
}
/*Deslocamento a direita
*@param int32_t reg1 - registrador rs
*		int8_t desloc - quantidade a ser deslocado
*@return int32_t - valor deslocado do registrador*/
int32_t srl(int32_t reg1,uint8_t desloc){
	return (reg1>>desloc);
}
/*1 se o registrador 1 eh menor que o registrador 2
*@param int32_t reg1 - registrador rs
*		int32_t reg2 - registrador rt*/
int32_t slt(int32_t reg1,int32_t reg2){
	if (reg1 < reg2){
		return 1;
	}else{
		return 0;
	}
}
/*Compara se eh menor que a constante
*@param int32_t reg1 - registrador rt
*		int16_t kte - imediato (levando em conta o sinal)*/
int32_t slti(int32_t reg1,int16_t kte){
	if (reg1 < kte){
		return 1;
	}else{
		return 0;
	}
}
/*Compara com a constante sem sinal
*@param int32_t reg1 - registrador rt
*		int16_t kte - imediato (nao levando em conta o sinal)*/
int32_t sltiu(int32_t reg1,uint16_t kte){
		if (reg1 < kte){
				return 1;
			}else{
				return 0;
			}
}
/*Load byte sem sinal
*@param int32_t reg1 - registrador rt
*		int16_t kte - imediato (nao levando em conta o sinal)
*@return uint8_t buffe - byte lido do registrador*/
uint8_t  lbu(uint32_t adress, uint16_t kte){
	uint8_t buffer;
	buffer = lb(adress,kte16);
	return buffer;
}
/*Load half word sem sinal
*@param int32_t reg1 - registrador rt
*		int16_t kte - imediato (nao levando em conta o sinal)
*@return uint8_t buffe - halfword lido do registrador*/
uint16_t lhu(uint32_t adress , uint16_t kte){
	uint16_t buffer;
	buffer =lh(adress,kte16);
	return buffer;
}
/*Load uper imediate
*@param uint16_t kte - imediato a ser lido
*@return uint32_t reg1 - registrador rd*/
uint32_t lui(uint16_t kte){
	uint32_t reg1 = kte;
	reg1 = reg1<<16;
	return reg1;
}
/*Multiplicacao - Maior Hi menor Lo(64bits)
*@param int64_t reg1 - registrador rs
*		int64_t reg2 - registrador rt
*@return void*/
void mult(int64_t reg1,int64_t reg2){
	uint64_t buffer,aux;
	buffer = reg1*reg2;
	aux = buffer>>32;
	aux = aux & 0x00000000FFFFFFFF;
	hi = aux;
	aux = buffer & 0x00000000FFFFFFFF;
	lo = aux;
}
/*Divisao
*@param int32_t reg1 - registrador rs
*		int32_t reg2 - registrador rt
*@return void*/
void divi(int32_t reg1,int32_t reg2){
	lo = reg1 / reg2;
	hi = reg1 % reg2;
}
/*Retorna HI*/
int32_t mfhi(){
	return hi;
}
/*Retorna Lo*/
int32_t mflo(){
	return lo;
}
/*Syscall - Imprimr determinado argumento no console
*@see lwStr, LoadInt*/
void syscall(){
	switch(v0){
			case STR:
				lwStr();
			break;
			case INTE:
				LoadInt();
			break;
			case ENC:
				flag =0;
			break;
			default:
			printf("Syscall nao Implementado\n");
			break;
	}
}
/*Imprime a String contida na memoria
*@see lb*/
void lwStr(){
	int i =0;
	uint32_t adress = 0x00000000;
	char c,string[100];
	uint8_t buffer;
		do{
			buffer = lb(a0,adress);
			c = (char)buffer;
				if (c != '\0'){
					string[i] = c;
					adress = adress + 0x00000001;
					i++;
				} else{
					string[i] ='\0';
				}
		}while(c != '\0');
	printf("%s",string);
}
/*Imprime um inteiro contido em a0*/
void LoadInt(){
	printf("%d",a0);
}
