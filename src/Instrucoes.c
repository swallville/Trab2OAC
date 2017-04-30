#include "Instrucoes.h"
#include <stdio.h>
#include <stdlib.h>
#include "funcoesMemory.h"
#include <stdint.h>
#include "SimpleOperation.h"
#include <string.h>
#include <strings.h>

/*Pula para o endereco contido no registrador rs */
void jr(uint32_t *pc,uint32_t reg1){
	*pc = reg1;
}
/*Salva o atual PC no registrador $ra e salta para o endereco da constante*/
void jal(uint32_t kte,uint32_t* pc){
	ra = *pc;
	*pc = kte<<2;
}
/*Pula para o endereco contido na constante*/
void j(uint32_t *pc,uint32_t kte){
	kte= kte<<2;
	*pc = kte;
}
/*Realiza a soma de um registrdor com a constante*/
int32_t addi(int32_t reg,int16_t kte){
	int32_t buffer;
	buffer = reg + kte;
	return buffer;
}
/*Realiza a soma aritmetica sem overflow*/
uint32_t addiu(int32_t reg,int16_t kte){
	uint32_t buffer;
	buffer = reg + kte;
	return buffer;
}
/*Compara se dois numeros sao diferente, se sim salta para o novo endereco contido na constante*/
uint32_t bne(uint32_t reg1,uint32_t reg2,uint16_t kte,uint32_t*pc){
	if(reg1 != reg2){
		kte = kte<<2;
		*pc = *pc + kte;
		return *pc;
	}else{
		return *pc;
	}
}
/*Compara se dois numeros sao iguais, se sim salta para o novo endereco contido na constante*/
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
/*Compara se o registrador eh maior que zero, se sim salta para o novo endereco contido na constante*/
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
/*Compara se o registrador eh menor que zero, se sim salta para o novo endereco contido na constante*/
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
/*Soma*/
int32_t add(int32_t reg1,int32_t reg2){
	return (reg1+reg2);
}
/*Subtracao*/
int32_t sub(int32_t reg1,int32_t reg2){
	return (reg1-reg2);
}
/*OU*/
int32_t or(int32_t reg1,int32_t reg2){
	return (reg1 | reg2);
}
/*OR imediate*/
int32_t ori(int32_t reg1,uint16_t kte){
	return (reg1 | kte);
}
/*AND*/
int32_t and(int32_t reg1,int32_t reg2){
	return (reg1 & reg2);
}
/*AND imadiate*/
int32_t andi(int32_t reg1,uint16_t kte){
	return (reg1 & kte);
}
/*XOR*/
int32_t xor(int32_t reg1,int32_t reg2){
	return (reg1 ^ reg2);
}
/*XOR imediate*/
int32_t xori(int32_t reg1,uint16_t kte){
	return (reg1 ^ kte);
}
/*NOR*/
int32_t nor(int32_t reg1,int32_t reg2){
	return (~(reg1|reg2));
}
/*Deslocamento a esquerda*/
int32_t sll(int32_t reg1,uint8_t desloc){
	return (reg1<<desloc);
}
/*Deslocamento a direita aritmetica*/
int32_t sra(int32_t reg1,uint8_t desloc){
	return (reg1>>desloc);
}
/*Deslocamento a direita*/
int32_t srl(int32_t reg1,uint8_t desloc){
	return (reg1>>desloc);
}
/*1 se o registrador 1 eh menor que o registrador 2*/
int32_t slt(int32_t reg1,int32_t reg2){
	if (reg1 < reg2){
		return 1;
	}else{
		return 0;
	}
}
/*Compara se eh menor que a constante*/
int32_t slti(int32_t reg1,int16_t kte){
	if (reg1 < kte){
		return 1;
	}else{
		return 0;
	}
}
/*Compara com a constante sem sinal*/
int32_t sltiu(int32_t reg1,uint16_t kte){
		if (reg1 < kte){
				return 1;
			}else{
				return 0;
			}
}
/*Load byte sem sinal*/
uint8_t  lbu(uint32_t adress, uint16_t kte){
	uint8_t buffer;
	buffer = lb(adress,kte16);
	return buffer;
}
/*Load half word sem sinal*/
uint16_t lhu(uint32_t adress , uint16_t kte){
	uint16_t buffer;
	buffer =lh(adress,kte16);
	return buffer;
}
/*Load uper imediate*/
uint32_t lui(uint16_t kte){
	uint32_t reg1 = kte;
	reg1 = reg1<<16;
	return reg1;
}
/*Multiplicacao - Maior Hi menor Lo(64bits)*/
void mult(int64_t reg1,int64_t reg2){
	uint64_t buffer,aux;
	buffer = reg1*reg2;
	aux = buffer>>32;
	aux = aux & 0x00000000FFFFFFFF;
	hi = aux;
	aux = buffer & 0x00000000FFFFFFFF;
	lo = aux;
}
/*Divisao*/
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
/*Syscall - Imprimr determinado argumento no console */
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
/*Imprime a String contida na memoria*/
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
