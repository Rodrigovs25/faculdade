#include "ListaProcessos.hpp"

void ListaProcessos::adicionar_processo(Processo* proc){
    Processo* aux = nullptr;
    if(this->_inicio == nullptr){
        this->_inicio = proc;
        this->_inicio.proximo = nullptr;
    }
    else{
        while(this->_inicio != nullptr){]
            aux = this->_inicio;
            if(this->_inicio._prioridade < proc->_prioridade){
                this->_inicio = proc;
                this->_inicio.proximo = aux;
                break;
            }
            else if(this->_inicio._prioridade > proc->_prioridade){
                this->_inicio = this->_inicio.proximo;
            }
        }
    }
}

Processo* ListaProcessos::remover_processo_maior_prioridade(){
    /*
    int maior=0, priori=0;
    Processo* promaior = nullptr;
    while(this->_inicio != nullptr){
        priori = this->_inicio.prioridade;
        if(priori > maior){

        }
        this->_inicio = this->_inicio.proximo;
    }
    */
    this->_inicio = this->_inicio.proximo;
}

Processo* ListaProcessos::remover_processo_menor_prioridade(){
    if(this->_inicio.proximo = nullptr){
        this->_inicio = nullptr;
    }
}

Processo* ListaProcessos::remover_processo_por_id(int id){

}

void ListaProcessos::imprimir_lista(){

}