#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <iostream>
#include "ponto.hpp"

class Pessoa {
    private:
        Ponto coordenada;
    
    public:
        
        Pessoa();
        Pessoa(Ponto coordenada);

        Ponto getCoordenada() const;
        
};

#endif