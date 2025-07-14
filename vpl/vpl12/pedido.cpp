#include "pedido.hpp"


Pedido::~Pedido() {
  for(auto it : m_produtos){
      delete(it);
  }
}

void Pedido::setEndereco(const std::string& endereco) {
  m_endereco = endereco;
}

float Pedido::calculaTotal() const {
  float total=0;
  for (auto it : m_produtos){
    total += it->getQtd() * it->getValor(); 
  }
  return total;
}

void Pedido::adicionaProduto(Produto* p) {
  m_produtos.push_back(p); 
}

std::string Pedido::resumo() const {
  std::string final = "";
  for (auto it : m_produtos){
    final += it->descricao() + "\n";
  }
  final += "Endereco: " + m_endereco + ".\n";
  return final;
}

