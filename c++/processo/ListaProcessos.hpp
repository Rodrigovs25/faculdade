#ifndef LISTAPROCESSOS_H
#define LISTAPROCESSOS_H

#include "Processo.hpp"
#include "ListaProcessos.hpp"
#include <cmath>
#include <iostream>

struct Node {
    Processo *processo;
    Node *next;
}

struct ListaProcessos {

    Node* head = nullptr;
    Node* tail = nullptr;

    void adicionar_processo(Processo* proc){
        Node* aux = new Node;
        aux->processo = proc;
        aux->next = nullptr;

        
        if (head == nullptr) {
            head = aux;
            tail = aux;
        } else {
            //precorrer a lista
            Node *current = this->head;
            Node *previous = nullptr;
            
            while (current != nullptr && proc->_prioridade <= current->processo->_prioridade) {
                previous = current;
                current = current->next;
            }
            //com a posição, bassta inserir
            if(current == nullptr){//FIM
                this->tail->next = aux;
                this->tail = aux;
            } else if(previous == nullptr){//priridade já é maior que a maior(HEAD)
                aux->next = this->head;
                this->head = aux;
            } else { // no meio da lista
                aux->next = previous->next;
                previous->next = aux->next;
            }
        }
    }

    Processo* remover_processo_maior_prioridade(){
        Processo *maior = this->head->processo;
        
        Node *aux = this->head;
        this->head = this->head->next;

        delete aux; 

        return maior;
    }

    Processo* remover_processo_menor_prioridade(){
        Processo *menor = this->tail->processo;
        Node *aux = this->tail;

        Node *current = head;
        while (current->next != this->tail) {
            current = current->next;
        }

        current->next = nullptr;
        this->tail = current;

        return menor;
    }

    Processo* remover_processo_por_id(int id){
        Node *current = this->head;
        Node *previous = nullptr;

        //percorrer a lista
        while(current != nullptr){
            //achar o q vai ser removido
            if(current->processo->_id == id){
                Processo *proc = current->processo;

                if(current == this->head){
                    this->head = current->next;
                } else if (current == this->tail){
                    previous->next = nullptr
                    this->tail = previous;
                } else {
                    previous->next = current->next;
                }

                delete current;
                return proc;

            }
            previous = current;
            current = current->next;
        }

        return nullptr;
    }

    void imprimir_lista(){
        Node *aux = head;
        while (aux != nullptr) {
            aux->processo->imprimir_dados();
            aux = aux->next;
        }
        cout << endl;
    }
};

#endif