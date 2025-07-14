#include "ponto.hpp"

Ponto::Ponto(){
    this->x = 0;
    this->y = 0;
}

Ponto::Ponto(int x, int y) : x(x), y(y) {}

int Ponto::getX() const {
    return this->x;
}

int Ponto::getY() const {
    return this->y;
}

int Ponto::distanciaEntreDoisPontos(const Ponto& outro) {
    int dx = this->x - outro.getX();
    int dy = this->y - outro.getY();
    return dx*dx + dy*dy;
}