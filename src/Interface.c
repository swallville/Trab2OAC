#include "Interface.h"
#include <stdint.h>

extern int flag;
/*exibi o menu e pega a opcao*/
int menu(){
	int op;

		printf("Simulador Arquitetura MIPS\n");
		printf("Menu de Operacoes Simulador\n");
		printf("[1]step:\n\tExecutar Instrucao a Instrucao do programa\n");
		printf("[2]run:\n\tExecutar programa(Sem parada)\n");
		printf("[3]dump_mem:\n\tImprimir Regiao da Memoria(Enderecos em Hexadecimal)\n");
		printf("[4]dum_reg:\n\tImprimir Registradores\n");
		printf("[5]Informacoes sobre o Simulador\n");
		printf("[6]Encerrar\n");
		printf("\n");
		printf("Opcao: \n");
		scanf("%d",&op);

	return op;
}

/*Trata cada opcao, com a operacao deseja*/
void opcao(int op){
	int opcao;
	uint32_t adressBg,adressEnd;
	char text[20],data[20];
		switch(op){
			case 1:
				flag = 1;
				pc = 0x00000000;
				system("clear");
				runStep();
				printf("Programa Executado\n");
				printf("\nPresione ENTER para retornar ao menu\n");
				getchar();
				system("clear");
			break;
			case 2:
				flag = 1;
				pc = 0x00000000;
				system("clear");
				printf("Programa Executado com sucesso\n\n");
				run();
				printf("\n\nPresione ENTER para retornar ao menu\n");
				getchar();
				getchar();
				system("clear");
			break;
			case 3:
				printf("Digite o endereco inicial(Hexadecimal):\n");
				scanf("%x",&adressBg);
				adressBg = adressBg/4;
				printf("Digite o endereco final(Hexadecimal):\n");
				scanf("%x",&adressEnd);
				adressEnd = adressEnd/4;
				printf("Escolha a base numerica:\n");
				printf("[1]Decimal\n");
				printf("[2]Hexadecimal\n");
				printf("Opcao: ");
				scanf("%d",&opcao);
					switch(opcao){
						case 1:
						dump_mem(adressBg,adressEnd,'d');
						break;
						case 2:
						dump_mem(adressBg,adressEnd,'h');
						break;
						default:
						printf("Erro - Nenhum Opcao Selecionada\n");
						break;
					}
				printf("Presione ENTER para retornar ao menu\n");
				getchar();
				getchar();
				system("clear");
			break;
			case 4:
				printf("Escolha a base numerica:\n");
				printf("[1]Decimal\n");
				printf("[2]Hexadecimal\n");
				printf("Opcao: ");
				scanf("%d",&opcao);
					switch(opcao){
						case 1:
						dump_reg('d');
						break;
						case 2:
						dump_reg('h');
						break;
						default:
						printf("Erro - Nenhum Opcao Selecionada\n");
						break;
					}
				printf("Presione ENTER para retornar ao menu\n");
				getchar();
				getchar();
				system("clear");
			break;
			case 5:
			system("clear");
			printf("Simulador Versao 1.0 - Simulador da arquitetura de processadores MIPS para entender como funciana a \n");
			printf("organizacao,a decodificaccao  e execucao em linguagem de assembly e linguagem de maquina.\n");
			printf("Presione ENTER para retornar ao menu\n");
			getchar();
			getchar();
			system("clear");
			break;

			case 6:
			break;

			default:
			printf("\nNenhuma opcao selecionada\n");
			printf("Presione ENTER para retornar ao menu\n");
			getchar();
			getchar();
			system("clear");
			break;
		}
}
