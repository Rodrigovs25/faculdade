#ifndef ABRIGO_HPP
#define ABRIGO_HPP

#include <iostream>
#include <vector>
#include "ponto.hpp"

class Abrigo {
    private:
        int raio;
        Ponto centro;
    
    public:
        
        Abrigo();
        Abrigo(int raio, Ponto centro);

        int getRaio() const;
        Ponto getCentro() const;

        int encontrarAbrigo(const std::vector<Abrigo>& abrigos);
        
};

#endif