#include "celular.hpp"

// TODO: Inicialize aqui sua variavel estatica. Caso tenha optado por essa
// solucao.

Celular::Celular(std::string modelo,
                 std::string fabricante,
                 int armazenamento,
                 std::string memoria, //int
                 double peso,
                 std::string cor,
                 int qtd,
                 float valor) {
  this->_modelo = modelo;
  this->_fabricante = fabricante;
  this->_armazenamento = armazenamento;
  this->_memoria = memoria;
  this->_peso = peso;
  this->_cor = cor;
  this->_qtd = qtd;
  this->_valor = valor;
}

//vood int

bool Celular::operator<(const Celular& other) {
  // TODO: Implemente este metodo. 
  // Preste atencao no exemplo que a descricao utilizada na ordenacao considera
  // a fabricante antes do modelo do celular
  
  return false;
}