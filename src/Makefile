IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR = ../lib

LIBS=-lm

_DEPS = funcoesMemory.h InputData.h SimpleOperation.h Instrucoes.h Interface.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
 
_OBJ = main.o funcoesMemory.o InputData.o SimpleOperation.o Instrucoes.o Interface.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

ProjetoOAC: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
		rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
