#include "Ponto2D.hpp"

Ponto2D::Ponto2D() {}

Ponto2D::Ponto2D(double x, double y ) {
    this->_x = x;
    this->_y = y;
}

double Ponto2D::calcular_distancia(Ponto2D* ponto){
    double dx = this->_x - ponto->_x;
    double dy = this->_y - ponto->_y;
    return sqrt(dx*dx + dy*dy);
}