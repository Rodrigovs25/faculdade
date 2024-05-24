#include <iostream>
#include "fila.h"

TipoItem::TipoItem(){
    chave = -1; // indica um item vazio
}

TipoItem::TipoItem(TipoChave c){
    chave = c;
}

void TipoItem::SetChave(TipoChave c){
    chave = c;
}

TipoChave TipoItem::GetChave(){
    return chave;
}

void TipoItem::Imprime(){
    //printf("%d ",chave);
    std::cout << chave << " ";
}

FilaArranjo::FilaArranjo() : Fila(){
    frente = 0;
    tras = 0;
}

void FilaArranjo::Enfileira(TipoItem item) {
    if (tamanho == MAXTAM)
        throw "Fila Cheia!";

    itens[tras] = item;
    // fila circular
    tras = (tras + 1) % MAXTAM; 
    tamanho++;
}

TipoItem FilaArranjo::Desenfileira() {
    TipoItem aux;

    if (tamanho == 0)
        throw "Fila está vazia!";

    aux = itens[frente];
    // fila circular
    frente = (frente + 1) % MAXTAM; 
    tamanho--;
    return aux;
}

void FilaArranjo::Limpa() {
    frente = 0;
    tras = 0;
    tamanho = 0;
}