#include "Interface.h"
#include <string.h>

extern int32_t registers[32];
extern int flag;

int main(int argc, char **argv){
	if (argc < 4) {
		printf("Parametros faltando!\n");
		return 0;
	}

	if (strcmp("f", argv[3]) == 0) {
		zerarMemory();
		adressMemory();
		LoadPtext(argv[1]);
		LoadPdata(argv[2]);
		system("clear");
		flag = 1;
		pc = 0x00000000;
		run();
		printMemory();
		printReg();
		printf("\n\nArquivos de saida gerados com sucesso!");
		printf("\nPrograma Executado com sucesso!\nEncerrando...\n");
	} else if (strcmp("p", argv[3]) == 0) {
		int opc;
		system("clear");
		zerarMemory();
		adressMemory();
		LoadPtext(argv[1]);
		LoadPdata(argv[2]);
		system("clear");
		while( opc != 6 ){
			opc = menu();
			opcao(opc);
		}
	} else {
		printf("Parametro %s invalido!\n", argv[3]);
	}
	return 0;
}
