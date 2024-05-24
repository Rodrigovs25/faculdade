#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2022-04-02 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/fatorial.o $(OBJ)/fibonacci.o
HDRS = $(INC)/fatorial.h $(INC)/fibonacci.h $(INC)/msgassert.h 
CFLAGS = -Wall -c -pg -I$(INC)

EXE = $(BIN)/main

run:  $(EXE)
	$(EXE) -s -x 5
	$(EXE) -m -x 5
	$(EXE) -t -x 5
	$(EXE) -h -x 5

$(BIN)/main: $(OBJS)
	$(CC) -pg -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.c
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.c 

$(OBJ)/fatorial.o: $(HDRS) $(SRC)/fatorial.c
	$(CC) $(CFLAGS) -o $(OBJ)/fatorial.o $(SRC)/fatorial.c

$(OBJ)/fibonacci.o: $(HDRS) $(SRC)/fibonacci.c
	$(CC) $(CFLAGS) -o $(OBJ)/fibonacci.o $(SRC)/fibonacci.c
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
