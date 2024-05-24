#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>

#include "fibonacci.h"
#include "fatorial.h"
#include "msgassert.h"

// definicoes de operacoes a serem testadas
#define FATITE 1
#define FATREC 2
#define FIBITE 3
#define FIBREC 4

// variaveis globais para opcoes
static int opescolhida;
char outnome[100];
int optx;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
  fprintf(stderr,"\t-s \t(fatorial iterativo) \n"); 
  fprintf(stderr,"\t-m \t(fatorial recursivo) \n");
  fprintf(stderr,"\t-t \t(fibonacci iterativo)\n");
  fprintf(stderr,"\t-h \t(fibonacci recursivo)\n");
  fprintf(stderr,"\t-x <int>\t(numero(1-20))\n");
}

void parse_args(int argc,char ** argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: optescolhida, optx, 
{
     // variaveis externas do getopt
     extern char * optarg;
     extern int optind;

     // variavel auxiliar
     int d;

     // inicializacao variaveis globais para opcoes
     opescolhida = -1;
     optx = -2;
     outnome[0] = 0;

     // getopt - letra indica a opcao, : junto a letra indica parametro
     // no caso de escolher mais de uma operacao, vale a ultima
     while ((d = getopt(argc, argv, "smtc:p:x:lh")) != -1){// EOF
       switch(d) {
         case 's':
	          avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = FATITE;
            break;
         case 'm':
	          avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = FATREC;
            break;
         case 't':
	          avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = FIBITE;
            break;
         case 'h':
	          avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = FIBREC;
            break;
         case 'x': 
	          optx = atoi(optarg);
		        break;
         case 'c':
         default:
                  uso();
                  exit(1);

       }
     }
     // verificacao da consistencia das opcoes
     erroAssert(opescolhida>0,"main - necessario escolher operacao");
     //erroAssert(optx>0,"main - x tem que ser positiva");
}

int main(int argc, char ** argv){

    // tempo do relogio, time
    struct timespec t1, t2, res;

    // avaliar linha de comando
    parse_args(argc,argv);

    clock_gettime(CLOCK_MONOTONIC, &t1);

    // execucao dependente da operacao escolhida
    switch (opescolhida){
        case FATITE:
            printf("Numero fatorial iterativo: %d\n", fatorialIterativo(optx));
            break;
        case FATREC:
            printf("Numero fatorial recursivo: %d\n", fatorialRecursivo(optx));
            break;
        case FIBITE:
            printf("Numero fibonacci iterativo: %d\n", fibonacciIterativo(optx));
            break;
        case FIBREC:
            printf("Numero fibonacci recursivo: %d\n", fibonacciRecursivo(optx));
            break;
    default:
            // nao deve ser executado, pois ha um erroAssert em parse_args
            uso();
    exit(1);
    }

    clock_gettime(CLOCK_MONOTONIC, &t2);

    // tempo do relogio, time
    if (t2.tv_nsec < t1.tv_nsec){
        res.tv_nsec =  1000000000 + t2.tv_nsec - t1.tv_nsec;
        res.tv_sec = t2.tv_sec - t1.tv_sec - 1;
    }
    else{
        res.tv_nsec = t2.tv_nsec - t1.tv_nsec;
        res.tv_sec = t2.tv_sec - t1.tv_sec;
    }
    printf("Tempo: %ld.%.9ld\n", res.tv_sec, res.tv_nsec);

    return 0;
}

//time .a.out 20
// .9 no segundo no printf
//g++ -pg ...
//time
//gprof ./a.out gmou.out | more; gprof ./bin/main gmon.out > gprof/analiseFATITE.txt
//man gprof -> opcoes gprof
//man getrusage
// 45 limite do recursivo

//time ./bin/main -h -x 40

/*
    $(EXE) -s -x 5
	$(EXE) -m -x 5
	$(EXE) -t -x 5
	$(EXE) -h -x 5
*/

/*
case FATITE:
            clock_gettime(CLOCK_MONOTONIC, &t1);
            printf("Numero FATITE: %d\n", fatorialIterativo(optx));
            clock_gettime(CLOCK_MONOTONIC, &t2);
            break;
        case FATREC:
            clock_gettime(CLOCK_MONOTONIC, &t1);
            printf("Numero FATREC: %d\n", fatorialRecursivo(optx));
            clock_gettime(CLOCK_MONOTONIC, &t2);
            break;
        case FIBITE:
            clock_gettime(CLOCK_MONOTONIC, &t1);
            printf("Numero FIBITE: %d\n", fibonacciIterativo(optx));
            clock_gettime(CLOCK_MONOTONIC, &t2);
            break;
        case FIBREC:
            clock_gettime(CLOCK_MONOTONIC, &t1);
            printf("Numero FIBREC: %d\n", fibonacciRecursivo(optx));
            clock_gettime(CLOCK_MONOTONIC, &t2);
            break;
*/