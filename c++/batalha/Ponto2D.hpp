#ifndef PONTO2D_H
#define PONTO2D_H

#include "Ponto2D.hpp"
#include <cmath>

struct Ponto2D {
  
    double _x;
    double _y;
    
    Ponto2D();
    Ponto2D(double x, double y);

    double calcular_distancia(Ponto2D* ponto);
};

#endif