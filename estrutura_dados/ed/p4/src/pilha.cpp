#include <iostream>
#include "fila.h"
#include "pilha.h"

PilhaArranjo::PilhaArranjo() : Pilha(){
    tamanho = 0;
}

void PilhaArranjo::criapilha(){
    tamanho = 0;
}

void PilhaArranjo::empilha(TipoItem item){
    if(tamanho == MAXTAM)
        throw "A pilha está cheia!";
    tamanho++;
    fila1.Enfileira(item);
}   

TipoItem PilhaArranjo::desempilha(){
    
    if(tamanho == 0)
        throw "A pilha está vazia!";
    
    int n = fila1.GetTamanho();
    for (int i = 0; i < n-1; i++) {
        fila2.Enfileira(fila1.Desenfileira());
    }
    TipoItem resultado = fila1.Desenfileira();
    for (int i = 0; i < n-1; i++) {
        fila1.Enfileira(fila2.Desenfileira());
    }
    tamanho--;
    return resultado;
}

void PilhaArranjo::destroipilha(){
    tamanho = 0;
}
