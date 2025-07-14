#ifndef PONTO2D_H
#define PONTO2D_H

//#include "Ponto2D.hpp"
#include <cmath>

struct Ponto2D {
  
    double x;
    double y;
    
    Ponto2D() {
        this->x = 0;
        this->y = 0;
    };
    
    Ponto2D(double x_, double y_) { //Ponto2D(double x_ = 0, double y_ = 0) {
        this->x = x_;
        this->y = y_;
    }

    double calcular_distancia(Ponto2D* ponto){
        double dx = ponto->x - this->x;
        double dy = ponto->y - this->y;
        return sqrt(dx*dx + dy*dy);
    }
};

#endif
/*
#ifndef PONTO2D_H
#define PONTO2D_H

#include "Ponto2D.hpp"
#include <cmath>

struct Ponto2D {
  
    double _x;
    double _y;
    
    Ponto2D(double x = 0, double y = 0) {
        this->_x = x;
        this->_y = y;
    }

    double calcular_distancia(Ponto2D* ponto){
        double dx = ponto->_x - this->_x;
        double dy = ponto->_y - this->_y;
        return sqrt(dx*dx + dy*dy);
    }
};

#endif
*/