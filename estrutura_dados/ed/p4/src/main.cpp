#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "fila.h"
#include "pilha.h"

using namespace std;

int main(){

  PilhaArranjo pilha;
  TipoItem t;

  /*for (int i = 0; i < 10; i++){
    t.SetChave(i);
    pilha.empilha(t);
    //t = pilha.desempilha();
    cout << "Tamanho: " << pilha.GetTamanho() << endl;
  }*/
  
  for (int i = 0; i < 10; i++) {
    int escolha = rand() % 4;
    if (escolha == 0 && !pilha.pilhavazia()) {
      pilha.desempilha();
      //cout << "Desempilhando " << t.Imprime() << endl;
      cout << "Tamanho: " << pilha.GetTamanho() << endl;
    } 
    else if(escolha > 0) {
      t.SetChave(rand() % 10); 
      //cout << "Empilhando " << t.Imprime() << endl;
      cout << "Tamanho: " << pilha.GetTamanho() << endl;
      pilha.empilha(t);
      }
  }
  
  return 0;
}