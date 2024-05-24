#ifndef QUADRO_H
#define QUADRO_H

#include <map>
#include "Disciplina.hpp"

struct QuadroAlocacao{

    map<string, Disciplina> _alocacao;
    
    //A disciplina ta no map?
    void inserir_alocacao(string codigo, string nome, string dia, string horario, string sala){
        if(!-_alocacao.count(codigo)){
            //Se não estiver tenho q inserir
            _alocacao.insert(pair<string, Disciplina>(codigo, Disciplina(codigo, nome)));
        }
        
        //Se estiver, eu tenho q adicionar uma nova alocacao para ela
        _alocacao.find(codigo)->second.inserir_alocacao(dia, horario, sala);


    }

    void remover_alocacao_disciplina(string codigo, string horario){
        _alocacao.find(codigo)->second.remover_alocacao(horario);
    }

    vector<Disciplina> recuperar_disciplinas_mais_ofertadas(){
        vector<Discplina> mais_ofertadas;

        int max_ofertas = -1;
        //cortar o maior numero de oferta de cada disciplina
        map<string, Disciplina>::iterator it;
        for(it =_alocacao.begin(); it != _alocacao.end(); ++it){
            Disciplina disciplina = it->second;
            int num = disciplina._alocacao.size();

            if(max_ofertas < 0 || num > max_ofertas){
                max_ofertas = num;
            }
        }
        //retormar so as mais ofertadas
        for(it =_alocacao.begin(); it != _alocacao.end(); ++it){
            Disciplina disciplina = it->second;
            int num = disciplina._alocacao.size();

            if(num == max_ofertas){
                mais_ofertadas.push_back(disciplina);
            }
        }

        return mais_ofertadas;
    }

    void imprimir_alocacao_completa(){
        map<string, Disciplina>::iterator it;
        for(it =_alocacao.begin(); it != _alocacao.end(); ++it){
            string codigo = it->first;
            Disciplina disciplina = it->second;
            disciplina.imprimir_alocacao();
        }
    }
    

};

#endif