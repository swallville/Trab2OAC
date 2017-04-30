#include <stdio.h>
#include <stdlib.h>
#include "funcoesMemory.h"
#include <stdint.h>
#include <string.h>
#include <strings.h>

extern uint32_t pc;
/*Macros para opcao do syscall*/
#define STR 0x00000004
#define INTE 0x00000001
#define ENC 0x0000000a

/*Load byte unsigned*/
uint8_t  lbu(uint32_t, uint16_t);

/*Load Half word unsigned*/
uint16_t lhu(uint32_t , uint16_t);

/*load uper imediate*/
uint32_t lui(uint16_t);

/*Add imediate*/
int32_t addi(int32_t ,int16_t);

/*Add imediate unsigned*/
uint32_t addiu(int32_t ,int16_t);

/*Salta se for menor que zero*/
uint32_t blez(int32_t ,int16_t ,uint32_t*);

/*Set on less than imediate*/
int32_t slti(int32_t,int16_t);

/*Set on less than imediate unsigned*/
int32_t sltiu(int32_t,uint16_t);

/*Imprime no console */
void syscall();

/*Funcao para imprimr String*/
void lwStr();

/*funcao para Imprimr*/
void LoadInt();

/*Adicao*/
int32_t add(int32_t,int32_t);

/*Subtracao*/
int32_t sub(int32_t,int32_t);

/*Operador Ou bit-bit*/
int32_t or(int32_t,int32_t);

/*Operador AND bit-bit*/
int32_t and(int32_t,int32_t);

/*Operador XOR bit-bit*/
int32_t xor(int32_t,int32_t);

/*Operador NOR bit-bit*/
int32_t nor(int32_t,int32_t);

/*Operador OR imediate bit-bit*/
int32_t ori(int32_t ,uint16_t);

/*Operador AND imeditate bit-bit*/
int32_t andi(int32_t ,uint16_t);

/*Operador XOR imediate bit-bit*/
int32_t xori(int32_t ,uint16_t);

/*Shif Left Logic*/
int32_t sll(int32_t,uint8_t);

/*Shift Right Aritmetic*/
int32_t sra(int32_t,uint8_t);

/*Shift Right Logic*/
int32_t srl(int32_t,uint8_t);

/*Set on less than*/
int32_t slt(int32_t,int32_t);

/*Salta se igual*/
uint32_t beq(uint32_t ,uint32_t ,uint16_t ,uint32_t*);

/*Salte se for maior que zero*/
uint32_t bgez(int32_t ,int16_t ,uint32_t*);

/*Salta se for diferente*/
uint32_t bne(uint32_t ,uint32_t ,uint16_t ,uint32_t*);

/*Jump Register*/
void jr(uint32_t *,uint32_t);

/*Jump*/
void j(uint32_t*,uint32_t);

/*Jump and Link*/
void jal(uint32_t,uint32_t*);

/*Multiplicao*/
void mult(int64_t,int64_t);

/*Divisao*/
void divi(int32_t,int32_t);

/*Move to hi*/
int32_t mfhi();

/*Move to lo*/
int32_t mflo();

