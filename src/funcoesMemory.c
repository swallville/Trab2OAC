/*Biblioteca de funcoes - Funcao*/
#include <stdio.h>
#include <stdlib.h>
#include "funcoesMemory.h"
#include <stdint.h>
#include <string.h>
#include <strings.h>
extern uint32_t pc;
extern int32_t hi,lo;
/*-----------------------------Load Func-----------------------------*/
/*Funcao load word realiza as seguintes operacoes: soma ao endereco(adress) a
constante(kte) para obter o verdadeiro endereco( com offset ) chama a funcao
FindAdressData que retorna em qual byte da memoria(enderecada em bytes) eh
indicada pelo endereco, com isso apenas retorna a celula da memoria que
determinada por esse byte*/
int32_t lw(uint32_t address, uint16_t kte){
	uint32_t adressToLoad;
	adressToLoad = address + kte;
	adressToLoad = FindAdressData(adressToLoad);
	return memory[adressToLoad][0];
}

/*A Funcao load byte opera de forma semelhante a load word, mas com uma pequena
diferenca: achamos o endereco(com offset) da mesma maneira e esse
endereco(endereco(em byte) que contem o byte que queremos) e chamaos a funcao
FindAdressByte que retorna em qual byte daquela palavra contem o que estamos
procurando. Com isso selecionamos o byte, com uma mascara e ocorre um
deslocamento dependendo da posicao para alinhar o byte na posicao menos
significativa. Por ultimo passamos para um registrador de 8bits*/
int8_t  lb(uint32_t address, uint16_t kte) {
	uint32_t adressToLoad;
	uint32_t dado;
	uint8_t Databyte;
	int adressToLoadAux,adressToLoadByte;

	adressToLoad = address + kte;
	adressToLoadAux = FindAdressData(adressToLoad);
	adressToLoadByte = FindAdressByte(adressToLoad);

		switch(adressToLoadByte){
			case 0:
			dado = memory[adressToLoadAux][0];
			dado = dado & 0x000000FF;
			Databyte = dado;
			return Databyte;
			break;

			case 1:
			dado = memory[adressToLoadAux][0];
			dado = dado & 0x0000FF00;
			dado = dado>>8;
			Databyte = dado;
			return Databyte;

			break;

			case 2:
			dado = memory[adressToLoadAux][0];
			dado = dado & 0x00FF0000;
			dado = dado>>16;
			Databyte = dado;
			return Databyte;
			break;

			case 3:
			dado = memory[adressToLoadAux][0];
			dado = dado & 0xFF000000;
			dado = dado>>24;
			Databyte = dado;
			return Databyte;
			break;
		}
	return -1;
}
/*A funcao load word realiza a mesma operacao da load byte com uma diferenca os
enderecos sao disponiveis no byte 0 e 2, logo podemos utilizar o mesmo metodo da
load byte apenas limitando o endereco que sera retornado pela funcao FindAdressByte.
Utilizamos um mascara e passamos para um registrador de 16bits*/
int16_t lh(uint32_t address, uint16_t kte) {
	uint32_t adressToLoad,data;
	uint16_t newData;
	int adressToLoadAux,adressToLoadHWord;
	adressToLoad = address + kte;

	adressToLoadAux = FindAdressData(adressToLoad);
	adressToLoadHWord = FindAdressByte(adressToLoad);

		switch(adressToLoadHWord){
			case 0:
			data = memory[adressToLoadAux][0];
			data = data & 0x0000FFFF;
		 	newData = data;
		 	return newData;
			break;

			case 2:
			data = memory[adressToLoadAux][0];
			data = data & 0xFFFF0000;
		 	data = data>>16;
			newData = data;
		 	return newData;
			break;
		}
		return -1;
}
/*-----------------------------Store Func-----------------------------*/
/*A funcao store word grava uma palavra na memoria, para isso obtem o endereco
real da palavra(com offset(kte)), com a funcao FindAdressData retorna o byte
referente a palavra e aloca aquele dado na posicao */
void sw(uint32_t address, uint16_t kte, int32_t dado) {
	uint32_t addressToSave;
	addressToSave = address + kte;
	addressToSave = FindAdressData(addressToSave);
	memory[addressToSave][0] = dado;
}
/*A funcao store word realiza as mesma operacoes da funcao loadbyte, acha o
endereco da palavra, depois do byte. Achado o byte correto, devemos aplicar
uma mascara para zera o dado que esatva na memoria abrindo espaco para o o novo
byte, com isso aplicamos a operacao OU/OR que tem a caracterista de repitir o
valor da entrada, logo alocamos o byte*/
void sb(uint32_t address, uint16_t kte, int8_t dado) {
	uint32_t adressToSave,oldData,newData;
	int adressToSaveAux,adressToSaveByte;
	adressToSave = address + kte;
	adressToSaveAux = FindAdressData(adressToSave);
	adressToSaveByte = FindAdressByte(adressToSave);

		switch(adressToSaveByte){
			case 0:
			oldData = memory[adressToSaveAux][0];
			oldData = oldData & 0xFFFFFF00;
			newData = dado & 0x000000FF;
			newData = oldData|newData;
			memory[adressToSaveAux][0] = newData;
			break;

			case 1:
			oldData = memory[adressToSaveAux][0];
			oldData = oldData & 0xFFFF00FF;
			newData = dado;
			newData = newData<<8;
			newData = newData & 0x0000FF00;
			newData = oldData|newData;
			memory[adressToSaveAux][0] = newData;
			break;

			case 2:
			oldData = memory[adressToSaveAux][0];
			oldData = oldData & 0xFF00FFFF;
			newData = dado;
			newData = newData<<16;
			newData = newData & 0x00FF0000;
			newData = oldData|newData;
			memory[adressToSaveAux][0] = newData;
			break;

			case 3:
			oldData = memory[adressToSaveAux][0];
			oldData = oldData & 0x00FFFFFF;
			newData = dado;
			newData = newData<<24;
			newData = newData & 0xFF000000;
			newData = oldData|newData;
			memory[adressToSaveAux][0] = newData;
			break;
		}
}
/*A funcao store halfword realiza as mesma operacoes, sabendo que os enderecos possices sao 0 e 2 na palavra aplicamos a mascara e a operacao OR, copiando o dado
para a aquela posicao de memoria com os 16bits alocados*/
void sh(uint32_t address, uint16_t kte, int16_t dado) {
	uint32_t adressToLoad,data;
	uint32_t newData;
	int adressToLoadAux,adressToLoadHWord;
	adressToLoad = address + kte;
	adressToLoadAux = FindAdressData(adressToLoad);
	adressToLoadHWord = FindAdressByte(adressToLoad);

		switch(adressToLoadHWord){
			case 0:
			data = memory[adressToLoadAux][0];

			data = data & 0xFFFF0000;
			newData =dado;
			newData = newData & 0x0000FFFF;
		 	newData = data | newData;
		 	memory[adressToLoadAux][0] = newData;
			break;

			case 2:
			data = memory[adressToLoadAux][0];
			data = data & 0x0000FFFF;
			newData = dado;
			newData = newData<<16;
		 	newData = data|newData;
		 	memory[adressToLoadAux][0] = newData;
			break;
		}
}
/*-----------------------------Memory Started Func-----------------------------*/
/*Inicializa a memoria com todos os elementos em zero*/
void zerarMemory(){
	for (int i = 0; i < MEM_SIZE; ++i){
		memory[i][0] = 0x00000000;
	}
	for (int i = 0; i < 32; ++i){
		registers[i] = 0x00000000;
	}
}
/*endereaca a segunda celula da memoria somente por criteria de visualizacao dos
enderecos*/
void adressMemory(){
	pc = 0x00000000;
	sp = 0x00003ffc;
	uint32_t address = 0x00000000;
		for (int i = 0; i < MEM_SIZE; ++i){
			memory[i][1] = address;
			address = address + 0x00000004;
		}
}
/*Imprimi a memoria em mem.txt*/
void printMemory(){
	FILE * pfile = fopen ("mem.txt", "w");;
	for (int i = 0; i < MEM_SIZE; ++i){
		fprintf(pfile,"|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
		i++;
		fprintf(pfile,"|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
		i++;
		fprintf(pfile,"|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
		i++;
		fprintf(pfile,"|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
		i++;
		fprintf(pfile,"|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
		i++;
		fprintf(pfile,"|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
		i++;
		fprintf(pfile,"|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
		i++;
		fprintf(pfile,"|0x%08x -- 0x%08x | \n",memory[i][1],memory[i][0]);
	 }
	 fclose (pfile);
}
/*Imprimi os registradores em reg.txt*/
void printReg(){
	FILE * pfile = fopen ("reg.txt", "w");

	fprintf(pfile, "\tRegisters\n");
	fprintf(pfile,"$zero=0x%08x\n",registers[0]);
	fprintf(pfile,"$at=0x%08x\n",registers[1]);
	fprintf(pfile,"$v0=0x%08x\n",registers[2]);
	fprintf(pfile,"$v1=0x%08x\n",registers[3]);
	fprintf(pfile,"$a0=0x%08x\n",registers[4]);
	fprintf(pfile,"$a1=0x%08x\n",registers[5]);
	fprintf(pfile,"$a2=0x%08x\n",registers[6]);
	fprintf(pfile,"$a3=0x%08x\n",registers[7]);
	fprintf(pfile,"$t0=0x%08x\n",registers[8]);
	fprintf(pfile,"$t1=0x%08x\n",registers[9]);
	fprintf(pfile,"$t2=0x%08x\n",registers[10]);
	fprintf(pfile,"$t3=0x%08x\n",registers[11]);
	fprintf(pfile,"$t4=0x%08x\n",registers[12]);
	fprintf(pfile,"$t5=0x%08x\n",registers[13]);
	fprintf(pfile,"$t6=0x%08x\n",registers[14]);
	fprintf(pfile,"$t7=0x%08x\n",registers[15]);
	fprintf(pfile,"$s0=0x%08x\n",registers[16]);
	fprintf(pfile,"$s1=0x%08x\n",registers[17]);
	fprintf(pfile,"$s2=0x%08x\n",registers[18]);
	fprintf(pfile,"$s3=0x%08x\n",registers[19]);
	fprintf(pfile,"$s4=0x%08x\n",registers[20]);
	fprintf(pfile,"$s5=0x%08x\n",registers[21]);
	fprintf(pfile,"$s6=0x%08x\n",registers[22]);
	fprintf(pfile,"$s7=0x%08x\n",registers[23]);
	fprintf(pfile,"$t8=0x%08x\n",registers[24]);
	fprintf(pfile,"$t9=0x%08x\n",registers[25]);
	fprintf(pfile,"$k0=0x%08x\n",registers[26]);
	fprintf(pfile,"$k1=0x%08x\n",registers[27]);
	fprintf(pfile,"$gp=0x%08x\n",registers[28]);
	fprintf(pfile,"$sp=0x%08x\n",registers[29]);
	fprintf(pfile,"$fp=0x%08x\n",registers[30]);
	fprintf(pfile,"$ra=0x%08x\n\n",registers[31]);
	fprintf(pfile,"PC=0x%08x\n",pc);
	fprintf(pfile,"HI=0x%08x\n",hi);
	fprintf(pfile,"LO=0x%08x\n",lo);
	fclose (pfile);
}
/*imprime uma determinada faixa da memoria e em um determinado formato*/
void dump_mem(int start, int end, char format){
	switch(format){
		case 'h':
		printf("\tMemory\n");
			for (int i = start; i < end; i++){
				printf("|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|0x%08x -- 0x%08x |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|0x%08x -- 0x%08x | \n",memory[i][1],memory[i][0]);
			}
		break;

		case 'd':
		printf("\tMemory\n");
			for (int i = start; i < end; ++i){
				printf("|%d -- %d |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|%d -- %d |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|%d -- %d |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|%d -- %d |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|%d -- %d |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|%d -- %d |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|%d -- %d |\n",memory[i][1],memory[i][0]);
				i++;
				printf("|%d -- %d| \n",memory[i][1],memory[i][0]);
			}
		break;
	}
 }
 /*Imprimo os registradores em um determinado formato*/
void dump_reg(char op){
	switch(op){
		case 'h':
			printf("\tRegisters\n");
			printf("$zero=0x%08x\n",registers[0]);
			printf("$at=0x%08x\n",registers[1]);
			printf("$v0=0x%08x\n",registers[2]);
			printf("$v1=0x%08x\n",registers[3]);
			printf("$a0=0x%08x\n",registers[4]);
			printf("$a1=0x%08x\n",registers[5]);
			printf("$a2=0x%08x\n",registers[6]);
			printf("$a3=0x%08x\n",registers[7]);
			printf("$t0=0x%08x\n",registers[8]);
			printf("$t1=0x%08x\n",registers[9]);
			printf("$t2=0x%08x\n",registers[10]);
			printf("$t3=0x%08x\n",registers[11]);
			printf("$t4=0x%08x\n",registers[12]);
			printf("$t5=0x%08x\n",registers[13]);
			printf("$t6=0x%08x\n",registers[14]);
			printf("$t7=0x%08x\n",registers[15]);
			printf("$s0=0x%08x\n",registers[16]);
			printf("$s1=0x%08x\n",registers[17]);
			printf("$s2=0x%08x\n",registers[18]);
			printf("$s3=0x%08x\n",registers[19]);
			printf("$s4=0x%08x\n",registers[20]);
			printf("$s5=0x%08x\n",registers[21]);
			printf("$s6=0x%08x\n",registers[22]);
			printf("$s7=0x%08x\n",registers[23]);
			printf("$t8=0x%08x\n",registers[24]);
			printf("$t9=0x%08x\n",registers[25]);
			printf("$k0=0x%08x\n",registers[26]);
			printf("$k1=0x%08x\n",registers[27]);
			printf("$gp=0x%08x\n",registers[28]);
			printf("$sp=0x%08x\n",registers[29]);
			printf("$fp=0x%08x\n",registers[30]);
			printf("$ra=0x%08x\n\n",registers[31]);
			printf("PC=0x%08x\n",pc);
			printf("HI=0x%08x\n",hi);
			printf("LO=0x%08x\n",lo);
		break;
		case 'd':
			printf("\tRegisters\n");
			printf("$zero=%d\n",registers[0]);
			printf("$at=%d\n",registers[1]);
			printf("$v0=%d\n",registers[2]);
			printf("$v1=%d\n",registers[3]);
			printf("$a0=%d\n",registers[4]);
			printf("$a1=%d\n",registers[5]);
			printf("$a2=%d\n",registers[6]);
			printf("$a3=%d\n",registers[7]);
			printf("$t0=%d\n",registers[8]);
			printf("$t1=%d\n",registers[9]);
			printf("$t2=%d\n",registers[10]);
			printf("$t3=%d\n",registers[11]);
			printf("$t4=%d\n",registers[12]);
			printf("$t5=%d\n",registers[13]);
			printf("$t6=%d\n",registers[14]);
			printf("$t7=%d\n",registers[15]);
			printf("$s0=%d\n",registers[16]);
			printf("$s1=%d\n",registers[17]);
			printf("$s2=%d\n",registers[18]);
			printf("$s3=%d\n",registers[19]);
			printf("$s4=%d\n",registers[20]);
			printf("$s5=%d\n",registers[21]);
			printf("$s6=%d\n",registers[22]);
			printf("$s7=%d\n",registers[23]);
			printf("$t8=%d\n",registers[24]);
			printf("$t9=%d\n",registers[25]);
			printf("$k0=%d\n",registers[26]);
			printf("$k1=%d\n",registers[27]);
			printf("$gp=%d\n",registers[28]);
			printf("$sp=%d\n",registers[29]);
			printf("$fp=%d\n",registers[30]);
			printf("$ra=%d\n\n",registers[31]);
			printf("PC=%d\n",pc);
			printf("HI=%d\n",hi);
			printf("LO=%d\n",lo);
		break;
	}
}
/*-----------------------------Auxiliar Func-----------------------------*/
/*Retorna o byte referente ao endereco da memoria. Ao dividir o endereco por 4
temos que a parte inteira representa a localizacao do byte na memoria
( enderecada em byte->4 em 4)*/
int FindAdressData(uint32_t address){
	 int a,result;
	 a =  address;
	 result = a/4;
	 return result;
}
/*O resto da divisao por byte indica em qual byte ele se encontra*/
int FindAdressByte(uint32_t address){
	 int a,result,resultAux;
	 a = address;
	 resultAux = (a%4);
	 return resultAux;
}
