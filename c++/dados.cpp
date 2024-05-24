#include <iostream>

struct Ponto {
  // Dados
  double _x_val;
  double _y_val;

  // Operacoes
  // 1. Construtor
  Ponto(double x_val, double y_val) {
    _x_val = x_val;
    _y_val = y_val;
  }
};

int main(){
    Ponto p1 = Ponto(1, 2);
}