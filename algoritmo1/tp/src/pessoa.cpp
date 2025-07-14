#include "pessoa.hpp"

Pessoa::Pessoa(){
    this->coordenada = Ponto(0, 0);
}

Pessoa::Pessoa(Ponto coordenada) : coordenada(coordenada) {}

Ponto Pessoa::getCoordenada() const {
    return this->coordenada;
}