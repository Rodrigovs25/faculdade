#include "abrigo.hpp"

Abrigo::Abrigo(){
    this->raio = 0;
    this->centro = Ponto(0, 0);
}

Abrigo::Abrigo(int raio, Ponto centro) : raio(raio), centro(centro) {}

int Abrigo::getRaio() const {
    return this->raio;
}

Ponto Abrigo::getCentro() const {
    return this->centro;
}

int Abrigo::encontrarAbrigo(const std::vector<Abrigo>& abrigos) {
    int n = static_cast<int>(abrigos.size());
    for(int i = 0; i < n; ++i) {
        int dist2 = abrigos[i].getCentro().distanciaEntreDoisPontos(this->getCentro());
        if(dist2 <= abrigos[i].getRaio() * abrigos[i].getRaio() ) {
            return i;
        }
    }
    return -1;
}