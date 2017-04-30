README

#-------------------------------------------------------------------------
#		Organização e Arquitetura de Computadores - Turma C 
#			Trabalho 2 - Simulador Assembly MIPS
#
# Semestre: 1/2017.
#
# Professor: Marcelo Grandi Mandelli.
#
# Nome:  Lukas Ferreira Machado			Matrícula: 12/0127377.
# Nome:  Eduardo Said Calil Vilaça		Matrícula: 13/0154253. 
# Nome:  Raphael Luis Souza de Queiroz 	        Matrícula: 13/0154989.
#
#  		"Lately, I've been working to convince myself that
#  		   everything is a computation." - Rudy Rucker.
#-------------------------------------------------------------------------

Compilacao:
Para compilar o programa deve-se seguir no terminal ate a pasta /src , 
e nesse diretorio executar o comando 'make'. O programa foi executado 
e compilado com sucesso no meu computador. Apos compilado deve-se executar 
o arquivo objeto ./ProjetoOAC

->Recomenda-se executar o programa com terminal em tela cheia para melhor visualizacao das impressoes no console.

Meu computador: 
Sistema Operacional: MAC OS X Sierra 10.12.4
Compilador( linguagem C) : GCC 4.2.1
Apple LLVM version 8.1.0 (clang-802.0.38)

Instrucoes de Uso do Programa:
Ao iniciar o programa, temos que ele segue os seguintes passos:
[1] Zera memoria para execusao e endereca a memoria em bytes

[2] Carrega Arquivos binarios provenientes do simulador MARS
opcoes no zip:
Teste 1: Roteiro - Numeros Primos
		.text: teste1Text.bin
		.data: teste1Data.bin

Teste 2: Roteiro - Fibonacci
		.text: teste2Text.bin
		.data: teste2Data.bin

Teste 3: Roteiro - Soma recursiva
		.text: teste3Text.bin

Teste 4: Roteiro - Multiplicacao e Divisao(Imprimir ao final conteudo dos registradores)
		.text: teste4Text.bin
		.data: teste4Data.bin

Ao iniciar o programa via parâmetro p, ira aparecer um MENU iterativo o qual possui as seguintes opcoes:

[1]Executa passo a passo imprimindo os registradores e os campos das instrucoes

[2]Executa o Programa ate o final

[3]Imprime Regiao da memoria a partir do endereco dado pelo usuario(em bytes)

[4]Imprime Registradores

[5]Imprime o objetivo do projeto 

[6]Encerra o Programa
