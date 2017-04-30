#include <stdio.h>
#include <stdlib.h>
#include "funcoesMemory.h"
#include <stdint.h>
#include "SimpleOperation.h"
#include <string.h>
#include <strings.h>
#include "Instrucoes.h"

/*A funcao run chama a funcao step que executa uma instrucao a partir do PC.
 Essa instrucao Run executa ate o final da memoria de programa
ou se o syscall encerrar o programa*/
void run(){
	while( flag != 0 && pc != 0x1000){
		step();
	}
}
/*A funcao run chama a funcao step que executa uma instrucao a partir do PC.
Essa instrucao Run executa ate o final da memoria de programa ou se o syscall
encerrar o programa. Porem com a diferenca de poder ver step-by-step do programa*/
void runStep(){
	while( flag != 0 && pc != 0x1000){
		stepStep();
	}
}
/*Funcao step chama a funcao fetch que seta a instrucao no registrador RI,
depois chama a decode para realizar a decodificacao dos campos da instrucao
e por ultimo executa a instrucao*/
void step(){
	fetch(&pc);
	decode();
	execute();
}
/*Funcao step chama a funcao fetch que seta a instrucao no registrador RI,
depois chama a decode para realizar a decodificacao dos campos da instrucao
e por ultimo executa a instrucao.Porem imprime o conteudo dos registradores
PASSO A PASSO assim como os campos da instrucao*/
void stepStep(){
	printf("\n Next Pc= %08x | opcode: %02x | rs: %02x | rt:%02x | rs:%02x | shamt:%02x | funct:%02x | kte16:%hx | kte26:%08x\n",pc,opcode,rs,rt,rd,shamt,funct,kte16,kte26);
	dump_reg('h');
	printf("PRESSIONE ENTER PARA SEGUIR PARA A PROXIMA INSTRUCAO\n");
	getchar();
	system("clear");
	fetch(&pc);
	decode();
	execute();
}
/*Incrementa pc para a proxima instrucao e carrega o registrador RI com o
conteudo do endereco de PC que aponta para a memoria*/
void fetch(uint32_t* pc){
	ri = lw(*pc,0);
	*pc = *pc + 0x00000004;
}
/*Seleciona os campos de cada tipo de instrucao caso ela seja executada ou nao,
pois so saberemos a instrucao na execute a partir dos campos setados nesta funcao*/
void decode(){
	opcode = ri>>26;
	rs = ri>>21;
	rs &= 0x0000001F;
	rt = ri>>16;
	rt &= 0x0000001F;
	rd = ri>>11;
	rd &= 0x0000001F;
	shamt = ri>>6;
	shamt &= 0x0000001F;
	funct = ri & 0x0000003F;
	kte16 =ri & 0x0000FFFF;//complemento de dois
	kte26 = ri & 0x03FFFFFF;
}
/*A partir dos campos opcode e func, eh definida a instrucao a ser relaizada
e as executa*/
void execute(){
	int i;
	switch(opcode){
		case EXT:
			tipoR();
		break;

		case ADDI:
			registers[rt] =addi(registers[rs],kte16);
		break;

		case LW:
			registers[rt]=lw(registers[rs],kte16);
		break;

		case ADDIU:
			registers[rt] = addiu(registers[rs],kte16);
		break;

		case BEQ:
			pc = beq(registers[rs],registers[rt],kte16,&pc);
		break;

		case J:
			j(&pc,kte26);
		break;

		case LH:
			registers[rt] = lh(registers[rs],kte16);
		break;

		case SB:
			sb(registers[rs],kte16,registers[rt]);
		break;

		case BLEZ:
			pc = blez(registers[rs],kte16,&pc);
		break;

		case SLTIU:
			registers[rt] = sltiu(registers[rs],kte16);
		break;

		case LHU:
			registers[rt] = lhu(registers[rs],kte16);
		break;

		case SH:
			sh(registers[rs],kte16,registers[rt]);
		break;

		case BGTZ:
			pc = bgez(registers[rs],kte16,&pc);
		break;

		case JAL:
			jal(kte26,&pc);
		break;

		case LB:
			registers[rt]=lb(registers[rs],kte16);
		break;

		case LUI:
			registers[rt]=lui(kte16);
		break;

		case ANDI:
			registers[rt] = andi(registers[rs],kte16);
		break;

		case ORI:
			registers[rt] = ori(registers[rs],kte16);
		break;

		case LBU:
			registers[rt]=lbu(registers[rs],kte16);
		break;

		case SW:
			sw(registers[rs],kte16,registers[rt]);
		break;

		case BNE:
			pc = bne(registers[rs],registers[rt],kte16,&pc);
		break;

		case SLTI:
			registers[rt] = slti(registers[rs],kte16);
		break;

		case XORI:
			registers[rt] = xori(registers[rs],kte16);
		break;

	}

}
void tipoR(){
	switch(funct){
			case SYSCALL:
				syscall();
			break;

			case ADD:
				registers[rd] = add(registers[rs],registers[rt]);
			break;

			case OR:
				registers[rd] = or(registers[rs],registers[rt]);
			break;

			case SLL:
				registers[rd] = sll(registers[rt],shamt);
			break;

			case SUB:
				registers[rd] = sub(registers[rs],registers[rt]);
			break;

			case XOR:
				registers[rd] = xor(registers[rs],registers[rt]);
			break;

			case SRL:
				registers[rd] = srl(registers[rt],shamt);
			break;

			case MULT:
				mult(registers[rs],registers[rt]);
			break;

			case NOR:
				registers[rd] = nor(registers[rs],registers[rt]);
			break;

			case SRA:
				registers[rd] = sra(registers[rt],shamt);
			break;

			case DIV:
				divi(registers[rs],registers[rt]);
			break;

			case SLT:
				registers[rd] = slt(registers[rs],registers[rt]);
			break;

			case AND:
				registers[rd] = and(registers[rs],registers[rt]);
			break;

			case JR:
				jr(&pc,registers[rs]);
			break;

			case MFHI:
				registers[rd] = mfhi();
			break;

			case MFLO:
				registers[rd] = mflo();
			break;

	}
}
