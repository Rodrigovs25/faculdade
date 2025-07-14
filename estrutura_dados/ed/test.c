#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>

#define avisoAssert(e,m) ((void) ((e)?0: __avisoassert (#e,__FILE__,__LINE__,m)))
#define __avisoassert(e,file,line,m) ((void) fprintf(stderr,"%s:%u: Aviso: '%s' - %s\n",file,line,e,m),0)
#define erroAssert(e,m) ((void) ((e)?0: __erroassert (#e,__FILE__,__LINE__,m)))
#define __erroassert(e,file,line,m) ((void) fprintf(stderr,"%s:%u: Erro '%s' - %s\n",file,line,e,m), abort(),0)

struct timespec tp;

int fatorialRecursivo (int n){
    if(n < 1){
        return 1;
    }
    return n * fatorialRecursivo(n-1);
}

int fatorialIterativo (int n){
    int fat = 1;
    
    for (int i = 1; i <= n; i++){
        fat *= i;
    }
    
    return fat;
}

int fibonacciRecursivo (int n){
    if (n <= 2){
        return 1;
    }
    else{
        return fibonacciRecursivo(n-1) + fibonacciRecursivo(n-2);
    }
}

int fibonacciIterativo (int n){
    int a = 0, b = 1, c = 0;

    for (int i = 1; i < n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    
    return b;
}

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
  fprintf(stderr,"\t-c \t(fibonacci recursivo)\n");
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

    //int result = clock_gettime(CLOCK_MONOTONIC,&tp);
    // tp.tv_sec;
    // tp.tv_nsec;

   
    // avaliar linha de comando
    parse_args(argc,argv);

    // execucao dependente da operacao escolhida
    switch (opescolhida){
        case FIBREC:
            printf("Numero %d\n", fibonacciRecursivo(optx));
            break;
        case FATITE:
            printf("Numero %d\n", fatorialIterativo(optx));
            break;
        case FATREC:
            printf("Numero %d\n", fatorialRecursivo(optx));
            break;
        case FIBITE:
            printf("Numero %d\n", fibonacciIterativo(optx));
            break;
    default:
            // nao deve ser executado, pois ha um erroAssert em parse_args
            uso();
    exit(1);
    }

    return 0;
}

//time .a.out 20
// .9 no segundo no printf
//g++ -pg ...
//time
//gprof ./a.out gmou.out | more; gprof ./bin/main gmon.out > analise.txt
//man gprof -> opcoes gprof
//man getrusage
//

//gcc -pg test.c
// ./a.out -t -x 20
// gprof ./a.out gmon.out > analise.txt