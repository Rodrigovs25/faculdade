#include "Nave.hpp"


Nave::Nave() {}

Nave::Nave(Ponto2D p1, double forca){
    this->_p1._x = p1._x;
    this->_p1._y = p1._y;
    this->energia = 100;
    if(forca == 0)
        this->_forca = 1;
    else
        this->_forca = forca;
}

void Nave::mover(double dx, double dy){
    this->_p1._x = this->_p1._x + dx;
    this->_p1._y = this->_p1._y + dy;
}

double Nave::calcular_distancia(Nave* nave){
    double dis = this->_p1.calcular_distancia(&(nave->_p1));
    return dis;
}

Nave* Nave::determinar_nave_mais_proxima(Nave** naves, int n){
    Nave *menor = nullptr;
    double dist = 10000;//this->calcular_distancia(naves[0]);
    double main=0;
    for (int i = 0; i < n; i++){
        main = this->calcular_distancia(naves[i]);
        if(main < dist && main != 0){
            menor = naves[i];
            dist = main;
        }
    }
    return menor;
}

void Nave::atacar(Nave** naves, int n){
    Nave *proxima = this->determinar_nave_mais_proxima(naves, n);
    double d = this->calcular_distancia(proxima);
    double dano = (100/d)*(this->_forca);
    if(dano > 30){
        dano = 30;
    }
    proxima->energia -= dano;
    if(proxima->energia <= 50){
        std::cout << "Energia baixa!" << std::endl;
    }
}

void Nave::imprimir_status(){
    std::cout << this->_p1._x << " " << this->_p1._y << " " << this->energia << std::endl;
}