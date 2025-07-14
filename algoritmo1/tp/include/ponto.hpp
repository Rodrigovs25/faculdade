#ifndef PONTO_HPP
#define PONTO_HPP

#include <iostream>

class Ponto {
    private:
        int x, y;
    
    public:
        
        Ponto();
        Ponto(int x, int y);

        int getX() const;
        int getY() const;

        int distanciaEntreDoisPontos(const Ponto& outro);
};

#endif