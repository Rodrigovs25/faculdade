/*#include "test.h"

int main(int argc, char* argv[]) {
    Test* pTest = new Test();
    pTest->Print();
    return 0;
}*/
#include <iostream>
#include <string>
#include "test.h"

// definicoes de operacoes a serem testadas
#define LER 1
#define INFIXA 2
#define POSFIXA 3
#define RESOLVE 4

// variaveis globais para opcoes
static int opescolhida;
char outnome[100];
int optx;

using namespace std;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
  fprintf(stderr,"\t-LER <string>\t(ler a expressao) \n"); 
  fprintf(stderr,"\t-INFIXA \t(expressao armazenada no programa para notacao infixa) \n");
  fprintf(stderr,"\t-POSFIXA \t(expressao armazenada no programa para notacao posfixa)\n");
  fprintf(stderr,"\t-RESOLVE \t(operacao que calcula a expressao)\n");
  
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
     while ((d = getpt(argc, argv, "smtc:p:x:lh")) != -1){// EOF
       switch(d) {
         case "LER":
	          //avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = LER;
            break;
         case "INFIXA":
	          //avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = INFIXA;
            break;
         case "POSFIXA":
	          //avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = POSFIXA;
            break;
         case "RESOLVE":
	          //avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = RESOLVE;
            break;
         default:
                  uso();
                  exit(1);

       }
     }
     // verificacao da consistencia das opcoes
     //erroAssert(opescolhida>0,"main - necessario escolher operacao");
     //erroAssert(optx>0,"main - x tem que ser positiva");
}

int main(int argc, char ** argv){

    

    // avaliar linha de comando
    parse_args(argc,argv);

    

    // execucao dependente da operacao escolhida
    switch (opescolhida){
        case LER:
            cout << "LER" << endl;
            break;
        case INFIXA:
            cout << "INFIXA" << endl;
            break;
        case POSFIXA:
            cout << "POSFIXA" << endl;
            break;
        case RESOLVE:
            cout << "RESOLVE" << endl;
            break;
    default:
            // nao deve ser executado, pois ha um erroAssert em parse_args
            uso();
    exit(1);
    }

    

    return 0;
}