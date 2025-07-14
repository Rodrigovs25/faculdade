CC=c++
CFLAGS=-std=c++14 -Wall
BUILD    = ./build
SRC    = ./src
INCLUDE  = ./include
TARGET = vpl_execution

${TARGET}: ${BUILD}/Funcionario.o ${BUILD}/Pessoa.o ${BUILD}/Professor.o ${BUILD}/main.o
	${CC} ${CFLAGS} $^ -o $@

${BUILD}/Funcionario.o: ${SRC}/entidades/Funcionario.cpp ${INCLUDE}/Funcionario.hpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c $< -o $@

${BUILD}/Pessoa.o: ${SRC}/entidades/Pessoa.cpp ${INCLUDE}/Pessoa.hpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c $< -o $@

${BUILD}/Professor.o: ${SRC}/entidades/Professor.cpp ${INCLUDE}/Professor.hpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c $< -o $@

${BUILD}/main.o: ${SRC}/main.cpp ${INCLUDE}/Funcionario.hpp ${INCLUDE}/Pessoa.hpp ${INCLUDE}/Professor.hpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c $< -o $@

clean:
	rm -f ${BUILD}/* 
