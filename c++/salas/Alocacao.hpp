#ifndef ALOCACAO_H
#define ALOCACAO_H

#include <iostream>

using namespace std;

struct Alocacao
{
    string _dia, _horario, _sala;

    Alocacao(string dia, string horario, string sala){
        this->_dia = dia;
        this->_horario = horario;
        this->_sala = sala;
    }

    void imprimir_dados(){
        cout << this->_dia << " " << this->_horario << " " << this->_sala << endl;
    }
};

#endif