#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <vector>
#include <algorithm>
#include "Alocacao.hpp"

struct comparador_alocacao{
    bool operator()(const Alocacao& a1, const Alocacao& a2){
        return a1._horario < a2._horario;
    }
};


struct Disciplina{

    string _codigo, _nome;
    vector<Alocacao> _alocacao;

    Disciplina(string codigo, string nome){
        this->_codigo = codigo;
        this->_nome = nome;
    }

    void inserir_alocacao(string dia, string horario, string sala){
        this->_alocacao.push_back(Alocacao(dia, horario, sala));
    }

    void remover_alocacao(string horario){
        for (int i = 0; i < _alocacao.size(); i++){
            if(_alocacao[i]._horario == horario){
                _alocacao.erase(_alocacao.begin() + i);
            }
        }
    }

    void imprimir_alocacao(){

        sort(_alocacao.begin(), _alocacao.end(), comparador_alocacao());

        for(Alocacao &alocacao : this->_alocacao){
            cout << this->_codigo << " " << this->_nome << " ";
            alocacao.imprimir_dados();
        }
    }

};

#endif