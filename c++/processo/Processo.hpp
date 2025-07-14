#ifndef PROCESSO_H
#define PROCESSO_H

#include "Processo.hpp"
#include <string>
#include <iostream>

struct Processo{

    int _id;
    std::string _nome;
    int _prioridade;

    Processo();
    Processo(int id, std::string nome, int prioridade){
        this->_id = id;
        this->_nome = nome;
        this->_prioridade = prioridade;
    }

    void imprimir_dados(){
        std::cout << this->_id << " " << this->_nome << " " << this->_prioridade << std::endl;
    }

}

#endif